#include <reg52.h>
#include "btn4.h"
#include "timer0.h"

sbit dcMotorSwitch = P1^0;

U8 gMode = 0, gTotalMode = 3;
U16 gTimerDelay = 500; // ms
U8 gDelayTotal = 1, gDelayCnt = 0;

U8 calcDelayCnt(U8 mode) {
    return (mode - 1) * (mode - 1);
}

void time0Routine(void) {
    U8 pressedBtn;
    if (gDelayCnt > 0) {
        dcMotorSwitch = 1;
        --gDelayCnt;
        return;
    }

    dcMotorSwitch = 0;
    pressedBtn = getPressedBtnNum();
    if (pressedBtn > 0) {
        gMode = pressedBtn;
    }
    if (gMode > 0) {
        gDelayCnt = calcDelayCnt(gMode);
    }
}

void main(void) {
    dcMotorSwitch = 0;
    initTimer0(10, time0Routine);
    while(1) {
    }
}