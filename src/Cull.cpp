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

bool nodeBounds(cocos2d::CCNode* node, Rect& out) {
	if (!node) {
		return false;
	}

	auto const& size = node->getContentSize();
	auto const& pos = node->getPosition();

	// Sprites report their own scaled size; plain nodes report content size.
	float halfW = size.width * 0.5f;
	float halfH = size.height * 0.5f;

	auto scaleX = std::abs(node->getScaleX());
	auto scaleY = std::abs(node->getScaleY());

	halfW *= scaleX > 0.f ? scaleX : 1.f;
	halfH *= scaleY > 0.f ? scaleY : 1.f;

	out = Rect{
		pos.x - halfW,
		pos.y - halfH,
		pos.x + halfW,
		pos.y + halfH
	};

	return true;
}

}
