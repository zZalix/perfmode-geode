#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

namespace {

std::vector<WeakRef<cocos2d::CCNode>> g_hidden;

void restoreAll() {
	for (auto& ref : g_hidden) {
		if (auto node = ref.lock()) {
			node->setVisible(true);
		}
	}
	g_hidden.clear();
}

void cullChildren(cocos2d::CCNode* parent, perfmode::Rect const& view) {
	if (!parent) {
		return;
	}

	for (auto child : parent->getChildrenExt()) {
		auto obj = geode::cast::typeinfo_cast<GameObject*>(child);
		if (!obj || perfmode::mustSkip(obj)) {
			continue;
		}

		perfmode::Rect bounds;
		if (!perfmode::worldBounds(obj, bounds)) {
			continue;
		}

		if (perfmode::intersects(bounds, view)) {
			continue;
		}

		if (!obj->isVisible()) {
			continue;
		}

		obj->setVisible(false);
		g_hidden.emplace_back(obj);
	}
}

}

struct $modify(PerfModePlayLayer, PlayLayer) {
	void updateVisibility(float dt) {
		// The game's own visibility pass runs first. Permission objects,
		// gameplay elements and everything gameplay-driven keeps exactly the
		// visibility the game assigned this tick.
		PlayLayer::updateVisibility(dt);

		if (!perfmode::enabled() || !perfmode::runtimeActive() || !perfmode::cullObjects()) {
			restoreAll();
			return;
		}

		// Restore what we hid before the game's pass, so the current pass
		// sees every object candidate again. Objects that re-enter the view
		// are shown by the game itself from here on.
		restoreAll();

		auto view = perfmode::visibleRect(perfmode::margin());

		cullChildren(m_objectLayer, view);
		cullChildren(m_inShaderObjectLayer, view);
		cullChildren(m_aboveShaderObjectLayer, view);
	}

	void onExit() {
		restoreAll();
		PlayLayer::onExit();
	}
};
