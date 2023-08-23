#include <iostream>
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int main()
{
    auto L = luaL_newstate();
    std::cout << "Lua version number is " << lua_version(L) << std::endl;
    luaL_openlibs(L);
    if (luaL_loadfile(L, "../script.lua") || lua_pcall(L, 0, 0, 0)) {
        std::cout << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    lua_close(L);
    return 0;
}
