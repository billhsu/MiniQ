#ifndef __IMU_H
#define __IMU_H

#include <stdint.h>

void IMU_init(void);
void IMU_getYawPitchRoll(int16_t * angles,int16_t *data);

#endif
