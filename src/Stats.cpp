#include "Stats.hpp"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace perfmode {

namespace {

bool g_runtimeActive = true;
Settings g_settings;

}

void setRuntimeActive(bool active) {
	g_runtimeActive = active;
}

bool runtimeActive() {
	return g_runtimeActive;
}

Settings const& settings() {
	return g_settings;
}

void refreshSettings() {
	if (auto mod = Mod::get()) {
		g_settings.enabled = mod->getSettingValue<bool>("enabled");
		g_settings.cullObjects = mod->getSettingValue<bool>("cull-offscreen");
		g_settings.cullParticles = mod->getSettingValue<bool>("skip-particles");
		g_settings.margin = static_cast<float>(mod->getSettingValue<int64_t>("cull-margin"));
	}
}

void resetCounts() {
}

}
