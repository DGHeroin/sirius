#ifndef _lua_h_
#define _lua_h_

#include "lua/lua.hpp"
#include <base/macros.h>
int lua_app_start(const char* file);

#define lua_module_register(module_name, callback) \
extern "C"{ \
    int __declspec(dllexport) luaopen_##module_name (lua_State* L){ \
        return callback(L); \
    } \
}


#endif
