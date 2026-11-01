#pragma once

#include <Geode/Geode.hpp>

namespace perfmode {

struct Rect {
	float left;
	float bottom;
	float right;
	float top;
};

// Visible rectangle in world coordinates, expanded by margin.
Rect visibleRect(float margin);

bool intersects(Rect const& a, Rect const& b);

// Full world-space box via the whole transform chain. Accurate but costs 4
// matrix transforms: only used when the node or its parent is rotated.
bool worldBounds(cocos2d::CCNode* node, Rect& out);

// Cheap box: single transform for the center plus scaled extents. Used for
// the common case (no rotation anywhere), roughly 4x cheaper.
bool fastBounds(cocos2d::CCNode* node, Rect& out);

// True for the player, triggers and zero-size objects: never touched.
bool mustSkip(GameObject* obj);

}
