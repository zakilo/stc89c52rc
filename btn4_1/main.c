#include <REGX52.H>

void delayXms(unsigned int x) {
    while(x--) {
        int i = 300;
        while(--i);
    }
}

/**
 * if pressed, return true; or else return false.
 */
int checkBtnPressedAt(int i) {
    switch(i) {
        // pos 1 and 2 are reversed
        case 1:
            if (P3_1 == 0) {
                delayXms(20);
                while(P3_1 == 0);
                delayXms(20);
                return 1;
            }
            return 0;
        case 2:
            if (P3_0 == 0) {
                delayXms(20);
                while(P3_0 == 0);
                delayXms(20);
                return 1;
            }
            return 0;
        case 3:
            if (P3_2 == 0) {
                delayXms(20);
                while(P3_2 == 0);
                delayXms(20);
                return 1;
            }
            return 0;
        case 4:
            if (P3_3 == 0) {
                delayXms(20);
                while(P3_3 == 0);
                delayXms(20);
                return 1;
            }
            return 0;
        default: return 0;
    }
}

void main() {
    unsigned char v = 0;
    while(1) {
        if (checkBtnPressedAt(1)) {
            P2 = ~(++v);
        }
        if (checkBtnPressedAt(2)) {
            P2 = ~(--v);
        }
        if (checkBtnPressedAt(3)) {
            v >>= 1;
            P2 = ~v;
        }
        if (checkBtnPressedAt(4)) {
            v <<= 1;
            P2 = ~v;
        }
    }
}