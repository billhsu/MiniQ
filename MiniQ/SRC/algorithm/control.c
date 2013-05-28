#include "control.h"
#include "../driver/motor.h"
extern char status;

extern int16_t abs (int16_t i);//defined in mpu6050.c

float Ki,Kp,Kd;

int16_t lastErrRoll, lastErrPitch, lastErrYaw;
int16_t intRoll, intPitch, intYaw;

void initControl(void)
{
  setPWM(0,0,0,0);
  
  Ki=0.0f;
  Kp=7.0f;
  Kd=3.0f;
  
  lastErrRoll=0;
  lastErrPitch=0;
  lastErrYaw=0;
  
  intRoll=0;
  intPitch=0;
  intYaw=0;
}

void controlLoop(void)
{
  int16_t thr,Motor1,Motor2,Motor3,Motor4;
  int16_t rollOut,pitchOut,yawOut;
  
  if(status!=0xff)
  {
    thr=status*100;
    
    rollOut   =   pidCalc(roll,0,gyroX,&lastErrRoll);
    pitchOut  =   pidCalc(pitch,0,gyroY,&lastErrPitch);
    yawOut    =   pidCalc(yaw,0,gyroZ,&lastErrYaw);
    
    
    Motor1 = thr + rollOut           ;// - yawOut;
    Motor2 = thr           + pitchOut;// + yawOut;
    Motor3 = thr - rollOut           ;// - yawOut;
    Motor4 = thr           - pitchOut;// + yawOut;

    setPWM(Motor1,Motor2,Motor3,Motor4);
  }
  else
  {
    setPWM(0,0,0,0);
  }
}

int16_t pidCalc(int16_t actual, int16_t setPt, 
                int16_t gyro, int16_t* lastErr)
{
  int16_t err,out;
  err = setPt - actual;
  out = err*Kp - gyro*Kd;
  return out;
}
