/*!
 * @file       sys.h
 * @brief      ϵͳ����ͷ�ļ�
 * @author     ���� 
 */

#ifndef SYS_H_INCLUDED
#define SYS_H_INCLUDED

#define rec_limit 30   //����黹 ʱ��/�� 
#define break_limit 90 //��ʧ�ж�ʱ��/�� 
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
    int number;         //���
    char book_name[20];      //����
    char classes[20];   //���
    char author[20];    //����
    int price;     //�۸�
    
    status where;
    /*״̬��  athome ��ϵͳ��
              goout ���
    */
    int Borrow_i;       //���Ĵ���
    dates Borrow_dat;   //���� ��
                        //���� ��
                        //���� ��
    dates Must_dat;     //Ӧ�� ��
                        //Ӧ�� ��
                        //Ӧ�� ��
    int exist;
    /*�˱�־λ����ȷ��������*/
}Book_info;

typedef struct stu
{
    char name[20];           //����
    char number[20];         //ѧ��
    char Borrow_now;         //��ǰ����
    char Borrow_i;           //�ۼƽ��Ĵ���
    int exist;
}Student_info;

typedef struct bussiness
{
    char book_name[20];
    char student_name[20];
    int sta;
    /*1�ǽ��� 0�ǻ���*/
    dates happen_dat;
    int exist;
}Py;

#endif // SYS_H_INCLUDED
