#ifndef _log_h_
#define _log_h_

#include <base/macros.h>

enum LOG{
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_ASSERT,
    LOG_IF
};

void log_vprint(int priority, char* tag, char* fmt, ...);

#define logger(priority, tag, ...) \
    log_vprint(priority, tag, ##__VA_ARGS__)

#define log_verbose(...)      logger(LOG_VERBOSE, LOG_TAG, ##__VA_ARGS__)
#define log_debug(...)        logger(LOG_DEBUG, LOG_TAG, ##__VA_ARGS__)
#define log_info(...)         logger(LOG_INFO, LOG_TAG, ##__VA_ARGS__)
#define log_warn(...)         logger(LOG_WARN, LOG_TAG, ##__VA_ARGS__)
#define log_error(...)        logger(LOG_ERROR, LOG_TAG, ##__VA_ARGS__)
#define log_assert(cond, ...) do{ if(!(cond)){logger(LOG_ASSERT, LOG_TAG, ##__VA_ARGS__);assert((cond));}}while(0)
#define log_if(cond, ...) do{if((cond))logger(LOG_IF, LOG_TAG, ##__VA_ARGS__);}while(0)

#endif // _log_h_
