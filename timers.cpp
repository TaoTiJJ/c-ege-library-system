/*!
 * @file       timers.cpp
 * @brief      ʱ�亯��
 * @author     
 */
#include "timer.h"

/* judge is year a leap year��*/
#define leap_year(year) ((((year%4==0)&&(year%100!=0))||(year % 400 == 0))?1:0)

#define Beginyear 1970
/*****************************************************/

int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
//              1 2 3 4 5 6 7 8 9 10 11 12

//����
int month1[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

/*****************************************************/


/*
    �������ߣ�
    ע����
*/
dates get_systime()
{
    /*ʱ��ڵ�ȴ��1900*/
    /*��ȡ��������ʱ�� 19700101*/
    dates sys_time;
    time_t now;
    struct tm *timenow;
    time(&now);
    //time������ȡ���ڵ�ʱ��(���ʱ�׼ʱ��Ǳ���ʱ��)��Ȼ��ֵ��now
    timenow =localtime(&now);
    //localtime�����Ѵ�timeȡ�õ�ʱ��now�����������е�ʱ��(���������õĵ���)
    sys_time.year = timenow->tm_year+1900;
    // tm_year;years from 1900
    sys_time.month = timenow->tm_mon+1;
    sys_time.day = timenow->tm_mday;
    sys_time.hours = timenow->tm_hour;
    sys_time.minutes = timenow->tm_min;
    return sys_time;
}

int month_to_day(dates now)
{
    int i,day=0;
    for(i=1;i< now.month;i++)
    {
        day+=month[i];
    }
    if((leap_year(now.year))&&now.month >2)
    {
        day+=1;
    }
    day=day+now.day;
    return day;
}

dates day_to_month(int day)
{
    dates now;
    int i;
    int imonth=1;
    now= get_systime();

    if(leap_year(now.year))
    {
        for(i=1;day>month1[i];i++)
        {
            day -= month1[i];
            imonth++;
        }
    }
    else
    {
        for(i=1;day>month1[i];i++)
        {
            day -= month[i];
            imonth++;
        }
    }
    now.day = day;
    now.month = imonth;
    return now;
}

