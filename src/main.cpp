#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

namespace {

bool g_active = true;

}

$on_mod(Loaded) {
	g_active = Mod::get()->getSettingValue<bool>("enabled");

	listenForKeybindSettingPresses("kill-switch", [](Keybind const&, bool down, bool, double) {
		if (!down) {
			return;
		}

		g_active = !g_active;

		Notification::create(
			g_active ? "Perf Mode on" : "Perf Mode off",
			g_active ? NotificationIcon::Success : NotificationIcon::Info
		)->show();
	});
}
