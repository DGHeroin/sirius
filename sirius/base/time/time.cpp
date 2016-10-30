#include <base/time/time.h>
#include <stdio.h>
#ifdef _WIN32

#include <Windows.h>

static void get_system_datetime(Date* date, int local_time_flag){
    SYSTEMTIME  stUTC;
    if(local_time_flag)
        ::GetSystemTime (&stUTC);
    else
        ::GetLocalTime (&stUTC);
    date->year  = stUTC.wYear;
    date->month = stUTC.wMonth;
    date->day   = stUTC.wDay;
    date->hour  = stUTC.wHour;
    date->minute = stUTC.wMinute;
    date->second = stUTC.wSecond;
    date->milliseconds = stUTC.wMilliseconds;
}

#else


static void get_system_datetime(Date* date, int local_time_flag){
    assert(!"Not Impl yet!");
}

#endif



void datetime_local(Date* date){
    return get_system_datetime(date, 1);
}

void datetime_utc(Date* date){
    return get_system_datetime(date, 0);
}
