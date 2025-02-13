// main include

#include <Geode/Geode.hpp>

namespace SerpentLua {
    namespace bindings {
        struct _geode {
            static void bind(sol::state lua);
            static void enums(sol::state lua);
        };
    }
}