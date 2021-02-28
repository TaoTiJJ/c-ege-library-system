/*!
 * @file       Files.cpp
 * @brief      文件函数
 * @author     刘
 */
#include "include.h" 
/*初始化文件 若不存在则自动创建文件*/
void File_init(void)
{
    FILE *fp;
    while( (fp=fopen("datas\\book_info.dat","rb"))==NULL )
    {
        fp=fopen("datas\\book_info.dat","wb");
    }
    fclose(fp);
    while( (fp=fopen("datas\\student_info.dat","rb"))==NULL )
    {
        fp=fopen("datas\\student_info.dat","wb");
    }
    fclose(fp);
    while( (fp=fopen("datas\\py_info.dat","rb"))==NULL )
    {
        fp=fopen("datas\\py_info.dat","wb");
    }
    fclose(fp);
    
    pb=books;
    fp=fopen("datas\\book_info.dat","rb");
    fread(pb,sizeof(Book_info),MAX_use,fp);
    fclose(fp);
    pp=bussiness;
    fp=fopen("datas\\py_info.dat","rb");
    fread(pp,sizeof(Book_info),MAX_use,fp);
    fclose(fp);
}

void books_storage()
{
    FILE *fp;
    while( (fp=fopen("datas\\book_info.dat","rb"))==NULL )
    {
        fp=fopen("datas\\book_info.dat","wb");
    }
    fclose(fp);
    fp=fopen("datas\\book_info.dat","wb");
    pb = books;
    fwrite(pb,sizeof(Book_info),MAX_use,fp);
    fclose(fp);
}

void py_storage()
{
    FILE *fp;
    while( (fp=fopen("datas\\py_info.dat","rb"))==NULL )
    {
        fp=fopen("datas\\py_info.dat","wb");
    }
    fclose(fp);
    fp=fopen("datas\\py_info.dat","wb");
    pp = bussiness;
    fwrite(pp,sizeof(Py),MAX_use,fp);
    fclose(fp);
}
