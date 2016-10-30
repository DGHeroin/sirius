#include <base/log/log.h>

#define LOG_TAG "Echo server"
int echo_main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    log_verbose("hello %s", "world!");
    log_info("hello %s", "world!");
    log_warn("hello %s", "world!");
    log_debug("hello %s", "world!");
    log_error("hello %s", "world!");
    //log_assert(!"not ok", "hello %s", "world!");

    log_if(0, "hello %s", "world!");
    log_if(1, "hello %s", "world!");

    return 0;
}

