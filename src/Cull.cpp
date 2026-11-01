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

namespace {

bool chainHasRotation(cocos2d::CCNode* node) {
	for (auto* cur = node; cur; cur = cur->getParent()) {
		if (cur->getRotation() != 0.f || cur->getRotationX() != 0.f || cur->getRotationY() != 0.f) {
			return true;
		}
	}
	return false;
}

}

bool worldBounds(cocos2d::CCNode* node, Rect& out) {
	if (!node) {
		return false;
	}

	auto const& size = node->getContentSize();
	if (size.width <= 0.f || size.height <= 0.f) {
		return false;
	}

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

bool fastBounds(cocos2d::CCNode* node, Rect& out) {
	if (!node) {
		return false;
	}

	auto const& size = node->getContentSize();
	if (size.width <= 0.f || size.height <= 0.f) {
		return false;
	}

	// One matrix transform for the center, then expand by scaled extents.
	// Exact whenever nothing in the transform chain is rotated.
	auto center = node->convertToWorldSpace(cocos2d::CCPoint(size.width * 0.5f, size.height * 0.5f));

	float halfW = size.width * 0.5f * std::abs(node->getScaleX());
	float halfH = size.height * 0.5f * std::abs(node->getScaleY());

	out = Rect{
		center.x - halfW,
		center.y - halfH,
		center.x + halfW,
		center.y + halfH
	};

	return true;
}

bool mustSkip(GameObject* obj) {
	if (!obj) {
		return true;
	}

	if (geode::cast::typeinfo_cast<PlayerObject*>(obj)) {
		return true;
	}

	if (obj->m_isTrigger) {
		return true;
	}

	auto const& size = obj->getContentSize();
	if (size.width <= 0.f || size.height <= 0.f) {
		return true;
	}

	return false;
}

}
