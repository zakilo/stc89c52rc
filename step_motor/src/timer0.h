#ifndef __MY_TIMER0_H__
#define __MY_TIMER0_H__

#include "type_def.h"

#define FOSC 11059200
#define T1MS (65536 - FOSC/12/1000) //1ms timer calculation method in 12T mode

struct Timer0Data {
    // 初始指定毫秒数
    U16 initCntMs;
    
    // 运行时毫秒计数
    U16 tCntMs;
    
    // 定时调用函数
    Runable tRoutine;
};

/**
 * run routine every cntMs ms.
 */
void initTimer0(U16 cntMs, Runable routine);

#endif
