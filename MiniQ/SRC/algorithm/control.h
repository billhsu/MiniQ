#ifndef _MY_CONTROL_H
#define _MY_CONTROL_H
#include "../global.h"
#include "stm32f10x.h"

extern int16_t yaw,pitch, roll;

void initControl(void);
void controlLoop(void);

#endif
