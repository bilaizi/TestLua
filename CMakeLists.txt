cmake_minimum_required(VERSION 3.25)
project (TestLua)  # project here actually means solution in premake

set(LUA_VERSION 5.4.6)

if(WIN32)
    add_definitions("-DLUA_BUILD_AS_DLL")
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
endif(WIN32)

aux_source_directory(lua-5.4.6/src LUA_SOURCES)
list(REMOVE_ITEM LUA_SOURCES "lua-5.4.6/src/lua.c" "lua-5.4.6/src/luac.c")

set(LUA_LIBRARY lua${LUA_VERSION})
add_library(${LUA_LIBRARY} SHARED ${LUA_SOURCES})

add_executable(lua lua-5.4.6/src/lua.c)
target_link_libraries(lua ${LUA_LIBRARY})
if(UNIX AND NOT APPLE) #add math library for linux
    target_link_libraries(lua m)
endif()

add_executable(luac ${LUA_SOURCES} lua-5.4.6/src/luac.c)
if(UNIX AND NOT APPLE)
    target_link_libraries(luac m)
endif()

include_directories(lua-5.4.6/src)
add_executable (TestLua main.cpp)
target_link_libraries (TestLua ${LUA_LIBRARY})
if(UNIX AND NOT APPLE) #add math library for linux
    target_link_libraries(TestLua m)
endif()
