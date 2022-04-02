#include <REGX52.H>
#include "my_lib.h"

// com positive
U8 nexieNumCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

/**
 * notice that position value start from 1, and read it from right to left on nexieTube.
 */
void markNum(U8 position, U8 value) {
    U8 actPos = (position > 0 && position < 9) ? (position - 1) : 0;
    P2 = 0x00;
    P2_2 = actPos & 0x01;
    P2_3 = actPos & 0x02;
    P2_4 = actPos & 0x04;

    if (value < 10) {
        P0 = nexieNumCode[value];
    }
    
    delayXms(1);
    P0 = 0;
}

void main() {
    U16 value = 0;
    int i = 0;
    U16 j, k, m, n;
    while(1) {
        if (checkBtnPressedAt(1)) {
            ++value;
        }
        if (checkBtnPressedAt(2)) {
            --value;
        }
        if (checkBtnPressedAt(3)) {
            value <<= 1;
        }
        if (checkBtnPressedAt(4)) {
            value >>= 1;
        }
        
        m = 10;
        n = 1;
        for (i = 0; i < 4; ++i) {
            markNum(i + 1, value % m / n);
            m *= 10;
            n *= 10;
        }
    }
}
