#ifndef _MYIIC_H
#define _MYIIC_H
#include "device.h"

#define IIC_SCL_PIN 16U
#define IIC_SDA_PIN 17U

#define IIC_SCL_0 GPIO_writePin(IIC_SCL_PIN,0)
#define IIC_SCL_1 GPIO_writePin(IIC_SCL_PIN,1)
#define IIC_SDA_0 GPIO_writePin(IIC_SDA_PIN,0)
#define IIC_SDA_1 GPIO_writePin(IIC_SDA_PIN,1)
#define READ_SDA  GPIO_readPin(IIC_SDA_PIN)

void SDA_IN(void);                                  //输入模式
void SDA_OUT(void);                                 //输入模式
void IIC_Init(void);                                //初始化IIC的IO口
void IIC_Start(void);				                //发送IIC开始信号
void IIC_Stop(void);	  			                //发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			        //IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);           //IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				        //IIC等待ACK信号
void IIC_Ack(void);					                //IIC发送ACK信号
void IIC_NAck(void);				                //IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
#endif

