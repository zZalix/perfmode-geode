#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

#include "Stats.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	perfmode::refreshSettings();
	perfmode::setRuntimeActive(perfmode::settings().enabled);

	// Cache the settings so the hot path never touches the settings store.
	listenForSettingChanges<bool>("enabled", [](bool) {
		perfmode::refreshSettings();
	});
	listenForSettingChanges<bool>("cull-offscreen", [](bool) {
		perfmode::refreshSettings();
	});
	listenForSettingChanges<bool>("skip-particles", [](bool) {
		perfmode::refreshSettings();
	});
	listenForSettingChanges<int64_t>("cull-margin", [](int64_t) {
		perfmode::refreshSettings();
	});

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
