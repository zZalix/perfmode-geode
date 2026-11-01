#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

struct $modify(PerfModeParticle, cocos2d::CCParticleSystemQuad) {
	void draw() {
		if (perfmode::enabled() && perfmode::runtimeActive() && perfmode::cullParticles()) {
			perfmode::Rect bounds;
			if (perfmode::worldBounds(this, bounds)) {
				auto view = perfmode::visibleRect(perfmode::margin());
				if (!perfmode::intersects(bounds, view)) {
					return;
				}
			}
		}

		cocos2d::CCParticleSystemQuad::draw();
	}
};
