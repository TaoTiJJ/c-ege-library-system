#include "include.h"
extern int time_debug ; 
void display_init(void){
	setinitmode(0);   //去掉丑陋的EGE载入画面 
	initgraph(900,700); //窗口为900*700 
	setbkcolor(EGERGB(255,255,255));   //白底背景
	setcaption("图书管理系统Library management system"); //标题 
	setcolor(EGERGB(0,0,0));
    setfont(30,0,"楷书");  //设置字体 
}

void display_zero(void){
	PIMAGE backgroud = newimage();
    getimage(backgroud,"Image\\background.jpg");
    putimage(100,100,1000,900,backgroud,20,0);
    delimage(backgroud);
    
    PIMAGE backgroud2 = newimage();
    getimage(backgroud2,"Image\\bg01.jpg");
    putimage(20,0,1000,900,backgroud2,20,0);
    delimage(backgroud2);
    
    if(time_debug == 0)
    	sys_time = get_systime();
    setbkmode(TRANSPARENT);                        //设置文字为透明
	setcolor(EGERGB(0,0,0));
	setfont(30,0,"黑体");
    /****************************/
    xyprintf(220,240,"◆录入◆");
   	xyprintf(220,340,"◆删除◆");
    xyprintf(220,440,"◆查询◆");
	xyprintf(480,240,"◆借阅◆");
   	xyprintf(480,340,"◆归还◆");
   	xyprintf(480,440,"◆测试◆");
   	xyprintf(740,20,"%4d/%2d/%2d",sys_time.year,sys_time.month,sys_time.day);
   	xyprintf(740,50,"  %2d:%2d  ",sys_time.hours,sys_time.minutes);
}

void display_login(void){
	PIMAGE backgroud = newimage();
    getimage(backgroud,"Image\\LOGIN.png");
    putimage(0,0,1000,900,backgroud,20,0);
    delimage(backgroud);
}

void display_loading(const char *c){
	int i,j,xth=0;
    setlinestyle(CENTER_LINE,NULL,10);
    for(i=100;i>=0;i--)
    {
        cleardevice();
        PIMAGE bye=newimage();
		getimage(bye,"Image\\load0.png");
		putimage(0,0,bye);
		delimage(bye);
		setcolor(BLACK);
 		setfont(60,0,"黑体");
 		
        xyprintf(80,300,"%s",c);
        xyprintf(80,360,"%d%%",100-(i));
        setfont(40,0,"楷书");
 		
        //setcolor(RED);
        //line(0,490,xth,490);
        PIMAGE load = newimage();
        getimage(load,"Image\\load.png");
        putimage(xth,470,load);
        delimage(load);
        
        delay_ms(2);
        xth+=8;
    }
}

void display_input(void){
	cleardevice();
	char str[20];
	
	PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
	flushkey();  //清除键盘缓冲区 
	
    pb = getbooks(pb);
    inputbox_getline("录入新书？ 请小心输入"," 准备好了吗？ 输入回车let's go!",str,sizeof(str));
    /*注 1226 发现ege键盘输入缓冲区有时候会产生回车 导致输入失败 这里用一个空白无用的输入来缓冲*/
    /*1228 发现flushkey函数可以解决 上一行懒得删除 就留着了*/ 

    inputbox_getline("录入新书？ 请小心输入","请输入书名：",pb->book_name,sizeof(pb->book_name));
    inputbox_getline("录入新书？ 请小心输入","请输入类别：",pb->classes,sizeof(pb->classes));
    inputbox_getline("录入新书？ 请小心输入","请输入作者：",pb->author,sizeof(pb->author));
    inputbox_getline("录入新书？ 请小心输入","请输入价格：",str,sizeof(str));
    pb->price = atoi(str);//C语言库自带神奇函数 输入char型，输出int型 
    pb->exist = 1;
    pb->where = at_home;
    
    books_storage();
    display_loading("正在添加。。。");
}

void display_watch(void){
	mouse_msg msg = {0};
	static int xianshi=1; // =1 显示书 =0 显示借阅记录 
    book_display();
    for (; is_run(); delay_fps(60))
    {
    	while (mousemsg())               //获取鼠标消息，这个函数会等待，等待到有消息为止
        {
            msg = getmouse();
        }	
	 	if(xianshi == 1)
        {
			book_display();
			setcolor(RED);
			xyprintf(220,20,"%s","【书籍信息】");
			setcolor(BLACK);
			xyprintf(500,20,"%s","【借阅信息】"); 
		}
		else
		{
			py_display();
			setcolor(RED);
			xyprintf(500,20,"%s","【借阅信息】"); 
			setcolor(BLACK);
			xyprintf(220,20,"%s","【书籍信息】");
		}
		//xyprintf(0,500,"%d-%d",msg.x,msg.y);
		xyprintf(700,640,"%s","【返回】");
		if(Mouse_position(670,810,600,680,msg) == 1){
		 	if(msg.is_down() == 1){
		 		display_loading("返回中。。。"); 
			 	break;
			}
		 }
		 else if(Mouse_position(220,380,18,50,msg) == 1){
		 	if(msg.is_down() == 1){
				xianshi = 1;
			}
		 }
		else if(Mouse_position(500,660,18,50,msg) == 1){
		 	if(msg.is_down() == 1){
				xianshi = 0;
			}
		 }
	}
} 

