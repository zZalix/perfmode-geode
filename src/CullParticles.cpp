#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

struct $modify(PerfModeParticle, cocos2d::CCParticleSystemQuad) {
	void draw() {
		auto const& cfg = perfmode::settings();

		if (cfg.enabled && perfmode::runtimeActive() && cfg.cullParticles) {
			perfmode::Rect bounds;
			// Fast box first; only cocos calls here, no atomics beyond a
			// cached settings read.
			if (perfmode::fastBounds(this, bounds)) {
				auto view = perfmode::visibleRect(cfg.margin);
				if (!perfmode::intersects(bounds, view)) {
					perfmode::Rect exact;
					if (perfmode::worldBounds(this, exact) && !perfmode::intersects(exact, view)) {
						return;
					}
				}
			}
		}

		cocos2d::CCParticleSystemQuad::draw();
	}
};
