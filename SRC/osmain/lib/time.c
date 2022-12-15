#include <inc/time.h>
#include <inc/lib.h>

size_t mktime(struct tm tm_now)
{
    const unsigned int year0 = tm_now.tm_year+1900;
    const unsigned int mon0 = tm_now.tm_mon+1;
    const unsigned int day = tm_now.tm_mday;
    const unsigned int hour = tm_now.tm_hour;
    const unsigned int min = tm_now.tm_min;
    const unsigned int sec = tm_now.tm_sec;
	unsigned int mon = mon0, year = year0;
 
	/* 1..12 -> 11,12,1..10 */
	if (0 >= (int) (mon -= 2)) {
		mon += 12;	/* Puts Feb last since it has leap day */
		year -= 1;
	}
 
	return ((((unsigned int)
		  (year/4 - year/100 + year/400 + 367*mon/12 + day) +
		  year*365 - 719499
	    )*24 + hour /* now have hours */
	  )*60 + min /* now have minutes */
	)*60 + sec; /* finally seconds */
}

void gmtime(struct tm *tm_time, size_t timestamp){
	unsigned int four_year_num;      // 有多少个四年
    unsigned int one_year_hours;     // 一年的小时数

    const static unsigned char Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const static unsigned int ONE_YEAR_HOURS = 8760;        // 8760 = 365 * 24 (一年的小时数 非闰年)
    const static unsigned int FOUR_YEAR_HOURS = 35064;      // 35064 = (365 * 3 + 366) * 24 (四年的小时数)

    if (timestamp > 0x7FFFFFFF)
    {
        return;
    }
        
    tm_time->tm_isdst = 0;
    tm_time->tm_sec = (int)(timestamp % 60);                // 计算秒
    timestamp /= 60;   
    tm_time->tm_min = (int)(timestamp % 60);                // 计算分
    timestamp /= 60;   
    tm_time->tm_wday = (int)(timestamp/24 + 4) % 7;         // 计算星期 1970年1月1日星期四   
    four_year_num = timestamp / FOUR_YEAR_HOURS;       
    tm_time->tm_year=(four_year_num << 2) + 70;             // 计算年  
    timestamp %= FOUR_YEAR_HOURS;                           // 不足四年的小时数  
    while (1)
    {
        one_year_hours = ONE_YEAR_HOURS;
       
        if ((tm_time->tm_year & 3) == 0)                    // 判断闰年
        {
            one_year_hours += 24;
        }

        if (timestamp < one_year_hours)
        {
            break;
        }

        tm_time->tm_year++;
        timestamp -= one_year_hours;
    }

    tm_time->tm_hour=(int)(timestamp % 24);                 // 计算时

    timestamp /= 24;                                        // 一年中剩下的天数
    timestamp++;
  
    tm_time->tm_yday = timestamp-1;                         // 计算天

    if ((tm_time->tm_year & 3) == 0)                        // 闰年处理
    {
        if (timestamp > 60)
        {
            timestamp--;                                    // 因为有1月29日的存在
        }
        else if (timestamp == 60)
        {
            tm_time->tm_mon = 1;                            // 计算月
            tm_time->tm_mday = 29;                          // 计算日
            return;
        }
    }

    // 计算日月
    for (tm_time->tm_mon = 0; Days[tm_time->tm_mon] < timestamp; tm_time->tm_mon++)
    {
        timestamp -= Days[tm_time->tm_mon];
    }

    tm_time->tm_mday = (int)(timestamp);
}

