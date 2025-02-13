#include <Geode/Geode.hpp>
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <sol/sol.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

void createLib(sol::state& lua) {
	lua.set_function("createPopup", [](const std::string& name, const std::string& desc, const std::string& btn) {
		log::info("{}", name);
		log::info("{}", desc);
		log::info("{}", btn);
		FLAlertLayer::create(name.c_str(), desc, btn.c_str())->show();
	});
}


class $modify(MyMenuLayer, MenuLayer) {
struct Fields {
	sol::state lua;
};
	bool init() {
		if (!MenuLayer::init()) return false;
		m_fields->lua.open_libraries(sol::lib::base);

		createLib(m_fields->lua);

		return true;
	}
	void onMoreGames(CCObject*) {
		m_fields->lua.script(R"(
createPopup("hello", "lib", "ok")
		)");
	}
};