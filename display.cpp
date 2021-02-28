#include "include.h"
extern int time_debug ; 
void display_init(void){
	setinitmode(0);   //ȥ����ª��EGE���뻭�� 
	initgraph(900,700); //����Ϊ900*700 
	setbkcolor(EGERGB(255,255,255));   //�׵ױ���
	setcaption("ͼ�����ϵͳLibrary management system"); //���� 
	setcolor(EGERGB(0,0,0));
    setfont(30,0,"����");  //�������� 
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
    setbkmode(TRANSPARENT);                        //��������Ϊ͸��
	setcolor(EGERGB(0,0,0));
	setfont(30,0,"����");
    /****************************/
    xyprintf(220,240,"��¼���");
   	xyprintf(220,340,"��ɾ����");
    xyprintf(220,440,"����ѯ��");
	xyprintf(480,240,"�����ġ�");
   	xyprintf(480,340,"���黹��");
   	xyprintf(480,440,"�����ԡ�");
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
 		setfont(60,0,"����");
 		
        xyprintf(80,300,"%s",c);
        xyprintf(80,360,"%d%%",100-(i));
        setfont(40,0,"����");
 		
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
	flushkey();  //������̻����� 
	
    pb = getbooks(pb);
    inputbox_getline("¼�����飿 ��С������"," ׼�������� ����س�let's go!",str,sizeof(str));
    /*ע 1226 ����ege�������뻺������ʱ�������س� ��������ʧ�� ������һ���հ����õ�����������*/
    /*1228 ����flushkey�������Խ�� ��һ������ɾ�� ��������*/ 

    inputbox_getline("¼�����飿 ��С������","������������",pb->book_name,sizeof(pb->book_name));
    inputbox_getline("¼�����飿 ��С������","���������",pb->classes,sizeof(pb->classes));
    inputbox_getline("¼�����飿 ��С������","���������ߣ�",pb->author,sizeof(pb->author));
    inputbox_getline("¼�����飿 ��С������","������۸�",str,sizeof(str));
    pb->price = atoi(str);//C���Կ��Դ����溯�� ����char�ͣ����int�� 
    pb->exist = 1;
    pb->where = at_home;
    
    books_storage();
    display_loading("������ӡ�����");
}

