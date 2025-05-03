#ifndef USER_USART_H_
#define USER_USART_H_

//*****************************************************************************
//
// 如果使用c++编译器构建，则使此头文件中的所有定义都具有C绑定。
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// 包含文件
//

#include "driverlib.h"
#include "device.h"
#include "string.h"
#include "led.h"
#include "micro_printf.h"
//*****************************************************************************
//
// PinMux 复用配置
//
//*****************************************************************************

//
// SCIA -> mySCI0 Pinmux
//
//
// SCIRXDA - GPIO 设置
//
#define GPIO_PIN_SCIRXDB        13
#define mySCI0_SCIRX_GPIO       13
#define mySCI0_SCIRX_PIN_CONFIG GPIO_13_SCIRXDB
//
// SCITXDA - GPIO 设置
//
#define GPIO_PIN_SCITXDB        40
#define mySCI0_SCITX_GPIO       40
#define mySCI0_SCITX_PIN_CONFIG GPIO_40_SCITXDB

//*****************************************************************************
//
// SCI 配置
//
//*****************************************************************************
#define mySCI0_BASE             SCIB_BASE
#define mySCI0_BAUDRATE         115200
#define mySCI0_CONFIG_WLEN      SCI_CONFIG_WLEN_8
#define mySCI0_CONFIG_STOP      SCI_CONFIG_STOP_ONE
#define mySCI0_CONFIG_PAR       SCI_CONFIG_PAR_NONE
#define mySCI0_FIFO_TX_LVL      SCI_FIFO_TX0
#define mySCI0_FIFO_RX_LVL      SCI_FIFO_RX0
void mySCI0_init();

//*****************************************************************************
//
// 串口配置
//
//*****************************************************************************
void        USART_Init(void);
uint8_t     USART_CanReadUntil(uint8_t endChar);
uint8_t     USART_CanReadStr(void);
uint8_t     USART_CanReadLine(void);
uint32_t    USART_ReadLine(uint8_t *str);

void        USART_WriteChar(uint8_t ch);
uint8_t     USART_Write(uint8_t *str, uint16_t len);
uint8_t     USART_WriteUntil(uint8_t *str, uint8_t endChar);
uint8_t     USART_WriteStr(uint8_t *str);
uint8_t     USART_WriteLine(uint8_t *str);

__interrupt void SCIB_RXFIFOISR(void);
//*****************************************************************************
//
// 标记c++编译器的C绑定部分的末尾。
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif



#endif /* 6_USER_SCI_H_ */
