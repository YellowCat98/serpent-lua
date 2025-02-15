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

$execute {
	log::info("SerpentLua Loaded!");
	SerpentLua::lua.open_libraries(sol::lib::base);

	SerpentLua::bindings::robtop::bind(SerpentLua::lua);
	SerpentLua::bindings::cocos::enums(SerpentLua::lua);
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
local n = Notification.create("HELLOOOOOOOOOOOOOOO")

n:show()

createQuickPopup(
	"Do YOU Want to USE the CUBE NUMBer of the ONE Next to YOUR current One???????????????",
	"DESCRIPTION",
	"Yes.", "no.",
	function(layer, btn2)
		if not btn2 then
			GameManager.get():setPlayerFrame(GameManager.get():m_playerFrame + 1)
		else
			FLAlertLayer.create("OK.", "I did NOT sET cube TO CUBE 484...............................", "thanks"):show()
		end
	end
)
		)");
	}
};