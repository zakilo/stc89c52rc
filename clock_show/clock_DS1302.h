#ifndef __MY_CLOCK_DS1302_H__
#define __MY_CLOCK_DS1302_H__

#include "type_def.h"

#define CLK_BYTE_SIZE 7

/**
 * init a default time
 */
void initClockDS1302(void);

/**
 * @param clockAddr - register address for read
 * @retval data read from DS1302 with BCD code
 */
U8 readByteClockDS1302(U8 clockAddr);

/**
 * @param clockAddr - register address to write
 * @param clockData - data to write with BCD code
 */
void writeByteClockDS1302(U8 clockAddr, U8 clockData);

/**
 * @retval 7 bytes time with BCD code: 秒分时日月周年
 */
PU8 readTimeClockDS1302(void);

/**
 * @param time - 7 bytes BCD code: 秒分时日月周年
 */
void writeTimeClockDS1302(U8 clockTime[CLK_BYTE_SIZE]);

#endif
