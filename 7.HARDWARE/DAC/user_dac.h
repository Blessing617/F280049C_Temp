#ifndef USER_DAC_H_
#define USER_DAC_H_

#include "device.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
#include "sgen.h"
#include "micro_printf.h"

void DAC_init(void);
void DAC_Set_Value(float V);

#endif
