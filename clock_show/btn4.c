#include <REGX52.H>
#include "btn4.h"

/**
 * @param i - position of btn, start from 1, left to right
 * @retval if pressed, return 1; else return 0.
 */
U8 checkBtnPressedAt(U8 i) {
    switch(i) {
        // pos 1 and 2 are reversed
        case 1: return P3_1 == 0;
        case 2: return P3_0 == 0;
        case 3: return P3_2 == 0;
        case 4: return P3_3 == 0;
        default: return 0;
    }
}
