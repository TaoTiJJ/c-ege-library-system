/*!
 * @file       calculate_date.cpp
 * @brief      时间计算函数 
 * @author      
 */

 /****************************************/

/*该文件主要作用为图书馆借阅书的时间计算，
完成功能：
1. 两个日期的时间差
2. 某个日期的三十天后是某天
3. 输入字符串 获取日期 简化输入难度
*/
/***************************************/
#include "calculate_data.h"


/****************************************/
/*
#define rec_limit 30
#define break_limit 90
注： 所有关于define和结构体的定义都移动到了sys.h
*/

/*字符串转换成data*/
/*20111011- 2011年10月11日*/
dates string_dat(char *string_data)
{
    char year[5],month[5],day[3];
    dates d1;
    d1=get_systime();
    memset(year,0x00,sizeof(year));
    memset(month,0x00,sizeof(month));
    memset(day,0x00,sizeof(day));

    memcpy(year,string_data,4);
    memcpy(month,string_data+4,2);
    memcpy(day,string_data+6,2);

    d1.year = atoi(year);
    d1.month = atoi(month);
    d1.day = atoi(day);

    return d1;
}

int day_day(dates dbegin ,dates dend)
{
    int begini,endi;
    int p;
    if(dbegin.month == 12)
    {
        return 0;
    }
    else
    {
        begini = month_to_day(dbegin);
        endi =  month_to_day(dend);
        p=endi-begini;
        return p;
    }
}



//输入一个日期结构体 返回应该还书的时间
dates Borrow_d(dates now)
{
    int i;
    dates rec;
    i=month_to_day(now);
    rec=day_to_month(i+rec_limit);
    return rec;
}
