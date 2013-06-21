#include "control.h"
#include "../driver/motor.h"
extern char baseThr;
#include <math.h>
extern int16_t abs (int16_t i);//defined in mpu6050.c
extern int16_t yaw,pitch, roll;
extern int16_t gyroX,gyroY,gyroZ;

extern float halfT;

float Ki,Kp,Kd;
int16_t iMax;

int16_t lastErrRoll, lastErrPitch, lastErrYaw;
int16_t intRoll, intPitch, intYaw;

void initControl(void)
{
  setPWM(0,0,0,0);
  
  Ki=0.25f;
  Kp=0.65f;
  Kd=0.04f;//0.032
  
  lastErrRoll=0;
  lastErrPitch=0;
  lastErrYaw=0;
  
  intRoll=0;
  intPitch=0;
  intYaw=0;
  
  iMax = 100;
}

void controlLoop(void)
{
  int16_t thr,Motor1,Motor2,Motor3,Motor4;
  int16_t rollOut,pitchOut,yawOut;
  
  if(baseThr!=0x00)
  {
    thr=(baseThr-1)*10;
    
    rollOut   =   pidCalc(roll,-28,&intRoll,&lastErrRoll,gyroY);
    pitchOut  =   pidCalc(pitch,0,&intPitch,&lastErrPitch,-gyroX);
    yawOut    =   -pidCalc(yaw,0,&intYaw,&lastErrYaw,gyroZ);
    
    Motor1 = thr + rollOut            ;//- yawOut/4;
    Motor2 = thr           + pitchOut ;//+ yawOut/4;
    Motor3 = thr - rollOut            ;//- yawOut/4;
    Motor4 = thr           - pitchOut ;//+ yawOut/4;

	  //Motor4=(int16_t)(thr + rollOut - pitchOut);// + yawOut);
	  //Motor1=(int16_t)(thr + rollOut + pitchOut);// - yawOut);
	  //Motor2=(int16_t)(thr - rollOut + pitchOut);// + yawOut);
	  //Motor3=(int16_t)(thr - rollOut - pitchOut);// - yawOut);
  
    setPWM(Motor1,Motor2,Motor3,Motor4);
  }
  else
  {
    setPWM(0,0,0,0);
  }
}

int16_t pidCalc(int16_t actual, int16_t setPt, 
                int16_t* integral,int16_t* lastErr,
                int16_t gyro)
{
  int16_t err,P,I,D,out;
  err = setPt - actual;
  err=err;
  P = err*Kp; // calc proportional term
  

	*integral += Ki * err;
	
	if(*integral>iMax) 	*integral = iMax;
	if(*integral<-iMax)	*integral = -iMax;
	I = *integral;// integral term
  I=0;
  //D = (*lastErr-err)*Kd; // derivative term
  D = gyro*Kd;
  out = P + I - D; // Total drive = P+I+D
  
  *lastErr = err;

  return out;
}
