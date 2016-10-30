#include <lua/lua.h>
#include <base/log/log.h>
#include <base/core/File.h>

#define LOG_TAG "sirius lua"

struct RegisterItem{
    const char* func_name;
    lua_CFunction func;
};
static int cfunc_log_verbose(lua_State* L){
    const char* msg = luaL_checkstring(L, 1);
    log_verbose("%s", msg);
    return 0;
}
static int cfunc_log_debug(lua_State* L){
    const char* msg = luaL_checkstring(L, 1);
    log_debug("%s", msg);
    return 0;
}
static int cfunc_log_info(lua_State* L){
    const char* msg = luaL_checkstring(L, 1);
    log_info("%s", msg);
    return 0;
}
static int cfunc_log_warn(lua_State* L){
    const char* msg = luaL_checkstring(L, 1);
    log_warn("%s", msg);
    return 0;
}
static int cfunc_log_error(lua_State* L){
    const char* msg = luaL_checkstring(L, 1);
    log_error("%s", msg);
    return 0;
}
static int cfunc_log_assert(lua_State* L){
    int cond = (int)luaL_checknumber (L, 1);
    const char* msg = luaL_checkstring(L, 2);
    log_assert(cond, "%s", msg);
    return 0;
}
static int cfunc_log_if(lua_State* L){
    int cond = (int)luaL_checknumber (L, 1);
    const char* msg = luaL_checkstring(L, 2);
    log_if(cond, "%s", msg);
    return 0;
}

struct RegisterItem RegisterList[] = {
{"log_verbose", cfunc_log_verbose},
{"log_debug",   cfunc_log_debug},
{"log_info",    cfunc_log_info},
{"log_warn",    cfunc_log_warn},
{"log_error",   cfunc_log_error},
{"log_assert",  cfunc_log_assert},
{"log_if",      cfunc_log_if},
    {NULL, NULL}
};


void lua_register_func(lua_State*L){
    for(int i=0;RegisterList[i].func_name != NULL; i++){
        struct RegisterItem* item = &RegisterList[i];
        lua_register(L, item->func_name, item->func );
    }
}


int lua_app_start(const char* file){
    if(!file_exist (file)){
        log_error("file not exist!");
        return -1;
    }

    std::string subfix = file_subfix (file);
    if(subfix != ".lua"){
        log_error("need a lua file");
        return -1;
    }
    log_debug("run lua file:%s", file);
    lua_State* L;
    L = luaL_newstate ();
    luaL_openlibs (L);
    lua_register_func(L);

    int run_status = luaL_dofile(L, file);
    const char* err_str = lua_tostring(L, -1);
    int result = 0;
    if (err_str == NULL){
        log_info("Lua status(%d) ok.", run_status);
        result = -1;
    } else {
        log_info("Lua status(%d) error. Messages:%s", run_status, err_str);
        result = 0;
    }

    lua_close (L);
    return 0;
}

int addme(lua_State*lua, int status){
    log_info("endter lua");
    return 1;
}
