#ifndef __IMU_H
#define __IMU_H
#include "stm32f10x.h"

void IMU_DataPrepare(void);
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az,float mx,float my,float mz) ;

void IMU_TEST(void);
void GET_EXPRAD(void);
#endif
