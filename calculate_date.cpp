/*!
 * @file       calculate_date.cpp
 * @brief      ʱ����㺯�� 
 * @author      
 */

 /****************************************/

/*���ļ���Ҫ����Ϊͼ��ݽ������ʱ����㣬
��ɹ��ܣ�
1. �������ڵ�ʱ���
2. ĳ�����ڵ���ʮ�����ĳ��
3. �����ַ��� ��ȡ���� �������Ѷ�
*/
/***************************************/
#include "calculate_data.h"


/****************************************/
/*
#define rec_limit 30
#define break_limit 90
ע�� ���й���define�ͽṹ��Ķ��嶼�ƶ�����sys.h
*/

/*�ַ���ת����data*/
/*20111011- 2011��10��11��*/
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



//����һ�����ڽṹ�� ����Ӧ�û����ʱ��
dates Borrow_d(dates now)
{
    int i;
    dates rec;
    i=month_to_day(now);
    rec=day_to_month(i+rec_limit);
    return rec;
}
