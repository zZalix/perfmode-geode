#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

namespace {

// Nodes this mod hid on a previous pass, so they can be restored as soon as
// they come back into view or the mod is switched off.
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
			if (!child->isVisible()) {
				child->setVisible(true);
			}
			continue;
		}

		st.culled++;
		if (child->isVisible()) {
			child->setVisible(false);
			g_hidden.emplace_back(child);
		}
	}
}

}

struct $modify(PerfModePlayLayer, PlayLayer) {
	void updateVisibility(float dt) {
		PlayLayer::updateVisibility(dt);

		if (!perfmode::enabled() || !perfmode::runtimeActive() || !perfmode::cullObjects()) {
			restoreAll();
			return;
		}

		auto& st = perfmode::stats();
		st.drawn = 0;
		st.culled = 0;

		// Rebuild the hidden list each pass: only nodes hidden by us are ever
		// restored, and nodes the game hid itself are never touched.
		auto previous = std::move(g_hidden);
		g_hidden.clear();

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
