#include "Stats.hpp"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace perfmode {

namespace {

bool g_runtimeActive = true;

}

Stats& stats() {
	static Stats s;
	return s;
}

bool enabled() {
	return Mod::get()->getSettingValue<bool>("enabled");
}

bool cullObjects() {
	return Mod::get()->getSettingValue<bool>("cull-offscreen");
}

bool cullParticles() {
	return Mod::get()->getSettingValue<bool>("skip-particles");
}

bool cullLabels() {
	return Mod::get()->getSettingValue<bool>("skip-labels");
}

float margin() {
	return static_cast<float>(Mod::get()->getSettingValue<int64_t>("cull-margin"));
}

void setRuntimeActive(bool active) {
	g_runtimeActive = active;
}

bool runtimeActive() {
	return g_runtimeActive;
}

}
