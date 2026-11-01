#pragma once

#include <Geode/Geode.hpp>

namespace perfmode {

struct Rect {
	float left;
	float bottom;
	float right;
	float top;
};

// Returns the rectangle currently visible on screen, in the coordinate space
// used by the layer that is being traversed.
Rect visibleRect(float margin);

bool intersects(Rect const& a, Rect const& b);

// Screen-space bounds of a node, expanded by its scale.
bool nodeBounds(cocos2d::CCNode* node, Rect& out);

}
