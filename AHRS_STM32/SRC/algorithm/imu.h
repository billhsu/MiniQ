#ifndef __IMU_H
#define __IMU_H

#include <stdint.h>


//Mini IMU AHRS 解算的API
void IMU_init(void); //初始化
void IMU_getYawPitchRoll(int16_t * angles,int16_t *data); //更新姿态
uint32_t micros(void);	//读取系统上电后的时间  单位 us 

#endif
