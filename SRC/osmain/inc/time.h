#ifndef _TIME_H
#define _TIME_H

#include <inc/types.h>
#include <inc/nasmfuc.h>

struct tm 
{
    int tm_sec;         /* 秒 – 取值区间为[0,59] */
    int tm_min;         /* 分 - 取值区间为[0,59] */
    int tm_hour;        /* 时 - 取值区间为[0,23] */
    int tm_mday;        /* 一个月中的日期 - 取值区间为[1,31] */
    int tm_mon;         /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
    int tm_year;        /* 年份，其值等于实际年份减去1900 */
    int tm_wday;        /* 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一 */
    int tm_yday;        /* 从每年1月1日开始的天数– 取值区间[0,365]，其中0代表1月1日 */
    int tm_isdst;       /* 夏令时标识符，夏令时tm_isdst为正；不实行夏令时tm_isdst为0 */    
};

typedef	long long time_t;		/* <time> type */

size_t mktime(struct tm tm_now);
void gmtime(struct tm *tm_time, size_t timestamp);

#endif