void display_miss(){
	mouse_msg msg = {0};
	char str[20];
    int width=80;
    int sfind=0;
    cleardevice();
    flushkey();
    inputbox_getline("删除书籍吗?" ,"请输入被删除书名：",str,sizeof(str));
    for(pb=books;(((pb->exist)==1)&&(sfind==0));pb++)
    {
        if(strcmp(str,pb->book_name)== 0)
		{
			sfind=1;pb--;
		}
        else
            sfind=0;
    }
    
    for (; is_run(); delay_fps(60))
    {
    		PIMAGE bg=newimage();
			getimage(bg,"Image\\1.jpg");
			putimage(0,0,bg);
			delimage(bg);
    		while (mousemsg())               //获取鼠标消息，这个函数会等待，等待到有消息为止
            {
                msg = getmouse();
            }
            xyprintf(0,0,"%d,%d",msg.x,msg.y);
            setfont(30,0,"黑体"); 
            xyprintf(500,200,"查找结果: ");
           
            if(sfind==1)
    		{
    			xyprintf(440,240,"%s(%s)-（%d元）",pb->book_name,pb->author,pb->price);
				xyprintf(440,280,"你确定要删除吗？") ;	
				
				xyprintf(450,400,"确定");
				xyprintf(650,400,"算了"); 
				if(msg.is_left() == 1){
				
					if(Mouse_position(450,510,400,450,msg) == 1) //确定 
					{
						for(;(((pb+1)->exist)==1);pb++)
								*pb = *(pb+1);
						pb->exist = 0;
						books_storage();
						display_loading("正在删除-->删除成功"); 
						flushkey();
						flushmouse();
						break;
					}
					if(Mouse_position(650,710,400,450,msg) == 1) //算了 
					{
						flushkey();
						flushmouse();
						display_loading("算了就算了"); 
						break;
					}
				} 
    		}
    		else
    		{
    			xyprintf(540,240,"未找到");
    			xyprintf(500,280,"你确定要删除<<%s>>?",str);
				xyprintf(540,500,"【按任意键返回主菜单】");
				flushkey();
				getch(); 
				break;
			} 
	}
} 

void display_borrow(void)
{
	char str[20];
    int width=50;
    int sfind = 0;
    setfont(30,0,"黑体"); 
    pp = getPy(pp);
    PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
    flushkey(); 
    inputbox_getline("请小心输入,别弄错","请输入书名：",str,sizeof(str));
    
    pb=books;
    for(;(((pb->exist)==1)&&(sfind==0));pb++)
    {
        if(strcmp(pb->book_name,str)== 0)
        {
            if((pb->where == at_home))
            {
                sfind=1;
                pb--;
            }
            else
            {
                sfind=3;
            }
        }
        else
        {
            sfind=0;
        }
    }
    
    cleardevice();
    bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
    if(sfind==0)
    {
        xyprintf(100,100,"【系统消息】：查找失败:没有书籍");
        xyprintf(100,130,"请确认是否输入错误或者根本没书， 谢谢合作");
        setcolor(BLACK);
        xyprintf(100,480,"%s","返回主菜单【Enter】");
        while(!(getch()==13)); //Enter的ASCii=13
        display_loading("返回主菜单中");
    }
    else if(sfind==1)
    {
    	width = 50;
        pb->where=go_out;
        pb->Borrow_i+=1;
        pb->Borrow_dat = sys_time;
        pb->Must_dat = Borrow_d(pb->Borrow_dat);
        
        pp = getPy(pp);
    	inputbox_getline("你的名字？: ","tell me your name ", pp->student_name,sizeof( pp->student_name));
    	pp->exist = 1;
    	pp->happen_dat = sys_time;
    	strcpy(pp->book_name,pb->book_name);
   	 	pp->sta = 1;
    	xyprintf(50,width-30,"借书人：%8s",pp->student_name);
    	xyprintf(50,width,"借阅书籍：%8s",pp->book_name);

    	width+=30;
    	xyprintf(50,width,"借阅日期：%d年-%d月-%d日",pb->Borrow_dat.year,pb->Borrow_dat.month,pb->Borrow_dat.day);
    	width+=30;
    	xyprintf(50,width,"应还日期：%d年-%d月-%d日",pb->Must_dat.year,pb->Must_dat.month,pb->Must_dat.day);
    	width+=30;
    	xyprintf(50,width,"【系统消息】：请确认信息");
    	width+=30;
		xyprintf(50,width,"    看好借出日期与应还日期，谢谢合作");
    	
    	xyprintf(50,400,"【Enter 返回】");
        books_storage();	
		py_storage();
        while(!(getch() == 13)); 
        display_loading("返回主菜单中");
    }
    else
    {
        xyprintf(100,100,"【系统消息】：不好意思， 书被借走了哦 下次早点来吧！ ");
        setcolor(BLACK);
        xyprintf(100,480,"%s","返回主菜单【Enter】");
        while(!(getch()==13)); //Enter的ASCii=13
        display_loading("返回主菜单中");
    }
} 

