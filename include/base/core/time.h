#ifndef _time_h_
#define _time_h_

#include <base/macros.h>

typedef
struct stDate{
    uint16_t year;
    uint16_t month;
    uint16_t day;

    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    uint16_t milliseconds;
}Date;

void datetime_local(Date* date);


#endif // _time_h_
