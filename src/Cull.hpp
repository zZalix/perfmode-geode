#pragma once

#include <Geode/Geode.hpp>

namespace perfmode {

struct Rect {
	float left;
	float bottom;
	float right;
	float top;
};

// The rectangle currently visible, in world coordinates, expanded by margin.
Rect visibleRect(float margin);

bool intersects(Rect const& a, Rect const& b);

// World-space bounding box of a node using its full transform chain
// (position, scale, rotation, anchor, camera). Handles nested batch nodes and
// children so platformer levels and moving groups cull correctly.
bool worldBounds(cocos2d::CCNode* node, Rect& out);

// True for trigger/spawn/logic-only objects that must never be touched, plus
// the player.
bool mustSkip(GameObject* obj);

}
