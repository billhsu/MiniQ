#ifndef _MY_CONTROL_H
#define _MY_CONTROL_H
#include "../global.h"
#include "stm32f10x.h"

void initControl(void);
void controlLoop(void);
int16_t pidCalc(int16_t actual, int16_t setPt, 
               int16_t intThresh, int16_t* integral, 
               int16_t* lastErr, int16_t gyro);

#endif
