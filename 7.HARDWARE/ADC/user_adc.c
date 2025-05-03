#include "user_adc.h"


uint16_t index = 0;                                             // 下标
uint16_t bufferFull = 0;                                        // 指示缓冲区已满的标志
extern uint16_t fft_flag;                                       // 指示缓冲区已满的标志

uint16_t ADC_GetValue              [sampledot]               = {0};    // 结果缓冲区

#pragma DATA_SECTION(fft_inputbuf   , "FFT_buffer1")
#pragma DATA_SECTION(fft_outputbuf  , "FFT_buffer2")

float       fft_inputbuf            [FFT_LENGTH*2   ]        = {0};
float       fft_outputbuf           [FFT_LENGTH     ]        = {0};    //FFT输出数组
float       fft_twiddleFactors      [FFT_LENGTH     ]        = {0};
float       fft_phase               [FFT_LENGTH     ]        = {0};
//const float fftWindow             [FFT_LENGTH     ]        = HAMMING1024;

CFFT_F32_STRUCT cfft;
CFFT_F32_STRUCT_Handle hnd_cfft = &cfft;

void ADC_Init(void)
{
    // 将VREF设置为内部
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
    EALLOW;
    // 将ADCCLK分频器设置为/4
    AdcaRegs.ADCCTL2.bit.PRESCALE    = 6;
    // 将脉冲位置设置为较晚
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    // 接通ADC电源，然后延迟1毫秒
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ    = 1;
    EDIS;
    delay_us(1000);
}

void EPWM_Fre_Init(uint32_t Fre)
{
    uint16_t CNT = SYS_CLK/(2*Fre);
    EALLOW;
    EPwm1Regs.ETSEL.bit.SOCAEN     = 0;              // 禁用A组上的SOC
    EPwm1Regs.ETSEL.bit.SOCASEL    = 4;              // 在递增计数时选择SOC
    EPwm1Regs.ETPS.bit.SOCAPRD     = 1;              // 在第一个事件上生成脉冲

    EPwm1Regs.TBCTL.bit.SYNCOSEL   = TB_CTR_ZERO;    //SYNCO失能
    EPwm1Regs.TBCTL.bit.PHSEN      = TB_ENABLE;      //相位失能（因为并不用到同位功能）
    EPwm1Regs.TBPHS.bit.TBPHS      = 0x0000;         //设置计数器相位为0
    EPwm1Regs.TBCTR                = 0x0000;         //初始化计数器计数值
    EPwm1Regs.TBPRD                = CNT;            //设置周期值
    EPwm1Regs.TBCTL.bit.CTRMODE    = 3;              //0：增计数       1：减计数      2：增减计数     3：停止计数
    EPwm1Regs.TBCTL.bit.CLKDIV     = TB_DIV1;        //TBCLK=SYSCLKOUT/(CLKDIV*HSPCLKDIV)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV  = TB_DIV1;        //TBCLK=SYSCLKOUT/(CLKDIV*HSPCLKDIV)

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;              //将CMPA寄存器设置为映射加载模式
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0;              //将在TBCTR=0时重装载映射寄存器中的值
    EPwm1Regs.CMPA.bit.CMPA        = CNT/2;          //占空比设定

    EDIS;
}

// initADCSOC-用于将ADCA的SOC0配置为由ePWM1触发的功能。
void ADCSOC_Init(void)
{
    // 选择要转换的通道和转换结束标志
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL       = 2;        // SOC0将转换引脚A1
                                                    // 0:A0   1:A1   2:A2   3:A3
                                                    // 4:A4   5:A5   6:A6   7:A7
                                                    // 8:A8   9:A9   A:A10  B:A11
                                                    // C:A12  D:A13  E:A14  F:A15
    AdcaRegs.ADCSOC0CTL.bit.ACQPS       = 10-1;     // 示例窗口为10个SYSCLK周期
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL     = 5;        // ePWM1 SOCA上的触发器

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL   = 0;        // SOC0结束将设置INT1标志
    AdcaRegs.ADCINTSEL1N2.bit.INT1E     = 1;        // 启用INT1标志
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1   = 1;        // 确保INT1标志已清除

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL   = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT1E     = 1;        // 启用INT1标志
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1   = 1;        // 确保INT1标志已清除

    EDIS;
}

void ADC_EPWM_Init(void)
{
    EALLOW;
    PieVectTable.ADCA1_INT = &adcA1ISR;     // Function for ADCA interrupt 1
    EDIS;
    ADC_Init();
    EPWM_Fre_Init(ADC_Fre);
    ADCSOC_Init();
    IER |= M_INT1;  // Enable group 1 interrupts
    PieCtrlRegs.PIEIER1.bit.INTx1    = 1;
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
}

void ADC_Start(void)
{
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;    // Enable SOCA
    EPwm1Regs.TBCTL.bit.CTRMODE = 2;    // Unfreeze, and enter up count mode
    // Wait while ePWM causes ADC conversions, which then cause interrupts,
    // which fill the results buffer, eventually setting the bufferFull
    // flag
    while(!bufferFull)
    {
    }
    bufferFull = 0;
    //clear the buffer full flag
    // Stop ePWM
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;   // Disable SOCA    0
    EPwm1Regs.TBCTL.bit.CTRMODE = 2;   // Freeze counter  3
    // Software breakpoint. At this point, conversion results are stored in
    // adcAResults.
    // Hit run again to get updated conversions.
    ESTOP0;
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

void FFT_Calculate(void)
{
    float *p_temp;
    float max;
    float amp;

    uint8_t  buf[50];
    uint16_t i = 0;
    uint16_t max_idx;
    uint16_t fre;

    amp = Get_amp(ADC_GetValue);

    for(i=0;i<FFT_LENGTH;i++)//生成信号序列
    {
        fft_inputbuf[2*i]    = (float)ADC_GetValue[i]*3.3f/4095.0f;    //实部为ADC采样值
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

     fre = ADC_Fre/sampledot * max_idx;

     //OLED显示
     OLED_ShowInt  (40,2,fre,2);
     OLED_ShowFloat(40,4,amp,2);
     Get_Show_THD  (p_temp);
}

__interrupt void adcA1ISR(void)
{
    uint16_t i = 0;
    // 将最新结果添加到缓冲区
    // ADCRESULT0是SOC0的结果寄存器
    ADC_GetValue[index++] = AdcaResultRegs.ADCRESULT0;
    // 如果缓冲区已满，请设置bufferFull标志
    // 清除中断标志
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    // 检查是否发生溢出
    if(AdcaRegs.ADCINTOVF.bit.ADCINT1 == 1 )
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //清除INT1溢出标志
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //清除INT1标志
    }
    // 确认中断
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    if(index >= sampledot)
    {
        index = 0;
        bufferFull = 1;
        for(i = 0;i<sampledot;i++)
        {
            micro_print("%d\r\n",ADC_GetValue[i]);
        }
        FFT_Calculate();
        fft_flag = 1;
    }
}

