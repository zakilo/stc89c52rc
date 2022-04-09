#include <REGX52.H>
#include "my_lib.h"

#define FOSC 11059200
#define T1MS (65536 - FOSC/12/1000) //1ms timer calculation method in 12T mode

U8 count = 0;

sbit TEST_LED = P2^0;

void timer0_routine(void) interrupt 1 {
    // timer count init
    TL0 = T1MS;
    TH0 = T1MS >> 8;
    if(count-- == 0) {
        if (checkBtnPressedAt(1)) {
            P2_1 = !P2_1;
        }
        if(checkBtnPressedAt(2)) {
            P2_2 = !P2_2;
        }
        TEST_LED = !TEST_LED;
    }
}

void int0_init(void) {
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
}

void main(void) {
    int0_init();
    P2 = 0xFF;
    while(1);
}