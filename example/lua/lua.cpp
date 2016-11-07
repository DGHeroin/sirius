#include <lua/lua.h>

#define LOG_TAG "example lua"
int lua_main(int argc, char** argv){
    const char* lua_file = argv[argc-1];
    log_info("lua_file:%s", lua_file);
    lua_app_start(lua_file);

    return 0;
}

