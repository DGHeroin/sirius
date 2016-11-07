#include <base/thread/thread.h>

#define LOG_TAG "Thread"

// funcs
typedef struct ThreadContext ThreadContext;
ThreadContext* ThreadContext_create();
void ThreadContext_destroy(ThreadContext*);
void ThreadContext_run(ThreadContext*, ThreadCallback, void* args);
void ThreadContext_join(ThreadContext*);
void ThreadContent_Sleep(uint32_t milliseconds);

#ifdef _WIN32
#include <windows.h>
struct ThreadContext{
    HANDLE mThread;
};

DWORD WINAPI ThreadFunc(void* data){
    return 0;
}

ThreadContext* ThreadContext_create(){
    ThreadContext* ctx = (ThreadContext*)calloc (1, sizeof(ThreadContext));
    if(!ctx){
        log_error("ThreadContext Alloc Memory failed.");
        return NULL;
    }
    return ctx;
}

void ThreadContext_run(ThreadContext*ctx, ThreadCallback callback, void* args){
    typedef DWORD (*WIN_ThreadCallback)(void*);
    ctx->mThread = CreateThread (NULL, 0, (WIN_ThreadCallback)callback, args, 0, NULL);
    if(ctx->mThread == NULL){
        log_error("ThreadContext Create Thread failed.");
        return;
    }
}

void ThreadContext_join(ThreadContext*ctx){
    WaitForSingleObject (ctx->mThread, INFINITE);
}

void ThreadContext_destroy(ThreadContext *ctx){
    if(ctx){
        ctx->mThread = NULL;
        free(ctx);
    }
}

void ThreadContent_Sleep(uint32_t milliseconds){
    Sleep (milliseconds);
}

#else

#endif



Thread::Thread() :
    mIsRunning(false)
{
    this->mCtx = ThreadContext_create();
}

Thread::~Thread (){
    ThreadContext_destroy(this->mCtx);
    this->mCtx = NULL;
}

void Thread::join (){
    ThreadContext_join(mCtx);
}

void Thread::Sleep (uint32_t milliseconds){
    ThreadContent_Sleep (milliseconds);
}

void Thread::run (ThreadCallback callback, void* args){
    mIsRunning = true;
    ThreadContext_run (mCtx, callback, args);
    mIsRunning = false;
}
