#include <Geode/Geode.hpp>
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <sol/sol.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <SerpentLua.hpp>

sol::state SerpentLua::lua = {};

using namespace geode::prelude;

void createLib(sol::state& lua) {
	lua.set_function("createPopup", [](const std::string& name, const std::string& desc, const std::string& btn) {
		log::info("{}", name);
		log::info("{}", desc);
		log::info("{}", btn);
		FLAlertLayer::create(name.c_str(), desc, btn.c_str())->show();
	});
}

$execute {
	log::info("SerpentLua Loaded!");
	SerpentLua::lua.open_libraries(sol::lib::base);
	SerpentLua::bindings::cocos::bind(SerpentLua::lua);
	SerpentLua::bindings::_geode::enums(SerpentLua::lua);
	SerpentLua::bindings::_geode::bind(SerpentLua::lua);
}

class $modify(MyMenuLayer, MenuLayer) {
	/*
	bool init() {
		if (!MenuLayer::init()) return false;
		SerpentLua::lua.script(R"(
local node = CCNode.create()

node:setID("lua-node-awesome")

CCScene.get():addChild(node)
			)");
		return true;
	}
		*/
	void onMoreGames(CCObject*) {
		SerpentLua::lua.script(R"(
local n = Notification.show("HELLOOOOOOOOOOOOOOO")

n:show()

createQuickPopup(
	"TITLE",
	"DESCRIPTION",
	"HIII", "Hooo!",
	function(layer, pressed)
		if pressed then
			print("PRESSED HIII")
		else
			print("PRESSED Hooo!")
		end
	end
)
		)");
	}
};