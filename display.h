#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "include.h"

void display_init(void);
void display_zero(void);
void display_login(void);
void display_loading(const char *c);
void display_input(void); 
void display_miss(void);
void display_borrow(void);
void display_ret(void);
void display_watch(void);
void display_test(char *c);
#endif 
