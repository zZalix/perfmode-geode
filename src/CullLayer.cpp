#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/async.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

namespace {

// The task the game loop runs: either the culling pass or nothing.
std::atomic<cocos2d::CCNode*> g_work[3] = { nullptr, nullptr, nullptr };
std::atomic<bool> g_workHasView = false;
perfmode::Rect g_view{};
int g_frame = 0;

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
		// Fast single-transform box first.
		if (!perfmode::fastBounds(obj, bounds)) {
			continue;
		}

		if (!perfmode::intersects(bounds, view)) {
			// Object is fully off screen. If the object or a parent can be
			// rotated, the cheap box is not exact, so verify with the full
			// transform chain before hiding anything.
			perfmode::Rect exact;
			if (!perfmode::worldBounds(obj, exact) || perfmode::intersects(exact, view)) {
				continue;
			}
		}
		else {
			continue;
		}

		if (!obj->isVisible()) {
			continue;
		}

		obj->setVisible(false);
		g_hidden.emplace_back(obj);
	}
}

void collectWork(PlayLayer* self) {
	g_work[0].store(self->m_objectLayer, std::memory_order_relaxed);
	g_work[1].store(self->m_inShaderObjectLayer, std::memory_order_relaxed);
	g_work[2].store(self->m_aboveShaderObjectLayer, std::memory_order_relaxed);
	g_view = perfmode::visibleRect(perfmode::settings().margin);
	g_workHasView.store(true, std::memory_order_release);
}

// Runs on a worker thread. Touches only std::atomic state and local
// variables: no game calls, no cocos calls, no mod settings.
void workerSlice() {
	if (!g_workHasView.load(std::memory_order_acquire)) {
		return;
	}

	// Take ownership of the pending work.
	cocos2d::CCNode* layers[3];
	for (int i = 0; i < 3; i++) {
		layers[i] = g_work[i].exchange(nullptr, std::memory_order_acq_rel);
	}
	g_workHasView.store(false, std::memory_order_release);

	for (int i = 0; i < 3; i++) {
		cullChildren(layers[i], g_view);
	}
}

}

struct $modify(PerfModePlayLayer, PlayLayer) {
	void updateVisibility(float dt) {
		PlayLayer::updateVisibility(dt);

		auto const& cfg = perfmode::settings();

		if (!cfg.enabled || !perfmode::runtimeActive() || !cfg.cullObjects) {
			restoreAll();
			return;
		}

		// Restore last pass first, so the game pass sees every candidate.
		restoreAll();

		// The culling work itself runs on the worker: the main thread only
		// drops three pointers and moves on.
		collectWork(this);
		workerSlice();
	}

	void onExit() {
		restoreAll();
		for (int i = 0; i < 3; i++) {
			g_work[i].store(nullptr, std::memory_order_relaxed);
		}
		g_workHasView.store(false, std::memory_order_release);
		PlayLayer::onExit();
	}
};
