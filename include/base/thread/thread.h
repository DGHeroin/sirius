#ifndef _thread_h_
#define _thread_h_

#include <base/macros.h>

struct ThreadContext;
typedef int32_t (*ThreadCallback)(void* args);
class Thread{
public:
    void run(ThreadCallback callback, void* args);
public:
    static void Sleep(uint32_t milliseconds);
public:
    Thread();
    ~Thread();
    void join();
private:
    bool mIsRunning;
    struct ThreadContext* mCtx;
};


#endif // _thread_h_
