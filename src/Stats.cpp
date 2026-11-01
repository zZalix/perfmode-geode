#include "Stats.hpp"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace perfmode {

namespace {

bool g_runtimeActive = true;
unsigned long long g_drawn = 0;
unsigned long long g_culled = 0;

}

void setRuntimeActive(bool active) {
	g_runtimeActive = active;
}

bool runtimeActive() {
	return g_runtimeActive;
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

float margin() {
	return static_cast<float>(Mod::get()->getSettingValue<int64_t>("cull-margin"));
}

void onHidden(cocos2d::CCNode*) {
	g_culled++;
}

void pruneRestoreList() {
}

unsigned long long drawnCount() {
	return g_drawn;
}

unsigned long long culledCount() {
	return g_culled;
}

void resetCounts() {
	g_drawn = 0;
	g_culled = 0;
}

}
