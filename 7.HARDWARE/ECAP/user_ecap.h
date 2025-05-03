#ifndef USER_ECAP_H_
#define USER_ECAP_H_

#include "driverlib.h"
#include "USART.h"
#include "micro_printf.h"

#define SYS_CLK     100000000

void ECAP_Init(void);
__interrupt void INT_ECAP_ISR(void);

#endif
