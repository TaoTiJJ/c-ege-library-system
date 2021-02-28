#include "include.h"

/***************************/
dates sys_time;
int time_debug = 0; 
// time_debug = 0 获取当前电脑时间， =1 用户自己设置时间 

Book_info books[MAX_use];
Book_info *pb;
Py bussiness[MAX_use];
Py *pp;
/***************************/

/*初始化程序*/
void all_init(void){
	display_init();
	File_init();
  	BGM();
  	sys_time = get_systime();
}

int main(int argc, char** argv) {
	int i;
	int password[4]={0}; 
	char str[20];
	int get = 10;
	all_init(); 
	mouse_msg msg = {0};
	 
	/***************************************************/
	for (; is_run(); delay_fps(60))
    {
    	cleardevice();
		display_login();
        while (mousemsg())               //获取鼠标消息，这个函数会等待，等待到有消息为止
        {
            msg = getmouse();
        }
        //xyprintf(0, 0, "x = %3d  y = %3d, %d，%d",msg.x, msg.y,msg.is_down(),get); 
        if(msg.is_down() == 1){
			if(Mouse_position(41,225,342,410,msg) == 1) // 7
				get = 7;
			else if(Mouse_position(240,420,324,410,msg) == 1) //8
				get = 8;
			else if(Mouse_position(445,635,324,410,msg) == 1) //9
				get = 9;
			else if(Mouse_position(41,225,416,495,msg) == 1) //4
				get = 4;
			else if(Mouse_position(240,420,416,495,msg) == 1) //5
				get = 5;
			else if(Mouse_position(445,635,416,495,msg) == 1) //6
				get = 6;
			else if(Mouse_position(41,225,500,575,msg) == 1) //1
				get = 1;
			else if(Mouse_position(240,420,500,575,msg) == 1) //2
				get = 2;
			else if(Mouse_position(445,635,500,575,msg) == 1) //3
				get = 3;
			else if(Mouse_position(30,230,575,650,msg) == 1) //C
				get =-1;
			else if(Mouse_position(240,420,575,650,msg) == 1) //0
				get = 0;
			else if(Mouse_position(445,615,575,650,msg) == 1) //login
				get = -2;
			else{
				get = 10;
			}
		}
		
		if(get>=0 && get <=9)
		{
			if(password[0]>0){
				if(password[password[0]] != get)
				if(password[0]<=3)
				{
					password[0]++;
					password[password[0]] = get;
				}
			}
			else
			{
				password[0]++;
				password[password[0]] = get;
			}
			
			get = 10;
		}
		if(get == -1)
		{
			password[0] = 0;
		}
		else if(get == -2)
		{
			if(password[1] == 1 && password[2] == 2 && password[3] == 3)
				break;
			else
				password[0] = 0;
		}
		for(i=1;i<=password[0];i++){
			setfont(30,0,"楷书"); 
			xyprintf(180*i-20,250,"%d",password[i]);
		} 
		flushmouse();
	}
	
	/***************************************************/
	
	display_loading("正在登陆。。。");	
    for (; is_run(); delay_fps(60))
    {
            while (mousemsg())               //获取鼠标消息，这个函数会等待，等待到有消息为止
            {
                msg = getmouse();
            }
            cleardevice();
           	//xyprintf(0,600, "x = %3d  y = %3d",msg.x, msg.y);
			display_zero();
			if(msg.is_left() == 1){
				if(Mouse_position(220,340,230,270,msg) == 1) //录入
				{
					display_input();
				}
				else if(Mouse_position(220,340,330,370,msg) == 1) //删除
				{
					display_miss();
				} 
				else if(Mouse_position(220,340,430,470,msg) == 1) //查询 
				{	
					 display_watch();
				}
				else if(Mouse_position(480,600,230,270,msg) == 1) //借阅 
				{
					display_borrow();
				}
				else if(Mouse_position(480,600,330,370,msg) == 1) //归还 
				{
					display_ret();
				}
				else if(Mouse_position(480,600,430,470,msg) == 1) //测试 
				{
					display_test(str);
					sys_time = string_dat(str);
					time_debug = 1;
				}
				else
					continue; 
			}
	}
	closegraph();
	return 0;
}
