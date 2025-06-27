#include "api.h"

lua_State* Lua::L = NULL;
void Lua::Execute(const char* code) {
	luaL_openlibs(L);
	if (luaL_dostring(L, code) != LUA_OK) {
		const char* err = lua_tostring(L, -1);
		lua_pop(L, 1);
	}
}