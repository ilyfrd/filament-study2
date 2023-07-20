/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <filament/Engine.h>
#include <filament/IndexBuffer.h>
#include <filament/LightManager.h>
#include <filament/Material.h>
#include <filament/RenderableManager.h>
#include <filament/Scene.h>
#include <filament/Skybox.h>
#include <filament/TextureSampler.h>
#include <filament/TransformManager.h>
#include <filament/VertexBuffer.h>
#include <filament/View.h>
#include <filament/Camera.h>

#include <math/norm.h>

#include <filamentapp/Config.h>
#include <filamentapp/FilamentApp.h>
#include <filamentapp/MeshAssimp.h>
#include <filamentapp/Sphere.h>


#include <fstream>
#include <iostream>

#include <ctime>
#include <random>

#include "generated/resources/resources.h"

using namespace filament;
using namespace filament::math;
using Backend = Engine::Backend;

struct GroundPlane {
    VertexBuffer* vb;
    IndexBuffer* ib;
    Material* mat;
    utils::Entity renderable;
};

struct App {
    Skybox* skybox;
    utils::Entity light;
    std::map<std::string, MaterialInstance*> materials;
    MeshAssimp* meshes;
    mat4f transform;
    GroundPlane plane;
};

// static const char* MODEL_FILE = "assets/models/monkey/monkey.obj";
static const char* MODEL_FILE = "assets/custom/models/aorta1.obj";
static const char* CUBE_FILE = "assets/models/cube/cube.obj";
static const char* IBL_FOLDER = "assets/ibl/lightroom_14b";

static const char* MATERIAL_FILE = "assets/custom/materials/sandboxLit.filamat";

extern filament::Camera* filamentAppMainCamera;

static std::ifstream::pos_type getFileSize(const char* filename) 
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
};

static constexpr bool ENABLE_SHADOWS = true;

static GroundPlane createGroundPlane(Engine* engine);

static const Config config {
    .title = "shadowtest",
    .iblDirectory = FilamentApp::getRootAssetsPath() + IBL_FOLDER,
    .scale = 1,
    .splitView = false
};

int main(int argc, char** argv) {
    App app;

    auto setup = [&app](Engine* engine, View* view, Scene* scene) {
        auto& tcm = engine->getTransformManager();
        auto& rcm = engine->getRenderableManager();
        auto& em = utils::EntityManager::get();

        // Add geometry into the scene.
        app.meshes = new MeshAssimp(*engine);
        app.meshes->addFromFile(FilamentApp::getRootAssetsPath() + MODEL_FILE, app.materials);
        auto firstEntity = app.meshes->getRenderables()[0];
        auto ti = tcm.getInstance(firstEntity);
        // app.transform = mat4f{ mat3f(1), float3(0, 0, -4) } * tcm.getWorldTransform(ti);
        app.transform = mat4f{ mat3f(0.01), float3(0, 0, 0) };
        tcm.setTransform(ti, app.transform);

        // 设置模型的材质
        auto materialPath = FilamentApp::getRootAssetsPath() + MATERIAL_FILE;
        std::ifstream in(materialPath.c_str(), std::ifstream::binary | std::ifstream::in);
        auto contentSize = getFileSize(materialPath.c_str());
        std::vector<uint8_t> buffer(static_cast<unsigned long>(contentSize));
        if (!in.read((char*) buffer.data(), contentSize)) 
        {
            std::cerr << "Unable to read " << std::endl;
            exit(1);
        }

        auto material = Material::Builder()
                .package(buffer.data(), buffer.size())
                .build(*engine);
        auto materialInstance = material->createInstance();
        materialInstance->setParameter("baseColor", float4(0.8, 0.8, 0.8, 1));
        materialInstance->setParameter("roughness", float(0.5));
        materialInstance->setParameter("metallic", float(0.0));
        materialInstance->setParameter("reflectance", float(1.0));

        for (auto renderable : app.meshes->getRenderables()) {
            auto instance = rcm.getInstance(renderable);
            if (rcm.hasComponent(renderable)) {
                rcm.setCastShadows(instance, ENABLE_SHADOWS);
                rcm.setReceiveShadows(instance, false);
                rcm.setMaterialInstanceAt(instance, 0, materialInstance);

                scene->addEntity(renderable);
            }
        }


        // Add light sources into the scene.
        app.light = em.create();
        LightManager::Builder(LightManager::Type::DIRECTIONAL)
            .color(Color::toLinear<ACCURATE>(sRGBColor(1.f, 1.f, 1.f)))
            .intensity(110000)
            .direction({ 0.7, -1, -0.8 })
            .castShadows(ENABLE_SHADOWS)
            .build(*engine, app.light);
        scene->addEntity(app.light);

        // Hide skybox and add ground plane.
        app.skybox = Skybox::Builder().color({0.5f,0.75f,1.0f,1.0f}).build(*engine);
        scene->setSkybox(app.skybox);
        app.plane = createGroundPlane(engine);
        // scene->addEntity(app.plane.renderable);
    };

    auto cleanup = [&app](Engine* engine, View*, Scene*) {
        engine->destroy(app.plane.renderable);
        engine->destroy(app.plane.mat);
        engine->destroy(app.plane.vb);
        engine->destroy(app.plane.ib);
        engine->destroy(app.light);
        engine->destroy(app.skybox);
        for (auto& item : app.materials) {
            engine->destroy(item.second);
        }
        delete app.meshes;
    };

    FilamentApp::get().animate([&app](Engine* engine, View* view, double now) {
        auto& tcm = engine->getTransformManager();
        auto ti = tcm.getInstance(app.meshes->getRenderables()[0]);
        // tcm.setTransform(ti, app.transform * mat4f::rotation(now, float3{ 0, 1, 0 }));

        auto cameraPosition = filamentAppMainCamera->getPosition();
        auto& lcm = engine->getLightManager();
        lcm.setDirection(lcm.getInstance(app.light), { -cameraPosition.x, -cameraPosition.y, -cameraPosition.z });

    });

    FilamentApp::get().run(config, setup, cleanup);

    return 0;
}

