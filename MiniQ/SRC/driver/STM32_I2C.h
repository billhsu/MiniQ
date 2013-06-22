#ifndef __STM32_I2C_H
#define __STM32_I2C_H
#include <stdint.h>
#include "stm32f10x.h"
#include "../define.h"
#include "stm32f10x_i2c.h"
/*====================================================================================================*/
/*====================================================================================================*/
bool i2cWriteBuffer(uint8_t addr_, uint8_t reg_, uint8_t len_, uint8_t *data);
bool i2cWrite(uint8_t addr_, uint8_t reg_, uint8_t data);
bool i2cRead(uint8_t addr_, uint8_t reg_, uint8_t len, uint8_t* buf);
void i2cInit(void);
uint16_t i2cGetErrorCounter(void);
static void i2cUnstick(void);

/*====================================================================================================*/
/*====================================================================================================*/
#endif
