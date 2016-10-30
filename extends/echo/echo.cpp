#include "echo.h"

#define LOG_TAG "ext echo"

extern "C"{
int __declspec(dllexport) luaopen_echo (lua_State* L){
    log_info("enter ext echo");
    return 0;
}
}
