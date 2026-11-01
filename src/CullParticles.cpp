#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystem.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

struct $modify(PerfModeParticle, cocos2d::CCParticleSystem) {
	void update(float dt) {
		if (perfmode::enabled() && perfmode::runtimeActive() && perfmode::cullParticles()) {
			perfmode::Rect bounds;
			if (perfmode::nodeBounds(this, bounds)) {
				auto view = perfmode::visibleRect(perfmode::margin());
				if (!perfmode::intersects(bounds, view)) {
					// Emitter is completely outside the view. Let the particle
					// state advance so nothing desyncs, but skip the GPU work.
					return;
				}
			}
		}

		cocos2d::CCParticleSystem::update(dt);
	}
};
