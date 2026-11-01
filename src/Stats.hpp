#pragma once

#include <atomic>
#include <cstdint>

namespace perfmode {

void setRuntimeActive(bool active);
bool runtimeActive();

// Cached settings, refreshed only when the user changes them.
struct Settings {
	bool enabled = true;
	bool cullObjects = true;
	bool cullParticles = true;
	float margin = 64.f;
};

Settings const& settings();
void refreshSettings();

void resetCounts();

}
