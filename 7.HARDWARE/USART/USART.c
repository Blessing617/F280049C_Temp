#include    "USART.h"
#define     USART_MAX_LEN   200

uint8_t     USART_buffer    [USART_MAX_LEN];
uint32_t    USART_bufferPos = 0;

//*****************************************************************************
//
// PINMUX 配置
//
//*****************************************************************************
void PinMux_init(void)
{
    //
    // 分配给CPU1的模块的PinMux
    //
    //
    // SCIB -> mySCI0 Pinmux
    //
    GPIO_setMasterCore(mySCI0_SCIRX_GPIO, GPIO_CORE_CPU1);                          //配置控制核心为CPU1
    GPIO_setPinConfig(mySCI0_SCIRX_PIN_CONFIG);                                     //配置片内外设
    GPIO_setPadConfig(mySCI0_SCIRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(mySCI0_SCIRX_GPIO, GPIO_QUAL_ASYNC);                  //无采样滤波

    GPIO_setMasterCore(mySCI0_SCITX_GPIO, GPIO_CORE_CPU1);                          //配置控制核心为CPU1
    GPIO_setPinConfig(mySCI0_SCITX_PIN_CONFIG);                                     //配置片内外设
    GPIO_setPadConfig(mySCI0_SCITX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(mySCI0_SCITX_GPIO, GPIO_QUAL_ASYNC);                  //无采样滤波


}

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
void SCI_init(void)
{
    mySCI0_init();
}

void mySCI0_init(void)
{
    //配置SCI
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);//使能相应时钟，打开外设

    //一些初始化操作
    //清除所有SCI中断源
    SCI_clearInterruptStatus(mySCI0_BASE, SCI_INT_RXFF | SCI_INT_TXFF | SCI_INT_FE | SCI_INT_OE | SCI_INT_PE | SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
    //清除接收FIFO溢出标志状态
    SCI_clearOverflowStatus(mySCI0_BASE);
    SCI_resetTxFIFO(mySCI0_BASE);//复位TX FIFO
    SCI_resetRxFIFO(mySCI0_BASE);//复位RX FIFO
    SCI_resetChannels(mySCI0_BASE);//重置SCI发送和接收通道

    // 配置SCIB参数
    SCI_setConfig(mySCI0_BASE, DEVICE_LSPCLK_FREQ, mySCI0_BAUDRATE, (SCI_CONFIG_WLEN_8|SCI_CONFIG_STOP_ONE|SCI_CONFIG_PAR_NONE));
    //执行一个软件复位的SCI和清除所有报告的接收器状态标志。
    SCI_performSoftwareReset(mySCI0_BASE);// 初始化SCIA及其FIFO

    //配置FIFO
    SCI_setFIFOInterruptLevel(mySCI0_BASE, SCI_FIFO_TX2, SCI_FIFO_RX1);//配置FIFO
    SCI_enableFIFO(mySCI0_BASE);////使能SCIB_FIFO
    //使能 SCI
    SCI_enableModule(mySCI0_BASE);//使能发送和接收。

    //配置中断
    Interrupt_register(INT_SCIB_RX, SCIB_RXFIFOISR);        //注册SCIB_RX
    SCI_enableInterrupt(mySCI0_BASE, SCI_INT_RXFF);         //使能RX_FIFO中断
    SCI_disableInterrupt(mySCI0_BASE, SCI_INT_RXERR);       //失能RX_ERR中断
    Interrupt_enable(INT_SCIB_RX);                          //使能SCIB中断
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);          //清除GROUP9请求
}

//*****************************************************************************
//
// 串口初始化配置
//
//*****************************************************************************
void USART_Init(void)
{
    EALLOW;

    PinMux_init();//GPIO的配置
    SCI_init();

    EDIS;
}

//*****************************************************************************
//
// 串口读部分代码
//
//*****************************************************************************

//缓存区数据移位
void __USART_Shift(uint32_t len)
{
  uint32_t i;
  for (i = 0; i < USART_MAX_LEN - len; i++)
  {
    USART_buffer[i] = USART_buffer[i + len];
  }
  USART_bufferPos -= len;
}

//串口读到指定字符
uint8_t USART_CanReadUntil(uint8_t endChar)
{
  uint32_t i;
  for (i = 0; i < USART_bufferPos; i++)
  {
    if (USART_buffer[i] == endChar)
      return 1;
  }
  return 0;
}

//串口读到字符串
uint8_t USART_CanReadStr()
{
  return USART_CanReadUntil('\0');
}

//串口读到\r\n换行符
uint8_t USART_CanReadLine(void)
{
  uint32_t i;
  for (i = 1; i < USART_bufferPos; i++)
  {
    if (USART_buffer[i - 1] == '\r' && USART_buffer[i] == '\n')
      return 1;
  }
  return 0;
}

//串口读字符串
uint32_t USART_ReadLine(uint8_t *str)
{
  if (!USART_CanReadLine())
    return 0;
  uint32_t i;
  for (i = 0; i < USART_bufferPos; i++)
  {
    *(str + i) = USART_buffer[i];
    if (i > 0 && *(str + i - 1) == '\r' && *(str + i) == '\n')
    {
      i++;
      break;
    }
  }
  __USART_Shift(i);
  return i;
}

//*****************************************************************************
//
// 串口写部分代码
//
//*****************************************************************************
//串口写字符
void USART_WriteChar(uint8_t ch)
{
    SCI_writeCharBlockingFIFO(mySCI0_BASE,ch);
}

//串口写字符串（指定长度）
uint8_t USART_Write(uint8_t *str, uint16_t len)
{
  uint32_t i;
  if (len > USART_MAX_LEN)
    return 0;
  for (i = 0; i < len; i++)
  {
      USART_WriteChar(*(str + i));
  }
  return len;
}

//串口写字符串（指定结束字符）
uint8_t USART_WriteUntil(uint8_t *str, uint8_t endChar)
{
  uint32_t i;
  for (i = 0; i < USART_MAX_LEN; i++)
  {
      USART_WriteChar(*(str + i));
    if (*(str + i) == endChar)
      break;
  }
  return i < USART_MAX_LEN;
}

//串口写字符串（指定结束字符为\0）
uint8_t USART_WriteStr(uint8_t *str) // the \0 will BE sent;
{
  return USART_WriteUntil(str, '\0');
}

//串口写字符串（指定结束字符为\0）并输出换行符\r\n
uint8_t USART_WriteLine(uint8_t *str) // the \0 of the string will not be sent, and the transimitted data ends with \r\n(no \0 at the end)
{
  uint32_t i;
  for (i = 0; i < USART_MAX_LEN; i++)
  {
    if (*(str + i) == '\0')
      break;
    USART_WriteChar(*(str + i));
  }
  USART_WriteChar('\r');
  USART_WriteChar('\n');
  return i + 2 < USART_MAX_LEN;
}

//串口中断函数
__interrupt void SCIB_RXFIFOISR(void)
{
    char* str;
    uint8_t Rx_data [200];

    SCI_clearInterruptStatus(mySCI0_BASE, SCI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    while(SCI_getRxFIFOStatus(mySCI0_BASE)!=SCI_FIFO_RX0)
    {
        USART_buffer[USART_bufferPos++] = SCI_readCharNonBlocking(SCIB_BASE);
        if (USART_bufferPos == USART_MAX_LEN)
        {
            USART_bufferPos = 0;
        }
    }

    if(USART_ReadLine(Rx_data))
    {
        micro_print((char*)Rx_data);

        str = strstr((char*)Rx_data,"LED1");
        if(str !=  NULL)
        {
            LED1_TOGGLE;
        }
        str = strstr((char*)Rx_data,"LED2");
        if(str !=  NULL)
        {
            LED2_TOGGLE;
        }
        memset(Rx_data,0,sizeof(Rx_data));
    }
}



