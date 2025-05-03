#ifndef USER_ADC_H_
#define USER_ADC_H_

#include "device.h"
#include "sci.h"
#include "micro_printf.h"
#include "F28x_Project.h"
#include "FPU_RFFT.h"
#include "FPU_CFFT.h"
#include "FPU_FFT_HAMMING.h"
#include "fastrts.h"
#include "dsp.h"
#include "micro_printf.h"
#include "USART.h"
#include "OLED_I2C.h"
#include "math.h"

#define sampledot   1024
#define FFT_STAGES  (10U)
#define FFT_LENGTH  (1<<FFT_STAGES)
#define ADC_Fre     102400
#define SYS_CLK     100000000

void ADC_Init(void);
void EPWM_Fre_Init(uint32_t Fre);
void ADCSOC_Init(void);
void ADC_EPWM_Init(void);
void ADC_Start(void);
float Get_amp(uint16_t* ADC_GetValue);
void FFT_Init(void);
void Get_Show_THD(float *temp);
__interrupt void adcA1ISR(void);


#endif
