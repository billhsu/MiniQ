/*
MiniQ: https://github.com/billhsu/MiniQ
Bill Hsu 2013
*/
#ifndef _MY_MOTOR_H
#define _MY_MOTOR_H
#include "../global.h"
#include "stm32f10x.h"
#define PWM_MAX 999

void initMotor(void);
void setPWM(int16_t pwm1, int16_t pwm2, 
            int16_t pwm3, int16_t pwm4);

#endif
