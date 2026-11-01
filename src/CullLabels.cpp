#include <Geode/Geode.hpp>
#include <Geode/modify/LabelGameObject.hpp>

#include "Cull.hpp"
#include "Stats.hpp"

using namespace geode::prelude;

struct $modify(PerfModeLabel, LabelGameObject) {
	void draw() {
		if (perfmode::enabled() && perfmode::runtimeActive() && perfmode::cullLabels()) {
			perfmode::Rect bounds;
			if (perfmode::nodeBounds(this, bounds)) {
				auto view = perfmode::visibleRect(perfmode::margin());
				if (!perfmode::intersects(bounds, view)) {
					return;
				}
			}
		}

		LabelGameObject::draw();
	}
};
