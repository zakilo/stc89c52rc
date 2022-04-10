#include <REGX52.H>
#include "timer0.h"

struct Timer0Data gTimer0Data;

void initTimer0(U16 cntMs, Runable routine) {
    EA = 1; // enable global interrupt
    ET0 = 1; // enable T0
    PT0 = 0; // low priority
    
    TMOD &= 0xF0;
    TMOD |= 0x01;
    TR0 = 1;
    TF0 = 0;
    
    // timer count init
    TL0 = T1MS;
    TH0 = T1MS >> 8;
    
    gTimer0Data.initCntMs = cntMs;
    gTimer0Data.tCntMs = cntMs;
    gTimer0Data.tRoutine = routine;
}

void timer0Routine(void) interrupt 1 {
    // timer count init
    TL0 = T1MS;
    TH0 = T1MS >> 8;
    if(gTimer0Data.tCntMs-- == 0) {
        gTimer0Data.tCntMs = gTimer0Data.initCntMs;
        (gTimer0Data.tRoutine)();
    }
}
