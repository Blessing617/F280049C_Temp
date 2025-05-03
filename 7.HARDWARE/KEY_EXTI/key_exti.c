#include "key_exti.h"

//
// 全局变量
//

interrupt void xint1_isr(void);
interrupt void xint2_isr(void);


////外部中断初始化
void EXTIX_Init(void)
{

    //配置三级中断  外设中断- PIE中断- CPU中断

    //
    // 本例中使用的中断被重新映射到该文件中的ISR函数。
    //
    Interrupt_register(INT_XINT1, &xint1_isr);//第一个输入的是PIE中断线，第二个是中断的函数
    Interrupt_register(INT_XINT2, &xint2_isr);//第一个输入的是PIE中断线，第二个是中断的函数
    //
    // 使能PIE中的XINT1和XINT2:   Group 1 interrupt 4 & 5
    //
    Interrupt_enable(INT_XINT1);
    Interrupt_enable(INT_XINT2);


    EINT;// 启用全局中断 CPU中断


    //设置GPIO口为输入模式
    //
    // GPIO0 and GPIO1 are inputs
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);//上拉输入
    GPIO_setDirectionMode(0,GPIO_DIR_MODE_IN);// input
    // XINT1 Synch to SYSCLKOUT only
    GPIO_setQualificationMode(0, GPIO_QUAL_SYNC);//同步采样

    GPIO_setPadConfig(1, GPIO_PIN_TYPE_PULLUP);//上拉输入
    GPIO_setDirectionMode(1,GPIO_DIR_MODE_IN);// input
    // XINT2 Qual using 6 samples
    GPIO_setQualificationMode(1, GPIO_QUAL_6SAMPLE);//6个采样周期采样
    // Set qualification period for GPIO0 to GPIO7
    // 每个采样窗口列表 510*SYSCLKOUT
    GPIO_setQualificationPeriod(3,510);//八个一组  我也不是很清楚

    //配置外设中断
     //
     // GPIO0 是 XINT1, GPIO1 是 XINT2 IO口映射到中断线
     //
     GPIO_setInterruptPin(0,GPIO_INT_XINT1);//外设中断
     GPIO_setInterruptPin(1,GPIO_INT_XINT2);//外设中断
     //
     // 设置中断的方式
     //
     // 上升沿中断
     GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
     // 上升沿中断
     GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_FALLING_EDGE);
     //
     // 使能 XINT1 and XINT2 中断线
     //
     GPIO_enableInterrupt(GPIO_INT_XINT1);         // Enable XINT1
     GPIO_enableInterrupt(GPIO_INT_XINT2);         // Enable XINT2

}

//
// xint1_isr - External Interrupt 1 ISR  中断服务函数
//
interrupt void xint1_isr(void)
{
    LED1_TOGGLE;
    //
    // Acknowledge this interrupt to get more from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

}

//
// xint2_isr - External Interrupt 2 ISR  中断服务函数
//
interrupt void xint2_isr(void)
{
    LED2_TOGGLE;
    //
    // Acknowledge this interrupt to get more from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


