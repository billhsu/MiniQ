#ifndef _MY_CONTROL_H
#define _MY_CONTROL_H
#include "../global.h"
#include "stm32f10x.h"

void PID_INIT(void);
void PID_CAL(void);
typedef struct PID{float P,POUT,I,IOUT,D,DOUT,IMAX,SetPoint,NowPoint,LastError,PrerError;}PID;
#endif
