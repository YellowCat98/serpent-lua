#include <Geode/Geode.hpp>
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <sol/sol.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	void onMoreGames(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		const char* luaCode = "print('Hello, World')";
		luaL_dostring(L, luaCode);
		lua_close(L);
	}
};