static GroundPlane createGroundPlane(Engine* engine) {
    Material* shadowMaterial = Material::Builder()
        .package(RESOURCES_GROUNDSHADOW_DATA, RESOURCES_GROUNDSHADOW_SIZE)
        .build(*engine);
    shadowMaterial->setDefaultParameter("strength", 0.7f);

    const static uint32_t indices[] {
        0, 1, 2, 2, 3, 0
    };
    const static float3 vertices[] {
        { -10, 0, -10 },
        { -10, 0,  10 },
        {  10, 0,  10 },
        {  10, 0, -10 },
    };
    short4 tbn = packSnorm16(normalize(positive(mat3f{
        float3{1.0f, 0.0f, 0.0f}, float3{0.0f, 0.0f, 1.0f}, float3{0.0f, 1.0f, 0.0f}
    }.toQuaternion())).xyzw);
    const static short4 normals[] { tbn, tbn, tbn, tbn };
    VertexBuffer* vertexBuffer = VertexBuffer::Builder()
        .vertexCount(4)
        .bufferCount(2)
        .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT3)
        .attribute(VertexAttribute::TANGENTS, 1, VertexBuffer::AttributeType::SHORT4)
        .normalized(VertexAttribute::TANGENTS)
        .build(*engine);
    vertexBuffer->setBufferAt(*engine, 0, VertexBuffer::BufferDescriptor(
            vertices, vertexBuffer->getVertexCount() * sizeof(vertices[0])));
    vertexBuffer->setBufferAt(*engine, 1, VertexBuffer::BufferDescriptor(
            normals, vertexBuffer->getVertexCount() * sizeof(normals[0])));
    IndexBuffer* indexBuffer = IndexBuffer::Builder().indexCount(6).build(*engine);
    indexBuffer->setBuffer(*engine, IndexBuffer::BufferDescriptor(
            indices, indexBuffer->getIndexCount() * sizeof(uint32_t)));

    auto& em = utils::EntityManager::get();
    utils::Entity renderable = em.create();
    RenderableManager::Builder(1)
        .boundingBox({{ 0, 0, 0 }, { 10, 1e-4f, 10 }})
        .material(0, shadowMaterial->getDefaultInstance())
        .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vertexBuffer, indexBuffer, 0, 6)
        .culling(false)
        .receiveShadows(ENABLE_SHADOWS)
        .castShadows(false)
        .build(*engine, renderable);

    auto& tcm = engine->getTransformManager();
    tcm.setTransform(tcm.getInstance(renderable), mat4f::translation(float3{ 0, -1, -4 }));
    return {
        .vb = vertexBuffer,
        .ib = indexBuffer,
        .mat = shadowMaterial,
        .renderable = renderable,
    };
}
