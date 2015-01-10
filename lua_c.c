#include "lua_c.h"
#include <stdlib.h>

lua_State* s_lua;


int proc_add_operation(int a, int b)
{
	lua_settop(s_lua, -1);
	lua_getglobal(s_lua, "test_func_add");
	lua_pushnumber(s_lua, a);
	lua_pushnumber(s_lua, b);
	int val = lua_pcall(s_lua, 2, 1, 0);
	if (val) {
		printf("lua_pcall_error %d\n", val);
	}
	return (int)lua_tonumber(s_lua, -1);
}

#define target 300
static int l_test_check_value(lua_State * l)
{
	int num = lua_tointeger(l, -1);
	bool check = (num == target);
	lua_pushboolean(l, check);
	return 1;
}

bool proc_check_value(int a)
{
	lua_settop(s_lua, -1);
	lua_getglobal(s_lua, "test_func_check");
	lua_pushnumber(s_lua, a);
	int val = lua_pcall(s_lua, 1, 1, 0);
	if (val) {
		printf("lua_pcall_error %d\n", val);
	}
	return (bool)lua_toboolean(s_lua, -1);
}

#define add 100
static int l_test_runtime_changes(lua_State * l)
{
	int num = lua_tointeger(l, -1);
	num += add;
	lua_pushnumber(l, num);
	return 1;
}

int proc_runtime_changes(int a)
{
	lua_settop(s_lua, -1);
	lua_getglobal(s_lua, "test_func_runtime_changes");
	lua_pushnumber(s_lua, a);
	int val = lua_pcall(s_lua, 1, 1, 0);
	if (val) {
		printf("lua_pcall_error %d\n", val);
	}
	return (int)lua_tonumber(s_lua, -1);
}

bool init_lua()
{
	s_lua = luaL_newstate();
	if (!s_lua) {
		printf("luaL_newstate failed!\n");
		exit(-1);
	}
	luaL_openlibs(s_lua);
	return true;
}

bool final_lua()
{
	lua_close(s_lua);
	return true;
}

void regist_func_to_lua()
{
	lua_register(s_lua, "test_check_value", l_test_check_value);
	lua_register(s_lua, "test_runtime_changes", l_test_runtime_changes);
}

bool load_lua_file(const char* lua_file)
{
	if (luaL_dofile(s_lua, lua_file) != 0) {
		printf("LOAD LUA %s %s\n", lua_file, BOOT_FAIL);
		return false;
	}
	printf("LOAD LUA %s %s\n", lua_file, BOOT_OK);
	return true;
}

void load_lua_files()
{
	if (!load_lua_file("./implement_one.lua")) {
		exit(-1);
	}

	if (!load_lua_file("./implement_two.lua")) {
		exit(-1);
	}
}
