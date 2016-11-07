#include <base/thread/thread.h>

#define LOG_TAG "example thread"
#include <iostream>
using namespace std;

int32_t CustomThread(void* args){
    log_info("run...");
    int* value = (int*) args;
    int i=*value;
    while(i++ != 5+*value){
        log_info("thread run: %d", i);
        Thread::Sleep (1000);
    }
    log_info("end");
    return 0;
}

int thread_main(int argc, char** argv){
    Thread th1;
    int value1 = 1;
    th1.run (CustomThread, &value1);

    Thread th2;
    int value2 = 100;
    th2.run (CustomThread, &value2);

    th1.join ();
    th2.join ();
    return 0;
}

