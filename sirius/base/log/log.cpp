#include <base/log/log.h>
#include <stdarg.h>
#include <stdio.h>

#include <base/time/time.h>

#include <iostream>
using namespace std;

void log_vprint(int priority, char* tag, char* fmt, ...){
    const size_t buff_sz = 64*1024;
    char buffer[buff_sz]={0};
    size_t offset = 0;
    Date date;
    datetime_local (&date);
    offset += sprintf_s (buffer, buff_sz - offset, "%d-%d-%d %2d:%2d:%2d.%3d",
                         date.year, date.month, date.day,
                         date.hour, date.minute, date.second, date.milliseconds);

    const char priority_tag[]={'v', 'd', 'i', 'w', 'e', 'a', 'f'};

    offset += sprintf_s ( &buffer[0] + offset, buff_sz - offset, " %c [%s] ", priority_tag[priority], tag);

    va_list ap;
    int retval;
    va_start(ap, fmt);
    retval = vsprintf_s (buffer + offset, buff_sz - offset, fmt, ap);
    va_end(ap);

    cout << buffer << endl;
}
