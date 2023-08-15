#ifndef __MY_BTN4_H__
#define __MY_BTN4_H__

#include "type_def.h"

/**
 * @param i position of btn, start from 1, left to right
 * @retval if pressed, return 1; else return 0.
 */
U8 checkBtnPressedAt(U8 i);

/**
 * get num of pressed btn
 */
U8 getPressedBtnNum();

#endif