#ifndef MY_LIB_H
#define MY_LIB_H

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;


/**
 * 4 buttons, start from 1;
 * if pressed, return 1; else return 0.
 */
U8 checkBtnPressedAt(U8 i);

#endif
