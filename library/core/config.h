//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息  
// 文件名称: config.h
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#ifndef __CONFIG_H__
#define __CONFIG_H__


//<<AICUBE_USER_DEFINE_BEGIN>>
// 在此添加用户宏定义

// USB CDC Endpoint Enable Macros
#define EN_EP1IN
#define EN_EP1OUT
#define EN_EP2IN

// USB Endpoint Size Macros
#define EP0_SIZE        64
#define EP1IN_SIZE      64
#define EP1OUT_SIZE     64
#define EP2IN_SIZE      64

//<<AICUBE_USER_DEFINE_END>>


#define __ENCODING              "UTF-8" //DO NOT DELETE or MODIFY


#define HIRC                    48000000UL
#define FOSC                    system_clock_freq
#define SYSCLK                  FOSC
#define MAIN_Fosc               FOSC

#include <stc32g144k246.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <intrins.h>

#include "def.h"
#include "stc32g144k246_def.h"


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含  
//<<AICUBE_USER_INCLUDE_END>>





//<<AICUBE_USER_EXTERNAL_DECLARE_BEGIN>>
// 在此添加用户外部函数和外部变量声明  
//<<AICUBE_USER_EXTERNAL_DECLARE_END>>


#endif
