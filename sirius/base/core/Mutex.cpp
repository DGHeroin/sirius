#include <base/core/Mutex.h>

#define LOG_TAG "Mutex"

Mutex* Mutex_create();
void Mutex_destory(Mutex*);

// func
#ifdef _WIN32

#include <Windows.h>

class Mutex{
public:
    Mutex(){
        mMutex = CreateMutex(NULL, FALSE, NULL);
        log_assert(mMutex != NULL, "Mutex Create failed.");
    }
    void lock(){
        WaitForSingleObject(this->mMutex, INFINITE);
    }
    void unlock(){
        ReleaseMutex (this->mMutex);
    }

    ~Mutex(){
        CloseHandle (this->mMutex);
    }

    HANDLE mMutex;
};

Mutex* Mutex_create(){
    Mutex* mtx = new Mutex;
    return mtx;
}

void Mutex_destory(Mutex* mtx){
    delete mtx;
}
#else

#endif

AutoMutex::AutoMutex(Mutex *mutex){
    this->mMutex = mutex;
    this->mMutex->lock ();
}

AutoMutex::~AutoMutex (){
    this->mMutex->unlock ();
}
