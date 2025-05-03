#include "user_ecap.h"
//
// Globals
//
volatile uint16_t cap2Count        = 0;
volatile uint16_t cap3Count        = 0;
volatile uint16_t cap4Count        = 0;

void ECAP_Init(void)
{
    GPIO_setPinConfig           (GPIO_3_GPIO3);
    XBAR_setInputPin            (XBAR_INPUT7, 3);

    SysCtl_setSyncOutputConfig  (SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig   (SYSCTL_SYNC_IN_EPWM4, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig   (SYSCTL_SYNC_IN_EPWM7, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig   (SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig   (SYSCTL_SYNC_IN_ECAP4, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig   (SYSCTL_SYNC_IN_ECAP6, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);

    SysCtl_enableExtADCSOCSource(0);
    SysCtl_enableExtADCSOCSource(0);

    ECAP_disableInterrupt(ECAP1_BASE,
        (       ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                ECAP_ISR_SOURCE_COUNTER_COMPARE)
        );
    ECAP_clearInterrupt(ECAP1_BASE,
        (       ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                ECAP_ISR_SOURCE_COUNTER_COMPARE)
        );

    ECAP_disableTimeStampCapture    (ECAP1_BASE);
    ECAP_stopCounter                (ECAP1_BASE);
    ECAP_enableCaptureMode          (ECAP1_BASE);
    ECAP_setCaptureMode             (ECAP1_BASE,ECAP_ONE_SHOT_CAPTURE_MODE,ECAP_EVENT_4);
    ECAP_setEventPrescaler          (ECAP1_BASE, 0U);
    ECAP_setEventPolarity           (ECAP1_BASE,ECAP_EVENT_1,ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity           (ECAP1_BASE,ECAP_EVENT_2,ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity           (ECAP1_BASE,ECAP_EVENT_3,ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity           (ECAP1_BASE,ECAP_EVENT_4,ECAP_EVNT_RISING_EDGE);

    ECAP_enableCounterResetOnEvent  (ECAP1_BASE,ECAP_EVENT_1);
    ECAP_enableCounterResetOnEvent  (ECAP1_BASE,ECAP_EVENT_2);
    ECAP_enableCounterResetOnEvent  (ECAP1_BASE,ECAP_EVENT_3);
    ECAP_enableCounterResetOnEvent  (ECAP1_BASE,ECAP_EVENT_4);
    ECAP_selectECAPInput            (ECAP1_BASE,ECAP_INPUT_INPUTXBAR7);
    ECAP_setPhaseShiftCount         (ECAP1_BASE,0U);
    ECAP_enableLoadCounter          (ECAP1_BASE);
    ECAP_setSyncOutMode             (ECAP1_BASE,ECAP_SYNC_OUT_SYNCI);
    ECAP_setEmulationMode           (ECAP1_BASE,ECAP_EMULATION_STOP);
    ECAP_startCounter               (ECAP1_BASE);
    ECAP_enableTimeStampCapture     (ECAP1_BASE);
    ECAP_reArm                      (ECAP1_BASE);
    ECAP_enableInterrupt            (ECAP1_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);

    GPIO_setPadConfig               (3, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode       (3, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode           (3, GPIO_DIR_MODE_IN);
    GPIO_setControllerCore          (3, GPIO_CORE_CPU1);

    Interrupt_register              (INT_ECAP1, &INT_ECAP_ISR);
    Interrupt_enable                (INT_ECAP1);
}

__interrupt void INT_ECAP_ISR(void)
{
    float    fre  = 0;
    float    duty = 0;
    uint8_t  buf[50];

    cap2Count = ECAP_getEventTimeStamp  (ECAP1_BASE, ECAP_EVENT_2);
    cap3Count = ECAP_getEventTimeStamp  (ECAP1_BASE, ECAP_EVENT_3);
    cap4Count = ECAP_getEventTimeStamp  (ECAP1_BASE, ECAP_EVENT_4);

    micro_print("低电平计数=%d\r\n",cap2Count);
    micro_print("高电平计数=%d\r\n",cap3Count);
    micro_print("低电平计数=%d\r\n",cap4Count);
    micro_print("总时间计数=%d\r\n",cap3Count+(cap2Count+cap4Count)/2);

    fre = SYS_CLK / (cap3Count+(cap2Count+cap4Count)/2);
    micro_print("频率=");
    myftoa(fre,buf);
    USART_WriteLine(buf);
    duty = (float)cap3Count /  (float)(cap3Count+(cap2Count+cap4Count)/2) * 100.0f;
    micro_print("占空比=");
    myftoa(duty,buf);
    USART_WriteLine(buf);

    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;

    ECAP_clearInterrupt                 (ECAP1_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt           (ECAP1_BASE);
    ECAP_reArm                          (ECAP1_BASE);
    Interrupt_clearACKGroup             (INTERRUPT_ACK_GROUP4);
}

