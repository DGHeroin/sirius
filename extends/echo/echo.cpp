#include "echo.h"

#define LOG_TAG "ext echo"

int ext_echo(lua_State* L){
    log_info("enter ext echo");
    return 0;
}

lua_module_register(echo, ext_echo)
