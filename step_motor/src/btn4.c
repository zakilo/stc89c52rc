#include <REGX52.H>
#include "btn4.h"

sbit btn1 = P3^1;
sbit btn2 = P3^0;
sbit btn3 = P3^2;
sbit btn4 = P3^3;

/**
 * @param i - position of btn, start from 1, left to right
 * @retval if pressed, return 1; else return 0.
 */
U8 checkBtnPressedAt(U8 i) {
    switch(i) {
        // pos 1 and 2 are reversed
        case 1: return btn1 == 0;
        case 2: return btn2 == 0;
        case 3: return btn3 == 0;
        case 4: return btn4 == 0;
        default: return 0;
    }
}

/**
 * @retval position of pressed btn, start from 1, left to right
 */
U8 getPressedBtnNum() {
    if (btn1 == 0) {
        return 1;
    }
    if (btn2 == 0) {
        return 2;
    }
    if (btn3 == 0) {
        return 3;
    }
    if (btn4 == 0) {
        return 4;
    }
    return 0;
}
