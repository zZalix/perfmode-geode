#pragma once

namespace perfmode {

void setRuntimeActive(bool active);
bool runtimeActive();

bool enabled();
bool cullObjects();
bool cullParticles();
float margin();

void onHidden(cocos2d::CCNode* node);
void pruneRestoreList();

unsigned long long drawnCount();
unsigned long long culledCount();
void resetCounts();

}
