#include "mouse.h"

int Mouse_position(int zx,int yx,int sy,int xy, mouse_msg M)
{
    if((M.x>=zx)&&(M.x<=yx)&&(M.y>=sy)&&(M.y<=xy))
        return 1;
    else
        return 0;
}



