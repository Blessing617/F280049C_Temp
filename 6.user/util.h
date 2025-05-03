#ifndef _MY_UTIL_H
#define _MY_UTIL_H

#include "device.h"

#define MYUTIL_FLOAT_PRECISION 6

uint16_t myitoa(int64_t val, uint8_t *str, uint8_t radix);
uint8_t myftoa_FD(float val, uint8_t *str, uint8_t precision);
uint8_t myftoa(float val, uint8_t *str);
int64_t myatoi(const uint8_t *str);
int64_t myatoi_hex(const uint8_t *str);
float myatof(uint8_t *str);
void splitparam_hex(uint8_t *str, uint8_t spliter, int64_t *result, uint64_t num);
void splitparam_f(uint8_t *str, uint8_t spliter, float *result, uint64_t num);
int64_t mygcd(int64_t a, int64_t b);

#endif

