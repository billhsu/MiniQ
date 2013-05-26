#include "control.h"
#include "../driver/motor.h"
extern char status;
void initControl(void)
{
  setPWM(0,0,0,0);
}

void controlLoop(void)
{
  int16_t thr,Motor1,Motor2,Motor3,Motor4;
  
  if(status==0xaa)
  {
    thr=600;
    Motor1=(thr + roll - pitch + yaw);
	  Motor2=(thr + roll + pitch - yaw);
	  Motor3=(thr - roll + pitch + yaw);
	  Motor4=(thr - roll - pitch - yaw);
    setPWM(Motor4,Motor1,Motor2,Motor3);
  }
  else 
  {
    setPWM(0,0,0,0);
  }
}
