#ifndef MICRO_PRINTF_H_
#define MICRO_PRINTF_H_

//#include "Includes.h"
#include <stddef.h>
#include <stdarg.h>
#include "driverlib.h"
#include "util.h"
#define PRINTF_MAX_NUM_LEN   20                  /*最大显示位数-----*/

#define u16 unsigned int
#define u32 unsigned long
#define u64 unsigned long long

#define s16 signed int
#define s32 signed long
#define s64 signed long long

typedef union{
    float _float_;
    u16   _u16_[2];
}float_to_u16;

typedef union{
    float _float_;
    u32   _u32_;
}float_to_u32;
u32 Float_to_u32(float data);
void float_to_char(float num,uint8_t* str);
void micro_print(const char *fmt, ...);
#endif
