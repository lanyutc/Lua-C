#ifndef _LUA_C_H_
#define _LUA_C_H_

#define BOOT_OK     "\e[1m\e[32m[ ok ]\e[m"
#define BOOT_FAIL   "\e[1m\e[31m[ failed ]\e[m"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

extern lua_State* s_lua;
bool init_lua();
bool final_lua();
void load_lua_files();
void regist_func_to_lua();
bool load_lua_file(const char* lua_file);

int proc_add_operation(int a, int b);
bool proc_check_value(int a);
int proc_runtime_changes(int a); 
#endif
