#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

namespace {

void cullChildren(cocos2d::CCNode* parent, float margin) {
	if (!parent) {
		return;
	}

	auto view = perfmode::visibleRect(margin);
	auto& st = perfmode::stats();

	for (auto child : parent->getChildrenExt()) {
		if (!geode::cast::typeinfo_cast<GameObject*>(child)) {
			continue;
		}

		perfmode::Rect bounds;
		if (!perfmode::nodeBounds(child, bounds)) {
			continue;
		}

		if (perfmode::intersects(bounds, view)) {
			st.drawn++;
			continue;
		}

		st.culled++;
		child->setVisible(false);
	}
}

}

struct $modify(PerfModePlayLayer, PlayLayer) {
	void updateVisibility(float dt) {
		PlayLayer::updateVisibility(dt);

		if (!perfmode::enabled() || !perfmode::runtimeActive() || !perfmode::cullObjects()) {
			return;
		}

		auto& st = perfmode::stats();
		st.drawn = 0;
		st.culled = 0;

		auto margin = perfmode::margin();

		cullChildren(m_objectLayer, margin);
		cullChildren(m_inShaderObjectLayer, margin);
		cullChildren(m_aboveShaderObjectLayer, margin);
	}
};
