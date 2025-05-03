#include "F28x_Project.h"
#include "device.h"
#include "math.h"
//模块头文件
#include "led.h"
#include "key_exti.h"
#include "USART.h"
#include "micro_printf.h"
#include "OLED_I2C.h"

#include "user_adc.h"
#include "user_dac.h"
//#include "user_ecap.h"
//#include "ADC_Multiple.h"

uint16_t fft_flag   = 0;

void Board_Start(void)
{
    uint8_t i = 0;
    /*启动指示*/
    for(i = 0; i < 3; i++ )
    {
        LED1_OFF;
        LED2_OFF;
        delay_ms(500);
        LED1_ON;

        LED2_ON;
        delay_ms(500);
    }
    micro_print("启动完成\r\n");
    BackGround();
}

void main(void)
{
    //初始化时钟和外设
    Device_init();
    //GPIO初始化设置
    Device_initGPIO();
    //初始化PIE并清空PIE寄存器，关闭CPU中断
    Interrupt_initModule();
    //初始化PIE向量表
    Interrupt_initVectorTable();
    //开启总中断
    Interrupt_enableMaster();
    /*模块初始化*/
     //LED初始化
     LED_Init();
     //按键外部中断初始化
     EXTIX_Init();
     //串口初始化
     USART_Init();
     //OLED初始化
     OLED_Init();
     //板子初始化
     Board_Start();
     //DAC初始化
     DAC_init();
     DAC_Set_Value(3.3f);
     //ECAP输入捕获初始化
//     ECAP_Init();
     //DSP库初始化
     FFT_Init();
     //ADC初始化
     ADC_EPWM_Init();
     ADC_Start();
//     ADC_Multiple_Init();
     //启用全局中断（INTM）和实时中断（DBGM）
     EINT;
     ERTM;
    while(1)
    {
//        LED1_TOGGLE;
//        LED2_TOGGLE;
//        micro_print("hello\r\n");
//        delay_s(1);
//        while(!fft_flag)
//        {
//
//        }
//        fft_flag=0;
    }
}


