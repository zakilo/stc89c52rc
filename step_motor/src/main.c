#include <REGX52.H>
#include "btn4.h"
#include "timer0.h"
#include "nexie.h"

#define MOTOR_CIRCIL_RATE 4096
#define MOTOR_STATUS_START 0xFE
#define MOTOR_STATUS_END 0xF7

sbit step_monitor_a = P1^0;
sbit step_monitor_b = P1^1;
sbit step_monitor_c = P1^2;
sbit step_monitor_d = P1^3;

U8 gMode = 0, gDirection = 0, gSpeed = 0;
U8 gTotalStep = 8;
U8 gDelayTotal = 1, gDelayCnt = 0;

U8 gMonitorStatus = MOTOR_STATUS_START;
U8 gMonitorStep1 = MOTOR_STATUS_START;
U8 gMonitorStep2 = MOTOR_STATUS_START;
U16 gMonitorLoopCnt = 0;

/**
 * Motor actions
 * see oneLoopMotor(), turnDirection()
*/
U8 nextStep() {
    if (gMonitorStep1 == gMonitorStep2) {
        // loop shift left
        if (gMonitorStep2 == MOTOR_STATUS_END) {
            ++gMonitorLoopCnt;
        }
        gMonitorStep2 = gMonitorStep2 == MOTOR_STATUS_END ? MOTOR_STATUS_START : ((gMonitorStep2 << 1) | 0x01);
    } else {
        gMonitorStep1 = gMonitorStep2;
    }
    gMonitorStatus = gMonitorStep1 & gMonitorStep2;
    return gMonitorStatus;
}

U8 prevStep() {
    if (gMonitorStep1 == gMonitorStep2) {
        // loop shift left
        gMonitorStep2 = gMonitorStep2 == MOTOR_STATUS_START ? MOTOR_STATUS_END : ((gMonitorStep2 >> 1) | 0x80);
        if (gMonitorStep2 == MOTOR_STATUS_START) {
            ++gMonitorLoopCnt;
        }
    } else {
        gMonitorStep1 = gMonitorStep2;
    }
    gMonitorStatus = gMonitorStep1 & gMonitorStep2;
    return gMonitorStatus;
}

void setMotorStatus(U8 statusInLow4) {
    step_monitor_a = statusInLow4 & 0x01;
    step_monitor_b = statusInLow4 & 0x02;
    step_monitor_c = statusInLow4 & 0x04;
    step_monitor_d = statusInLow4 & 0x08;
}

void oneLoopMotor() {
    U8 i = gTotalStep;
    U8 status;
    while(--i > 0) {
        status = gDirection ? prevStep() : nextStep();
        setMotorStatus(status);
    }
}

void turnDirection() {
    gDirection = !gDirection;
}

/**
 * Timer actions
 * see moveMotor()
*/
U8 calcDelayCnt(U8 speed) {
    return (3 - speed) * 2;
}

void moveMotor() {
    U8 pressedBtn = getPressedBtnNum();
    switch (pressedBtn) {
    case 1:
        gSpeed = 0;
        gDelayCnt = 0;
        gMode = !gMode;
        break;
    case 2:
        turnDirection();
        break;
    case 3:
        gSpeed = gSpeed < 3 ? (gSpeed + 1) : 3;
        gDelayCnt = calcDelayCnt(gSpeed);
        break;
    case 4:
        gSpeed = gSpeed > 1 ? (gSpeed - 1) : 1;
        gDelayCnt = calcDelayCnt(gSpeed);
        break;
    default:
        break;
    }
}

/**
 * Nexie actions
 * see showMotorLoopCnt(), showStatus()
*/
void showMotorLoopCnt() {
    U8 i = 0;
    U16 cnt = gMonitorLoopCnt;
    while(++i <= 5) {
        setNexie(i, cnt % 10);
        cnt /= 10;
    }
}

void showStatus() {
    setNexie(6, gMode);
    setNexie(7, gSpeed);
    setNexie(8, gDirection);
}

/**
 * Main action
*/
void time0Routine(void) {
    moveMotor();
}

/**
 * this module will operator a step-motor with follow actions:
 * 1. btn1 ctrl start or stop;
 * 2. btn2 ctrl turn left or right;
 * 3. btn3 ctrl speed up while max 3;
 * 4. btn4 ctrl speed down while min 1.
 * 
 * And you will see:
 * 1. nexie pos 8 show direction to left(0) or right(1);
 * 2. nexie pos 7 show speed level, between 1 and 3;
 * 3. nexie pos 6 show motor start(1) or stop(0);
 * 4. nexie pos 5 to 1 show count of circles.
*/
void main(void) {
    setMotorStatus(MOTOR_STATUS_START);
    initTimer0(200, time0Routine);
    while(1) {
        showStatus();
        showMotorLoopCnt();
        if (gMode == 0) {
            continue;
        }

        oneLoopMotor();
        delayXms(gDelayCnt);
    }
}