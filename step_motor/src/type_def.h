#ifndef __MY_TYPE_DEF_H__
#define __MY_TYPE_DEF_H__

#define NULL 0
#define BYTE_SIZE 8

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;

typedef unsigned char * PU8;
typedef unsigned short * PU16;
typedef unsigned long * PU32;

typedef int (* Callable)(void);
typedef void (* Runable)(void);

#endif