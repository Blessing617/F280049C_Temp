#ifndef USER_ADC_Multiple_H_
#define USER_ADC_Multiple_H_

#include "device.h"
#include "sci.h"
#include "micro_printf.h"

#include "FPU_CFFT.h"
#include "FPU_FFT_HAMMING.h"
#include "fastrts.h"
#include "dsp.h"
#include "math.h"

#include "OLED_I2C.h"
#include "USART.h"
#include "micro_printf.h"

#define sampledot   1024
#define FFT_STAGES  (10U)
#define FFT_LENGTH  (1<<FFT_STAGES)
#define ADC_Fre     102400
#define SYS_CLK     100000000

void ADC_Multiple_Init(void);

float Get_amp(uint16_t* ADC_GetValue);
void FFT_Init(void);
void wave_determine(float THD);
void Get_Show_THD(float *temp);
float Angel_Calculate(uint16_t max_idex);
void FFT_Calculate(void);

__interrupt void adcA1ISR(void);
__interrupt void dmach1ISR(void);

#endif
