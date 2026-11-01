#include "Cull.hpp"

namespace perfmode {

Rect visibleRect(float margin) {
	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

	return Rect{
		0.f - margin,
		0.f - margin,
		winSize.width + margin,
		winSize.height + margin
	};
}

bool intersects(Rect const& a, Rect const& b) {
	if (a.right < b.left) return false;
	if (a.left > b.right) return false;
	if (a.top < b.bottom) return false;
	if (a.bottom > b.top) return false;
	return true;
}

bool worldBounds(cocos2d::CCNode* node, Rect& out) {
	if (!node) {
		return false;
	}

	auto const& size = node->getContentSize();
	if (size.width <= 0.f || size.height <= 0.f) {
		return false;
	}

	// Four corners of the local box, mapped through the full transform chain
	// so scale, rotation, anchor and camera offsets are all accounted for.
	cocos2d::CCPoint corners[4] = {
		node->convertToWorldSpace(cocos2d::CCPoint(0.f, 0.f)),
		node->convertToWorldSpace(cocos2d::CCPoint(size.width, 0.f)),
		node->convertToWorldSpace(cocos2d::CCPoint(0.f, size.height)),
		node->convertToWorldSpace(cocos2d::CCPoint(size.width, size.height))
	};

	out = Rect{ corners[0].x, corners[0].y, corners[0].x, corners[0].y };
	for (int i = 1; i < 4; i++) {
		if (corners[i].x < out.left) out.left = corners[i].x;
		if (corners[i].x > out.right) out.right = corners[i].x;
		if (corners[i].y < out.bottom) out.bottom = corners[i].y;
		if (corners[i].y > out.top) out.top = corners[i].y;
	}

	return true;
}

bool mustSkip(GameObject* obj) {
	if (!obj) {
		return true;
	}

	// Player ships, waves and every dual are drawn through player systems.
	if (geode::cast::typeinfo_cast<PlayerObject*>(obj)) {
		return true;
	}

	// Never touch triggers, spawners or lock guides: they carry no visual
	// cost worth culling and some drive gameplay state.
	if (obj->m_isTrigger) {
		return true;
	}

	// Zero-size or textureless objects cost nothing to draw.
	auto const& size = obj->getContentSize();
	if (size.width <= 0.f || size.height <= 0.f) {
		return true;
	}

	return false;
}

}
