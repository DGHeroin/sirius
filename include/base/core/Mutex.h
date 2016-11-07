#ifndef _mutex_h_
#define _mutex_h_

#include <base/macros.h>

class Mutex;
Mutex* Mutex_create();
void Mutex_destory(Mutex*);

class AutoMutex{
public:
    AutoMutex(Mutex* mutex);
    ~AutoMutex();
private:
    Mutex* mMutex;
};

#endif
