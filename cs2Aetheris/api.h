#pragma once
#include "lua/lua.hpp"

namespace Lua {
	extern lua_State* L;
	extern void Execute(const char* code);
}