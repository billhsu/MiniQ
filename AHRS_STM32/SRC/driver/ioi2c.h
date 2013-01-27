#ifndef IOI2C_H_
#define IOI2C_H_

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f10x_lib.h"
#include <stdbool.h>

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7


void I2C_GPIO_Config(void);
void I2C_delay(void);
void delay5ms(void);
bool I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
bool I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
unsigned char I2C_ReadByte(void);
bool Single_Write(unsigned char SlaveAddress,
                  unsigned char REG_Address,
                  unsigned char REG_data);
unsigned char Single_Read(unsigned char SlaveAddress,
                  unsigned char REG_Address);


#ifdef __cplusplus
 }
#endif 

#endif



