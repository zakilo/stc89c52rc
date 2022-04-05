#include <REGX52.H>
#include "my_lib.h"

void delayXms(U8 x) {
}

/**
 * if pressed, return 1; else return 0.
 */
U8 checkBtnPressedAt(U8 i) {
    U16 period = 20;
    switch(i) {
        // pos 1 and 2 are reversed
        case 1:
            if (P3_1 == 0) {
                delayXms(period);
                while(P3_1 == 0);
                delayXms(period);
                return 1;
            }
            return 0;
        case 2:
            if (P3_0 == 0) {
                delayXms(period);
                while(P3_0 == 0);
                delayXms(period);
                return 1;
            }
            return 0;
        case 3:
            if (P3_2 == 0) {
                delayXms(period);
                while(P3_2 == 0);
                delayXms(period);
                return 1;
            }
            return 0;
        case 4:
            if (P3_3 == 0) {
                delayXms(period);
                while(P3_3 == 0);
                delayXms(period);
                return 1;
            }
            return 0;
        default: return 0;
    }
}
