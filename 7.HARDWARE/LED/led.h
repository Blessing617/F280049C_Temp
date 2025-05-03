#ifndef USER_LED_H_
#define USER_LED_H_

#include "driverlib.h"

#define LED1        23U  // GPIO number for LD4
#define LED2        34U  // GPIO number for LD5

#define LED1_ON             GPIO_writePin(LED1,0)  //低电平
#define LED1_OFF            GPIO_writePin(LED1,1)  //高电平
#define LED1_TOGGLE         GPIO_togglePin(LED1);  //翻转

#define LED2_ON             GPIO_writePin(LED2,0)  //低电平
#define LED2_OFF            GPIO_writePin(LED2,1)  //高电平
#define LED2_TOGGLE         GPIO_togglePin(LED2);  //翻转

void LED_Init(void);

#endif
