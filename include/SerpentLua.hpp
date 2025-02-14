// main include

#include <Geode/Geode.hpp>
#include <sol/sol.hpp>

namespace SerpentLua {
    extern sol::state lua;
    namespace bindings {
        struct _geode {
            static void bind(sol::state& lua);
            static void enums(sol::state& lua);
        };

        struct cocos {
            static void bind(sol::state& lua);
            static void enums(sol::state& lua);
        };
    }
}