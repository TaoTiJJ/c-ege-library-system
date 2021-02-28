/*!
 * @file       sys.h
 * @brief      系统定义头文件
 * @author     刘箐 
 */

#ifndef SYS_H_INCLUDED
#define SYS_H_INCLUDED

#define rec_limit 30   //借书归还 时间/天 
#define break_limit 90 //丢失判定时间/天 
#define MAX_use 100
// #define DEBUG
#define Release


typedef enum
{
    at_home=0,
    go_out=1,
} status;  


typedef struct timerst{
    int year;
    int month;
    int day;
    int hours;
    int minutes;
}dates;

typedef struct book
{
    int number;         //书号
    char book_name[20];      //书名
    char classes[20];   //类别
    char author[20];    //作者
    int price;     //价格
    
    status where;
    /*状态：  athome 在系统内
              goout 借出
    */
    int Borrow_i;       //借阅次数
    dates Borrow_dat;   //借阅 年
                        //借阅 月
                        //借阅 日
    dates Must_dat;     //应还 年
                        //应还 月
                        //应还 日
    int exist;
    /*此标志位用于确定库内书*/
}Book_info;

typedef struct stu
{
    char name[20];           //姓名
    char number[20];         //学号
    char Borrow_now;         //当前借书
    char Borrow_i;           //累计借阅次数
    int exist;
}Student_info;

typedef struct bussiness
{
    char book_name[20];
    char student_name[20];
    int sta;
    /*1是借书 0是还书*/
    dates happen_dat;
    int exist;
}Py;

#endif // SYS_H_INCLUDED
