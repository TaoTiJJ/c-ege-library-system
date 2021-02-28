/*
 * @Author: your name
 * @Date: 2019-10-29 14:11:32
 * @LastEditTime : 2019-12-23 14:10:02
 * @LastEditors  : Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \kendryte-standalone-sdk-develope:\Ccode\EGEpro\LMG0102\include.h
 */
/*!
 * @file       include.h
 * @brief      
 * @author    
 */
#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <ege.h>
#include <time.h>

#include "music.h"
#include "display.h"
#include "mouse.h"
#include "sys.h" 
#include "Files.h"
#include "calculate_data.h"
#include "timer.h" 
#include "book_stu.h"

extern Book_info books[MAX_use];
extern Book_info *pb;
extern Py bussiness[MAX_use];
extern Py *pp;
extern dates sys_time;
//#define DEBUG

#endif // INCLUDE_H_INCLUDED
