#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

#include "Stats.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	perfmode::setRuntimeActive(Mod::get()->getSettingValue<bool>("enabled"));

	listenForKeybindSettingPresses("kill-switch", [](Keybind const&, bool down, bool, double) {
		if (!down) {
			return;
		}

		bool next = !perfmode::runtimeActive();
		perfmode::setRuntimeActive(next);

		Notification::create(
			next ? "Perf Mode on" : "Perf Mode off",
			next ? NotificationIcon::Success : NotificationIcon::Info
		)->show();
	});
}
