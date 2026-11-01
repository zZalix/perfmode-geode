#pragma once

namespace perfmode {

struct Stats {
	unsigned long long drawn = 0;
	unsigned long long culled = 0;
};

Stats& stats();

bool enabled();
bool cullObjects();
bool cullParticles();
bool cullLabels();
float margin();

void setRuntimeActive(bool active);
bool runtimeActive();

}
