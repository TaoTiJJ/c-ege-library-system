/*!
 * @file       book_stu.cpp
 * @brief      指针计算
 * @author     
 * @remarks    通过指针移动操作 简单 高效 快速 值得信赖！
 */

#include "include.h"
Book_info *getbooks(Book_info *pb)
{
    for(pb=books;(pb->exist)==1;pb++);
    return pb;
}

Py *getPy(Py *pp)
{
    for(pp=bussiness;(pp->exist)==1;pp++);
    return pp;
}

Book_info *sure_miss(Book_info *pb)
{
    int i;
    dates now;
    now = get_systime();
    for(;((pb->where)== go_out);pb++)
    {
        if(day_day(pb->Borrow_dat,now) >= break_limit)
        {
            return pb;
        }
        else
            i++;
    }
    pb = NULL;
    return pb;
}

void book_display()
{
    int width=185;
    PIMAGE bg=newimage();
	getimage(bg,"Image\\bg02.jpg");
	putimage(0,0,bg);
	delimage(bg);
    pb=books;
    setfont(30,0,"黑体"); 
    setbkmode(TRANSPARENT);                        //设置文字为透明
    xyprintf(300,width-80,"-------%s-------","书籍信息");
    xyprintf(100,width-40,"|%20s|%5s|%8s|%4s|","书名        ","类别 ","作者 ","价格");
    xyprintf(100,width-20,"|%20s|%5s|%8s|%4s|","--------------------","-----","--------","----");
    for(;(pb->exist)==1;pb++)
    {
        if((pb->where)==go_out)
        {
                setcolor(RED);
               	xyprintf(100,width,"|<<%16s>>|%5s|%8s|%4d|",pb->book_name,pb->classes,pb->author,pb->price);
               	setcolor(BLACK);
                xyprintf(100,width+20,"|%20s|%5s|%8s|%4s|","--------------------","-----","--------","----");
        }
        else
        {
                setcolor(BLUE);
                xyprintf(100,width,"|<<%16s>>|%5s|%8s|%4d|",pb->book_name,pb->classes,pb->author,pb->price);
               	setcolor(BLACK);
                xyprintf(100,width+20,"|%20s|%5s|%8s|%4s|","--------------------","-----","--------","----");
        }
        width+=40;
    }
}

void py_display()
{
    int width = 185;
    PIMAGE bg=newimage();
	getimage(bg,"Image\\bg02.jpg");
	putimage(0,0,bg);
	delimage(bg);
    pp=bussiness;  
	setfont(30,0,"黑体");
    xyprintf(300,width-80,"-------%s-------","借阅信息");
    width = width - 20; 
    xyprintf(105,137,"________________________________________");
    for(;(pp->exist)==1;pp++)
    {
        if((pp->sta)==1)
        {
            setcolor(RED);
            xyprintf(100,width,"|%4d年%2d月%2d日%8s%5s<<%8s>>|",pp->happen_dat.year,pp->happen_dat.month,pp->happen_dat.day,pp->student_name,"借出",pp->book_name);
            setcolor(BLACK);
		    xyprintf(105,width+2,"________________________________________");
        }
        else
        {
            setcolor(BLUE);
            xyprintf(100,width,"|%4d年%2d月%2d日%8s%5s<<%8s>>|",pp->happen_dat.year,pp->happen_dat.month,pp->happen_dat.day,pp->student_name,"归还",pp->book_name);
            setcolor(BLACK);
		   	xyprintf(105,width+2,"________________________________________");
        }
        setcolor(BLACK);
        width+=30;
    }
}
