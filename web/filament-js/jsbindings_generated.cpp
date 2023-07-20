// This file has been generated by beamsplitter

#include <emscripten.h>
#include <emscripten/bind.h>

#include <filament/View.h>

using namespace emscripten;
using namespace filament;

EMSCRIPTEN_BINDINGS(jsbindings_generated) {

value_object<View::DynamicResolutionOptions>("View$DynamicResolutionOptions")
    .field("minScale", &View::DynamicResolutionOptions::minScale)
    .field("maxScale", &View::DynamicResolutionOptions::maxScale)
    .field("sharpness", &View::DynamicResolutionOptions::sharpness)
    .field("enabled", &View::DynamicResolutionOptions::enabled)
    .field("homogeneousScaling", &View::DynamicResolutionOptions::homogeneousScaling)
    .field("quality", &View::DynamicResolutionOptions::quality)
    ;

value_object<View::BloomOptions>("View$BloomOptions")
    // JavaScript binding for dirt is not yet supported, must use default value.
    // JavaScript binding for dirtStrength is not yet supported, must use default value.
    .field("strength", &View::BloomOptions::strength)
    .field("resolution", &View::BloomOptions::resolution)
    .field("anamorphism", &View::BloomOptions::anamorphism)
    .field("levels", &View::BloomOptions::levels)
    .field("blendMode", &View::BloomOptions::blendMode)
    .field("threshold", &View::BloomOptions::threshold)
    .field("enabled", &View::BloomOptions::enabled)
    .field("highlight", &View::BloomOptions::highlight)
    .field("lensFlare", &View::BloomOptions::lensFlare)
    .field("starburst", &View::BloomOptions::starburst)
    .field("chromaticAberration", &View::BloomOptions::chromaticAberration)
    .field("ghostCount", &View::BloomOptions::ghostCount)
    .field("ghostSpacing", &View::BloomOptions::ghostSpacing)
    .field("ghostThreshold", &View::BloomOptions::ghostThreshold)
    .field("haloThickness", &View::BloomOptions::haloThickness)
    .field("haloRadius", &View::BloomOptions::haloRadius)
    .field("haloThreshold", &View::BloomOptions::haloThreshold)
    ;

value_object<View::FogOptions>("View$FogOptions")
    .field("distance", &View::FogOptions::distance)
    .field("cutOffDistance", &View::FogOptions::cutOffDistance)
    .field("maximumOpacity", &View::FogOptions::maximumOpacity)
    .field("height", &View::FogOptions::height)
    .field("heightFalloff", &View::FogOptions::heightFalloff)
    .field("color", &View::FogOptions::color)
    .field("density", &View::FogOptions::density)
    .field("inScatteringStart", &View::FogOptions::inScatteringStart)
    .field("inScatteringSize", &View::FogOptions::inScatteringSize)
    .field("fogColorFromIbl", &View::FogOptions::fogColorFromIbl)
    // JavaScript binding for skyColor is not yet supported, must use default value.
    .field("enabled", &View::FogOptions::enabled)
    ;

value_object<View::DepthOfFieldOptions>("View$DepthOfFieldOptions")
    .field("cocScale", &View::DepthOfFieldOptions::cocScale)
    .field("maxApertureDiameter", &View::DepthOfFieldOptions::maxApertureDiameter)
    .field("enabled", &View::DepthOfFieldOptions::enabled)
    .field("filter", &View::DepthOfFieldOptions::filter)
    .field("nativeResolution", &View::DepthOfFieldOptions::nativeResolution)
    .field("foregroundRingCount", &View::DepthOfFieldOptions::foregroundRingCount)
    .field("backgroundRingCount", &View::DepthOfFieldOptions::backgroundRingCount)
    .field("fastGatherRingCount", &View::DepthOfFieldOptions::fastGatherRingCount)
    .field("maxForegroundCOC", &View::DepthOfFieldOptions::maxForegroundCOC)
    .field("maxBackgroundCOC", &View::DepthOfFieldOptions::maxBackgroundCOC)
    ;

value_object<View::VignetteOptions>("View$VignetteOptions")
    .field("midPoint", &View::VignetteOptions::midPoint)
    .field("roundness", &View::VignetteOptions::roundness)
    .field("feather", &View::VignetteOptions::feather)
    .field("color", &View::VignetteOptions::color)
    .field("enabled", &View::VignetteOptions::enabled)
    ;

value_object<View::RenderQuality>("View$RenderQuality")
    .field("hdrColorBuffer", &View::RenderQuality::hdrColorBuffer)
    ;

value_object<View::AmbientOcclusionOptions::Ssct>("View$AmbientOcclusionOptions$Ssct")
    .field("lightConeRad", &View::AmbientOcclusionOptions::Ssct::lightConeRad)
    .field("shadowDistance", &View::AmbientOcclusionOptions::Ssct::shadowDistance)
    .field("contactDistanceMax", &View::AmbientOcclusionOptions::Ssct::contactDistanceMax)
    .field("intensity", &View::AmbientOcclusionOptions::Ssct::intensity)
    .field("lightDirection", &View::AmbientOcclusionOptions::Ssct::lightDirection)
    .field("depthBias", &View::AmbientOcclusionOptions::Ssct::depthBias)
    .field("depthSlopeBias", &View::AmbientOcclusionOptions::Ssct::depthSlopeBias)
    .field("sampleCount", &View::AmbientOcclusionOptions::Ssct::sampleCount)
    .field("rayCount", &View::AmbientOcclusionOptions::Ssct::rayCount)
    .field("enabled", &View::AmbientOcclusionOptions::Ssct::enabled)
    ;

value_object<View::AmbientOcclusionOptions>("View$AmbientOcclusionOptions")
    .field("radius", &View::AmbientOcclusionOptions::radius)
    .field("power", &View::AmbientOcclusionOptions::power)
    .field("bias", &View::AmbientOcclusionOptions::bias)
    .field("resolution", &View::AmbientOcclusionOptions::resolution)
    .field("intensity", &View::AmbientOcclusionOptions::intensity)
    .field("bilateralThreshold", &View::AmbientOcclusionOptions::bilateralThreshold)
    .field("quality", &View::AmbientOcclusionOptions::quality)
    .field("lowPassFilter", &View::AmbientOcclusionOptions::lowPassFilter)
    .field("upsampling", &View::AmbientOcclusionOptions::upsampling)
    .field("enabled", &View::AmbientOcclusionOptions::enabled)
    .field("bentNormals", &View::AmbientOcclusionOptions::bentNormals)
    .field("minHorizonAngleRad", &View::AmbientOcclusionOptions::minHorizonAngleRad)
    // JavaScript binding for ssct is not yet supported, must use default value.
    ;

value_object<View::MultiSampleAntiAliasingOptions>("View$MultiSampleAntiAliasingOptions")
    .field("enabled", &View::MultiSampleAntiAliasingOptions::enabled)
    .field("sampleCount", &View::MultiSampleAntiAliasingOptions::sampleCount)
    .field("customResolve", &View::MultiSampleAntiAliasingOptions::customResolve)
    ;

value_object<View::TemporalAntiAliasingOptions>("View$TemporalAntiAliasingOptions")
    .field("filterWidth", &View::TemporalAntiAliasingOptions::filterWidth)
    .field("feedback", &View::TemporalAntiAliasingOptions::feedback)
    .field("enabled", &View::TemporalAntiAliasingOptions::enabled)
    ;

value_object<View::ScreenSpaceReflectionsOptions>("View$ScreenSpaceReflectionsOptions")
    .field("thickness", &View::ScreenSpaceReflectionsOptions::thickness)
    .field("bias", &View::ScreenSpaceReflectionsOptions::bias)
    .field("maxDistance", &View::ScreenSpaceReflectionsOptions::maxDistance)
    .field("stride", &View::ScreenSpaceReflectionsOptions::stride)
    .field("enabled", &View::ScreenSpaceReflectionsOptions::enabled)
    ;

value_object<View::GuardBandOptions>("View$GuardBandOptions")
    .field("enabled", &View::GuardBandOptions::enabled)
    ;

value_object<View::VsmShadowOptions>("View$VsmShadowOptions")
    .field("anisotropy", &View::VsmShadowOptions::anisotropy)
    .field("mipmapping", &View::VsmShadowOptions::mipmapping)
    .field("msaaSamples", &View::VsmShadowOptions::msaaSamples)
    .field("highPrecision", &View::VsmShadowOptions::highPrecision)
    .field("minVarianceScale", &View::VsmShadowOptions::minVarianceScale)
    .field("lightBleedReduction", &View::VsmShadowOptions::lightBleedReduction)
    ;

value_object<View::SoftShadowOptions>("View$SoftShadowOptions")
    .field("penumbraScale", &View::SoftShadowOptions::penumbraScale)
    .field("penumbraRatioScale", &View::SoftShadowOptions::penumbraRatioScale)
    ;

} // EMSCRIPTEN_BINDINGS