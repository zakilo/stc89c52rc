#include <REGX52.H>
#include "type_def.h"
#include "timer0.h"
#include "clock_DS1302.h"
#include "nexie2.h"
#include "btn4.h"

U8 gMode = 0; // 0 as HH:MM:SS, 1 as YY-MM-DD
U16 gTimerDelay = 500; // ms
U8 gDelayTotal = 6, gDelayCnt = 0;

void time0Routine(void) {
    if (gDelayCnt == 0) {        
        gMode = checkBtnPressedAt(1) | checkBtnPressedAt(2) | checkBtnPressedAt(3) | checkBtnPressedAt(4);
        if (gMode) gDelayCnt = gDelayTotal;
    }

    if (gDelayCnt > 0) --gDelayCnt;
}

void showTime(void) {
    PU8 time = NULL;
    U8 nexieNum[8] = {0}, i = 0;
    
    time = readTimeClockDS1302();
    if (gMode == 0) {
        nexieNum[0] = time[0] & 0x0F;
        nexieNum[1] = (time[0] & 0xF0) >> 4;
        nexieNum[2] = 10;
        nexieNum[3] = time[1] & 0x0F;
        nexieNum[4] = (time[1] & 0xF0) >> 4;
        nexieNum[5] = 10;
        nexieNum[6] = time[2] & 0x0F;
        nexieNum[7] = (time[2] & 0xF0) >> 4;
    } else {
        nexieNum[0] = time[3] & 0x0F;
        nexieNum[1] = (time[3] & 0xF0) >> 4;
        nexieNum[2] = time[4] & 0x0F;
        nexieNum[3] = (time[4] & 0xF0) >> 4;
        nexieNum[4] = time[6] & 0x0F;
        nexieNum[5] = (time[6] & 0xF0) >> 4;
        nexieNum[6] = 0;
        nexieNum[7] = 2;
    }
    
    for(i = 0; i < 8; ++i) {
        markNumNexie(i+1, nexieNum[i]);
    }
}

void main(void) {
    initClockDS1302();
    initTimer0(gTimerDelay, time0Routine);

    while(1) {
        showTime();
    }
}