#include "ADC_Multiple.h"

#pragma DATA_SECTION(ADC1_GetValue, "ramgs0");
#pragma DATA_SECTION(ADC2_GetValue, "ramgs0");

#pragma DATA_SECTION(fft_inputbuf   , "FFT_buffer1")
#pragma DATA_SECTION(fft_outputbuf  , "FFT_buffer2")

uint16_t i      = 0;
uint16_t index1 = 0;                                            // 下标
uint16_t index2 = 0;

uint16_t ADC1_GetValue       [sampledot]              = {0};    // 结果缓冲区
uint16_t ADC2_GetValue       [sampledot]              = {0};    // 结果缓冲区

extern      uint16_t    fft_flag;
float       fft_inputbuf            [FFT_LENGTH*2   ]        = {0};
float       fft_outputbuf           [FFT_LENGTH     ]        = {0};    //FFT输出数组
float       fft_twiddleFactors      [FFT_LENGTH     ]        = {0};
float       fft_phase               [FFT_LENGTH     ]        = {0};
//const float fftWindow             [FFT_LENGTH     ]        = HAMMING1024;

CFFT_F32_STRUCT cfft;
CFFT_F32_STRUCT_Handle hnd_cfft = &cfft;

void ADC_init(void)
{
    ADC_setVREF                 (ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    ADC_setPrescaler            (ADCA_BASE, ADC_CLK_DIV_2_0);
    ADC_setInterruptPulseMode   (ADCA_BASE, ADC_PULSE_END_OF_CONV);
    ADC_enableConverter         (ADCA_BASE);
    DEVICE_DELAY_US(5000);

    ADC_disableBurstMode        (ADCA_BASE);
    ADC_setSOCPriority          (ADCA_BASE, ADC_PRI_ALL_ROUND_ROBIN);

    ADC_setupSOC                (ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, 8U);
    ADC_setInterruptSOCTrigger  (ADCA_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
    ADC_setupSOC                (ADCA_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN6, 8U);
    ADC_setInterruptSOCTrigger  (ADCA_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_NONE);

    ADC_setInterruptSource      (ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER6);
    ADC_clearInterruptStatus    (ADCA_BASE, ADC_INT_NUMBER1);
//    ADC_disableContinuousMode   (ADCA_BASE, ADC_INT_NUMBER1);
    ADC_enableContinuousMode    (ADCA_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt         (ADCA_BASE, ADC_INT_NUMBER1);
}

void ASYSCTL_init(void)
{
    ASysCtl_disableTemperatureSensor();
    ASysCtl_setAnalogReferenceInternal( ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC );
    ASysCtl_setAnalogReference1P65( ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC );
}

void INTERRUPT_init(void)
{
    Interrupt_register  (INT_ADCA1, &adcA1ISR);
    Interrupt_enable    (INT_ADCA1);
}

void EPWM_init(uint32_t Fre)
{
    uint16_t CNT = SYS_CLK/(2*Fre);

    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, CNT/2);
    EPWM_setTimeBasePeriod(EPWM1_BASE, CNT);

    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

void ADC_Multiple_Init(void)
{
    FFT_Init();
    ADC_init();
    ASYSCTL_init();
    INTERRUPT_init();
    EPWM_init                   (ADC_Fre);
    Interrupt_enable            (INT_ADCA1);
    EPWM_enableADCTrigger       (EPWM1_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode (EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);

}

float Get_amp(uint16_t* ADC_GetValue)
{
    uint16_t i;
    float max=0,min=4096;
    float amp;
    for(i=0;i<sampledot-1;i++)
    {
        if((uint16_t)(ADC_GetValue[i])>max)
                max=(uint16_t)(ADC_GetValue[i]);
        if((uint16_t)(ADC_GetValue[i])<min)
                min=(uint16_t)(ADC_GetValue[i]);
    }
    amp=(max-min)*3.3/4095.0f;
    //OLED_ShowFloat(0,4,max*3.3/4095.0f,2);
    //OLED_ShowFloat(80,4,min*3.3/4095.0f,2);
    return amp;
}

void FFT_Init(void)
{
    CFFT_f32_setInputPtr    (hnd_cfft, fft_inputbuf);
    CFFT_f32_setOutputPtr   (hnd_cfft, fft_outputbuf);
    CFFT_f32_setStages      (hnd_cfft, FFT_STAGES);
    CFFT_f32_setFFTSize     (hnd_cfft, FFT_LENGTH);

    CFFT_f32_setTwiddlesPtr (hnd_cfft, fft_twiddleFactors);
    CFFT_f32_sincostable    (hnd_cfft);
}

void wave_determine(float THD)
{
    if(THD < 5.0f)
    {
        wave_show(sine);
    }
    else if(THD > 5.0f && THD <20.0f)
    {
        wave_show(tri);
    }
    else if(THD > 20.0f && THD <45.0f)
    {
        wave_show(squ);
    }
}

void Get_Show_THD(float *temp)
{
    float max[5],k[5];
    float THD;
    uint32_t i,j,l,l1;
    for (i=2;i<1022;i++)
    {
        if ((temp[i]>200)&&(temp[i]>2*temp[i-1])&&(temp[i]>=temp[i+1]))
        {
            break;
        }
    }
    max[0]=temp[i];
    for (j=1;j<5;j++)
    {
        float buf;
        k[0] = temp[(j+1)*i-2];
        k[1] = temp[(j+1)*i-1];
        k[2] = temp[(j+1)*i];
        k[3] = temp[(j+1)*i+1];
        k[4] = temp[(j+1)*i+2];
        for (l=0; l<4 ; ++l)                                //比较n-1轮
        {
            for (l1=0; l1<4-l; ++l1)                        //每轮比较n-1-i次,
            {
                if (k[l1] < k[l1+1])
                {
                    buf = k[l1];
                    k[l1] = k[l1+1];
                    k[l1+1] = buf;
                }
            }
        }
    max[j]=k[0];
    }
    for (i=0;i<5;i++)
    {
        if (max[i]<8)
        {
            max[i]=0;
        }
        if (max[i]>50000)
        {
            max[i]=0;
        }
    }
    THD = sqrtf(max[1]*max[1]+ max[2]*max[2] + max[3]*max[3] + max[4]*max[4] );
    THD = THD/max[0];
    THD = THD*100;
    wave_determine(THD);
    OLED_ShowFloat(40,6,THD,2);
}

float Angel_Calculate(uint16_t max_idex)
{
    uint16_t i;
    float phase1,phase2;
    float angel;

    for(i=0;i<FFT_LENGTH;i++)//生成信号序列
    {
        fft_inputbuf[2*i]    = (float)ADC1_GetValue[i]*3.3f/4095.0f;    //实部为ADC采样值
        fft_inputbuf[2*i+1]  = 0;                                       //实部为ADC采样值
    }
//  CFFT_f32_win_dual(&fft_inputbuf[0], (float *)&fftWindow, FFT_LENGTH);
    CFFT_f32        (hnd_cfft);                    // Calculate FFT
    phase1 = atan2f(fft_inputbuf[2*max_idex+1],fft_inputbuf[2*max_idex])*180.0f/3.1415926f;

    for(i=0;i<FFT_LENGTH;i++)//生成信号序列
    {
        fft_inputbuf[2*i]    = (float)ADC2_GetValue[i]*3.3f/4095.0f;    //实部为ADC采样值
        fft_inputbuf[2*i+1]  = 0;                                       //实部为ADC采样值
    }
//  CFFT_f32_win_dual(&fft_inputbuf[0], (float *)&fftWindow, FFT_LENGTH);
    CFFT_f32        (hnd_cfft);                    // Calculate FFT
    phase2 = atan2f(fft_inputbuf[2*max_idex+1],fft_inputbuf[2*max_idex])*180.0f/3.1415926f;

    angel=phase2-phase1;
    if(angel>180)  angel=angel-180;
    if(angel<-180) angel=angel+180;
    return angel;
}

void FFT_Calculate(void)
{
    float *p_temp;
    float max;
    float amp1,amp2;
    float angel=0;

    uint8_t  buf[50];
    uint16_t i = 0;
    uint16_t max_idx;
    uint16_t fre1,fre2;

    amp1 = Get_amp(ADC1_GetValue);
    amp2 = Get_amp(ADC2_GetValue);

    for(i=0;i<FFT_LENGTH;i++)//生成信号序列
    {
        fft_inputbuf[2*i]    = (float)ADC1_GetValue[i]*3.3f/4095.0f;    //实部为ADC采样值
        fft_inputbuf[2*i+1]  = 0;                                      //实部为ADC采样值
    }
//  CFFT_f32_win_dual(&fft_inputbuf[0], (float *)&fftWindow, FFT_LENGTH);
    CFFT_f32        (hnd_cfft);                    // Calculate FFT
    CFFT_f32_mag    (hnd_cfft);
    p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);

    max = 0.0f;
    max_idx = 1;
    for(i = 1 ; i < FFT_LENGTH/2; i++)
    {
        if(p_temp[i] > max)
        {
            max = p_temp[i];
            max_idx = i;
        }
     }
    if(max < 20.0f)
        max_idx = 0;

    //测试打印ADC1的频谱
//    for(i = 1 ; i < FFT_LENGTH/2; i++)
//    {
//        myftoa(p_temp[i],buf);
//        USART_WriteLine(buf);
//    }

     fre1 = ADC_Fre/sampledot * max_idx;

     for(i=0;i<FFT_LENGTH;i++)//生成信号序列
     {
         fft_inputbuf[2*i]    = (float)ADC2_GetValue[i]*3.3f/4095.0f;    //实部为ADC采样值
         fft_inputbuf[2*i+1]  = 0;                                       //实部为ADC采样值
     }
//   CFFT_f32_win_dual(&fft_inputbuf[0], (float *)&fftWindow, FFT_LENGTH);
     CFFT_f32        (hnd_cfft);                    // Calculate FFT
     CFFT_f32_mag    (hnd_cfft);
     p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);

     max = 0.0f;
     max_idx = 1;
     for(i = 1 ; i < FFT_LENGTH/2; i++)
     {
         if(p_temp[i] > max)
         {
             max = p_temp[i];
             max_idx = i;
         }
      }
     if(max < 20.0f)
         max_idx = 0;

     fre2 = ADC_Fre/sampledot * max_idx;


     angel = Angel_Calculate(max_idx);
//     myftoa(angel,buf);
//     USART_WriteLine(buf);
     //OLED显示(双路)
     OLED_ShowFloat(0,0,amp1,2);
     OLED_ShowInt  (64,0,fre1,2);
     OLED_ShowFloat(0,2,amp2,2);
     OLED_ShowInt  (64,2,fre2,2);
     OLED_ShowFloat(0,6,angel,2);
}

__interrupt void adcA1ISR(void)
{

    ADC1_GetValue[index1++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);
    ADC2_GetValue[index2++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER6);
    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    if(index1 >= sampledot)
    {
        index1 = 0;
        index2 = 0;

//        for(i = 0;i<sampledot;i++)
//        {
//            micro_print("%d,%d\r\n",ADC1_GetValue[i],ADC2_GetValue[i]);
//        }

        FFT_Calculate();
        fft_flag = 1;
//        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    }
}
