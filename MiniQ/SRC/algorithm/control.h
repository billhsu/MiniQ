#ifndef _MY_CONTROL_H
#define _MY_CONTROL_H
#include "../global.h"
#include "stm32f10x.h"

extern int16_t yaw,pitch, roll;
extern int16_t gyroX,gyroY,gyroZ;
void initControl(void);
void controlLoop(void);
int16_t pidCalc(int16_t actual, int16_t setPt, 
                int16_t gyro, int16_t* lastErr);

#endif