void display_watch(void){
	mouse_msg msg = {0};
	static int xianshi=1; // =1 ��ʾ�� =0 ��ʾ���ļ�¼ 
    book_display();
    for (; is_run(); delay_fps(60))
    {
    	while (mousemsg())               //��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
        {
            msg = getmouse();
        }	
	 	if(xianshi == 1)
        {
			book_display();
			setcolor(RED);
			xyprintf(220,20,"%s","���鼮��Ϣ��");
			setcolor(BLACK);
			xyprintf(500,20,"%s","��������Ϣ��"); 
		}
		else
		{
			py_display();
			setcolor(RED);
			xyprintf(500,20,"%s","��������Ϣ��"); 
			setcolor(BLACK);
			xyprintf(220,20,"%s","���鼮��Ϣ��");
		}
		//xyprintf(0,500,"%d-%d",msg.x,msg.y);
		xyprintf(700,640,"%s","�����ء�");
		if(Mouse_position(670,810,600,680,msg) == 1){
		 	if(msg.is_down() == 1){
		 		display_loading("�����С�����"); 
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
    inputbox_getline("ɾ���鼮��?" ,"�����뱻ɾ��������",str,sizeof(str));
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
    		while (mousemsg())               //��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
            {
                msg = getmouse();
            }
            xyprintf(0,0,"%d,%d",msg.x,msg.y);
            setfont(30,0,"����"); 
            xyprintf(500,200,"���ҽ��: ");
           
            if(sfind==1)
    		{
    			xyprintf(440,240,"%s(%s)-��%dԪ��",pb->book_name,pb->author,pb->price);
				xyprintf(440,280,"��ȷ��Ҫɾ����") ;	
				
				xyprintf(450,400,"ȷ��");
				xyprintf(650,400,"����"); 
				if(msg.is_left() == 1){
				
					if(Mouse_position(450,510,400,450,msg) == 1) //ȷ�� 
					{
						for(;(((pb+1)->exist)==1);pb++)
								*pb = *(pb+1);
						pb->exist = 0;
						books_storage();
						display_loading("����ɾ��-->ɾ���ɹ�"); 
						flushkey();
						flushmouse();
						break;
					}
					if(Mouse_position(650,710,400,450,msg) == 1) //���� 
					{
						flushkey();
						flushmouse();
						display_loading("���˾�����"); 
						break;
					}
				} 
    		}
    		else
    		{
    			xyprintf(540,240,"δ�ҵ�");
    			xyprintf(500,280,"��ȷ��Ҫɾ��<<%s>>?",str);
				xyprintf(540,500,"����������������˵���");
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
    setfont(30,0,"����"); 
    pp = getPy(pp);
    PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
    flushkey(); 
    inputbox_getline("��С������,��Ū��","������������",str,sizeof(str));
    
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
        xyprintf(100,100,"��ϵͳ��Ϣ��������ʧ��:û���鼮");
        xyprintf(100,130,"��ȷ���Ƿ����������߸���û�飬 лл����");
        setcolor(BLACK);
        xyprintf(100,480,"%s","�������˵���Enter��");
        while(!(getch()==13)); //Enter��ASCii=13
        display_loading("�������˵���");
    }
    else if(sfind==1)
    {
    	width = 50;
        pb->where=go_out;
        pb->Borrow_i+=1;
        pb->Borrow_dat = sys_time;
        pb->Must_dat = Borrow_d(pb->Borrow_dat);
        
        pp = getPy(pp);
    	inputbox_getline("������֣�: ","tell me your name ", pp->student_name,sizeof( pp->student_name));
    	pp->exist = 1;
    	pp->happen_dat = sys_time;
    	strcpy(pp->book_name,pb->book_name);
   	 	pp->sta = 1;
    	xyprintf(50,width-30,"�����ˣ�%8s",pp->student_name);
    	xyprintf(50,width,"�����鼮��%8s",pp->book_name);

    	width+=30;
    	xyprintf(50,width,"�������ڣ�%d��-%d��-%d��",pb->Borrow_dat.year,pb->Borrow_dat.month,pb->Borrow_dat.day);
    	width+=30;
    	xyprintf(50,width,"Ӧ�����ڣ�%d��-%d��-%d��",pb->Must_dat.year,pb->Must_dat.month,pb->Must_dat.day);
    	width+=30;
    	xyprintf(50,width,"��ϵͳ��Ϣ������ȷ����Ϣ");
    	width+=30;
		xyprintf(50,width,"    ���ý��������Ӧ�����ڣ�лл����");
    	
    	xyprintf(50,400,"��Enter ���ء�");
        books_storage();	
		py_storage();
        while(!(getch() == 13)); 
        display_loading("�������˵���");
    }
    else
    {
        xyprintf(100,100,"��ϵͳ��Ϣ����������˼�� �鱻������Ŷ �´�������ɣ� ");
        setcolor(BLACK);
        xyprintf(100,480,"%s","�������˵���Enter��");
        while(!(getch()==13)); //Enter��ASCii=13
        display_loading("�������˵���");
    }
} 

void display_ret(void){
	cleardevice();
	int i =0;
    char str[20];
   	mouse_msg msg = {0};
    char status[20];
    int sta=0; // 0Ϊδ�ж� 1Ϊ���� 2Ϊ��ʱ�� 3Ϊ��ʧ
    int width=50;
	 
   	PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
	flushkey();
    inputbox_getline("�ϣ��������ˣ� ","���������� ", str,sizeof(str));
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
        xyprintf(100,100,"��ϵͳ��Ϣ��������ʧ��:û���鼮");
        xyprintf(100,130,"��ȷ���Ƿ����������߸���û�飬 лл����");
        setcolor(BLACK);
        xyprintf(100,480,"%s","�������˵���Enter��");
        while(!(getch()==13)); //Enter��ASCii=13
        display_loading("�������˵���");
    } 
    else if(sfind == 1){
    	pb->where = at_home;
    	pp = getPy(pp);
    	
    	inputbox_getline("������֣�: ","tell me your name ", pp->student_name,sizeof( pp->student_name));
    	pp->exist = 1;
    	pp->happen_dat = get_systime();
    	strcpy(pp->book_name,pb->book_name);
    	py_storage();
    	books_storage();
    	i = day_day(pb->Borrow_dat,sys_time);
    	if( i< rec_limit) //����黹�鼮 
    	{
    		sta = 1;
    		strcpy(status,"����黹"); 
		}
		else if(i < break_limit)//��ʱ���� 
		{
			sta = 2;
			strcpy(status,"��ʱ����");
		}
		else{
			strcpy(str,pp->student_name) ;
			xyprintf(100,width-30,"�����ˣ�%8s",str);
    		xyprintf(100,width,"�黹�鼮��%8s",pb->book_name);
    		width+=30;
    		xyprintf(100,width,"�������ڣ�%d��-%d��-%d��",pb->Borrow_dat.year,pb->Borrow_dat.month,pb->Borrow_dat.day);
    		width+=30;
    		xyprintf(100,width,"��ǰ���ڣ�%d��-%d��-%d��",sys_time.year,sys_time.month,sys_time.day);
    		width+=30;
		} 
		
		if(sta == 2)
   		{
        	setcolor(RED);
        	xyprintf(100,width,"״̬��%s (%d��) ",status,i);
        	setcolor(BLACK);
    	}
   		else if(sta == 3)
    	{
        	setcolor(GREEN);
        	xyprintf(100,width,"״̬��%s (%d��) ",status,i);
        	setcolor(BLACK);
    	}
    	width+=30;
    	xyprintf(100,width,"������ɣ�%dԪ) ",i);
    	width+=30;
    	xyprintf(100,width,"��ϵͳ��Ϣ������˶Ի�����Ϣ");
     	xyprintf(700,470,"%s","�����ء�");
        msg=getmouse();
        while((Mouse_position(680,800,460,480,msg)==0)||(msg.is_left() == 0))
        {
            msg=getmouse();
        }
        display_loading("�������˵���");
	} 
  	else
    {
        xyprintf(100,100,"��ϵͳ��Ϣ����are you sure? ���ڿ��ﰡ ");
        setcolor(BLACK);
        xyprintf(200,470,"%s","�����ء�");
        msg=getmouse();
        while((Mouse_position(180,300,460,480,msg)==0)||(msg.is_left() == 0))
        {
            msg=getmouse();
        }
        display_loading("�������˵���");
    }
}

void display_test(char *c)
{
    PIMAGE bg=newimage();
	getimage(bg,"Image\\1.jpg");
	putimage(0,0,bg);
	delimage(bg);
	
    inputbox_getline("����_�ı�ʱ��(���ԡ���Ϊ������): ","����ʵ�����������ڸı�Ϊ2012��10��12��������20121012",c,sizeof(char)*9);
}
