#include <REGX52.H>
#include "type_def.h"
#include "clock_DS1302.h"

sbit DS1302_CLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

U8 gCLK_BYTE_SIZE = CLK_BYTE_SIZE;

//---DS1302 写入和读取时分秒的地址命令---//
U8 gWRITE_SAFE_ADDR = 0x8E;
U8 gWRITE_SAFE_SWITCH[2] = {0x80, 0x00}; // 0x00 open write, 0x80 close write
//---秒分时日月周年 最低位读写位;-------//
U8 gREAD_RTC_ADDR[CLK_BYTE_SIZE] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
U8 gWRITE_RTC_ADDR[CLK_BYTE_SIZE] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
//---DS1302 时钟初始化 2022 年 4 月 11 日星期一 00 点 59 分 47 秒。---//
//---存储顺序是秒分时日月周年,存储格式是用 BCD 码---//
U8 gDS1302_TIME[CLK_BYTE_SIZE] = {0x00, 0x00, 0x00, 0x11, 0x04, 0x01, 0x22};

void noop(void) {
//    U8 i = 0;
//    while(++i < 10);
}

void initClockDS1302(void) {
    U8 i = 0;
    writeTimeClockDS1302(gDS1302_TIME);
}

PU8 readTimeClockDS1302(void) {
    U8 i = 0;
    U8 time[CLK_BYTE_SIZE] = {0};
    for (i = 0; i < gCLK_BYTE_SIZE; ++i) {
        time[i] = readByteClockDS1302(gREAD_RTC_ADDR[i]);
    }
    return time;
}

void writeTimeClockDS1302(U8 time[CLK_BYTE_SIZE]) {
    U8 i = 0;
    writeByteClockDS1302(gWRITE_SAFE_ADDR, gWRITE_SAFE_SWITCH[1]);
    for (i = 0; i < gCLK_BYTE_SIZE; ++i) {
        writeByteClockDS1302(gWRITE_RTC_ADDR[i], time[i]);
    }
    writeByteClockDS1302(gWRITE_SAFE_ADDR, gWRITE_SAFE_SWITCH[0]);
}

U8 readByteClockDS1302(U8 clockAddr) {
    U8 i = 0, v = 0x00;
    DS1302_CE = 0;
    // noop();
    DS1302_CLK = 0;
    // noop();
    DS1302_CE = 1;
    // noop();
    
    for(i = 0; i < BYTE_SIZE; ++i) {
        DS1302_IO = clockAddr & (0x01 << i);
        
        DS1302_CLK = 1;
        // noop();
        DS1302_CLK = 0;
        // noop();
    }
    for(i = 0; i < BYTE_SIZE; ++i) {
        if (DS1302_IO) {
            v |= 0x01 << i;
        }

        DS1302_CLK = 1;
        // noop();
        DS1302_CLK = 0;
        // noop();
    }
    
    DS1302_CE = 0;
    // noop();
    DS1302_IO = 0;
    // noop();
    return v;
}

void writeByteClockDS1302(U8 clockAddr, U8 clockData) {
    U8 i = 0;
    DS1302_CE = 0;
    // noop();
    DS1302_CLK = 0;
    // noop();
    DS1302_CE = 1;
    // noop();
    
    for(i = 0; i < BYTE_SIZE; ++i) {
        DS1302_IO = clockAddr & (0x01 << i);
        
        DS1302_CLK = 1;
        // noop();
        DS1302_CLK = 0;
        // noop();
    }
    for(i = 0; i < BYTE_SIZE; ++i) {
        DS1302_IO = clockData & (0x01 << i);

        DS1302_CLK = 1;
        // noop();
        DS1302_CLK = 0;
        // noop();
    }
    
    DS1302_CE = 0;
}
