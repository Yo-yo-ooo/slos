#include <inc/time.h>
#include <inc/lib.h>

long timez = 0;
int daylite = 1;
#define dysize(xyear) ((xyear&03) ? 365 : 366)

time_t time(time_t tt){
    if(tt != NULL){
        localtime(tt);
    }else{
        return (time_t)-1;
    }
}

size_t mktime(struct tm tm_now){
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

scomp(register a,register b,register char s){
	if(s == '+')
		return(a > b);
	if(s == '-')
		return(a < (b * -1));
	return(a == b);
}

void tzset(){
    register char *p;
    register int n;
    int sign;
    if((p = getenv("TZ")) && *p){
        p += 3;
        if (sign = *p == '-')
			p++;
		n = 0;
		while (*p >= '0' && *p <= '9')
			n = (n * 10) + *p++ - '0';
		if (sign)
			n = -n;
		timez = ((long) (n * 60)) * 60;
		if (*p) daylite = 1;
		else daylite = 0;
    }
}

sunday(register struct tm *t,register int d){
    if ((d >= 58) && ((t->tm_year & 03) == 0)){ 
        d+=1; /* leap year */
    }
	return(d - (d - t->tm_yday + t->tm_wday + 700) % 7);
}

struct tm *l_gmtime(long *tim){
    char dmsize[12] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31
    };
    /* Keywords: time-processing */
	register int d0, d1;
	int day;
	long hms;
	static struct tm xtime;

	/*
	 * break initial number into days
	 */
	day = *tim / 86400;
	hms = *tim - (day*86400);

	/*
	 * generate hours:minutes:seconds
	 */
	d1 = hms/60;
	xtime.tm_sec = hms - (((long)d1)*60L);
	xtime.tm_min = d1%60;
	d1 /= 60;
	xtime.tm_hour = d1;

	/*
	 * day is the day number.
	 * generate day of the week.
	 * The addend is 4 mod 7 (1/1/1970 was Thursday)
	 */

	xtime.tm_wday = (day+4)%7;

	/*
	 * year number
	 */
	for(d1=70; day >= dysize(d1); d1++)
		day -= dysize(d1);
	xtime.tm_year = d1;
	xtime.tm_yday = d0 = day;

	/*
	 * generate month
	 */

	if ((d1&03) == 0)dmsize[1] = 29;
	else dmsize[1] = 28;
	for(d1=0; d0 >= dmsize[d1]; d1++)
		d0 -= dmsize[d1];
	xtime.tm_mday= d0+1;
	xtime.tm_mon = d1;
	return(&xtime);
}

struct tm *localtime(long *tim){
    register int dayno;
    register struct tm *ct;
    register daylbegin, daylend;
    long copyt;

    if(timez == 0) tzset();

	copyt = *tim - timez;
	ct = l_gmtime(&copyt);
	if (!daylite) return(ct);
	dayno = ct->tm_yday;
	daylbegin  = 119;	/* last Sun in Apr */
	daylend  = 303;		/* Last Sun in Oct */
	daylbegin = sunday(ct, daylbegin);
	daylend = sunday(ct, daylend);
	if ((dayno>daylbegin || (dayno==daylbegin && ct->tm_hour>=2)) &&
	    (dayno<daylend || (dayno==daylend && ct->tm_hour<1))) {
		copyt += 1*60*60;
		ct = l_gmtime(&copyt);
	}
	return(ct);
}
