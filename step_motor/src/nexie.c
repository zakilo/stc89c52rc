#include <REGX52.H>
#include "type_def.h"
#include "nexie.h"

// com positive
U8 nexieNumCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delayXms(U16 x) {
    while(x--) {
        int i = 300;
        while(--i);
    }
}

/**
 * notice that position value start from 1, and read it from right to left on nexieTube.
 */
void setNexie(U8 position, U8 value) {
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