void display_ret(void){
	cleardevice();
	int i =0;
    char str[20];
   	mouse_msg msg = {0};
    char status[20];
    int sta=0; // 0为未判断 1为常规 2为超时间 3为丢失
    int width=50;
	 
   	PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
	flushkey();
    inputbox_getline("呦，来还书了？ ","请输入书名 ", str,sizeof(str));
    int sfind=0;
    pb=books;
    for(;(((pb->exist)==1)&&(sfind==0));pb++)
    {
        if(strcmp(str,pb->book_name)== 0)
        {
            if((pb->where == go_out))
            {
                sfind=1;pb--;
            }
            else
            {
                sfind=3;
            }
        }
        else
        {
            sfind=0;
        }
    }
    
	if(sfind==0){
        xyprintf(100,100,"【系统消息】：查找失败:没有书籍");
        xyprintf(100,130,"请确认是否输入错误或者根本没书， 谢谢合作");
        setcolor(BLACK);
        xyprintf(100,480,"%s","返回主菜单【Enter】");
        while(!(getch()==13)); //Enter的ASCii=13
        display_loading("返回主菜单中");
    } 
    else if(sfind == 1){
    	pb->where = at_home;
    	pp = getPy(pp);
    	
    	inputbox_getline("你的名字？: ","tell me your name ", pp->student_name,sizeof( pp->student_name));
    	pp->exist = 1;
    	pp->happen_dat = get_systime();
    	strcpy(pp->book_name,pb->book_name);
    	py_storage();
    	books_storage();
    	i = day_day(pb->Borrow_dat,sys_time);
    	if( i< rec_limit) //常规归还书籍 
    	{
    		sta = 1;
    		strcpy(status,"常规归还"); 
		}
		else if(i < break_limit)//超时罚款 
		{
			sta = 2;
			strcpy(status,"超时罚款");
		}
		else{
			strcpy(str,pp->student_name) ;
			xyprintf(100,width-30,"还书人：%8s",str);
    		xyprintf(100,width,"归还书籍：%8s",pb->book_name);
    		width+=30;
    		xyprintf(100,width,"借阅日期：%d年-%d月-%d日",pb->Borrow_dat.year,pb->Borrow_dat.month,pb->Borrow_dat.day);
    		width+=30;
    		xyprintf(100,width,"当前日期：%d年-%d月-%d日",sys_time.year,sys_time.month,sys_time.day);
    		width+=30;
		} 
		
		if(sta == 2)
   		{
        	setcolor(RED);
        	xyprintf(100,width,"状态：%s (%d天) ",status,i);
        	setcolor(BLACK);
    	}
   		else if(sta == 3)
    	{
        	setcolor(GREEN);
        	xyprintf(100,width,"状态：%s (%d天) ",status,i);
        	setcolor(BLACK);
    	}
    	width+=30;
    	xyprintf(100,width,"常规缴纳：%d元) ",i);
    	width+=30;
    	xyprintf(100,width,"【系统消息】：请核对还书信息");
     	xyprintf(700,470,"%s","【返回】");
        msg=getmouse();
        while((Mouse_position(680,800,460,480,msg)==0)||(msg.is_left() == 0))
        {
            msg=getmouse();
        }
        display_loading("返回主菜单中");
	} 
  	else
    {
        xyprintf(100,100,"【系统消息】：are you sure? 它在库里啊 ");
        setcolor(BLACK);
        xyprintf(200,470,"%s","【返回】");
        msg=getmouse();
        while((Mouse_position(180,300,460,480,msg)==0)||(msg.is_left() == 0))
        {
            msg=getmouse();
        }
        display_loading("返回主菜单中");
    }
}

void display_test(char *c)
{
    PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
	
    inputbox_getline("测试_改变时间(测试——为答辩而生): ","输入实例：若想日期改变为2012年10月12日则输入20121012",c,sizeof(char)*9);
}
