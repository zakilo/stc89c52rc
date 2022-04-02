#include <REGX52.H>

void delayXs(unsigned int x) {
    while(x--) {
        int i = 100 * 1000;
        while(--i);
    }
}

void main() {
	unsigned int v = 0x01;
    while(1) {
        P2 = ~v;
        v = v << 1;
        if (v > 0x80) {
            v = 0x01;
        }
        delayXs(1);
    }
}