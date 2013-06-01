#include "control.h"
#include "../driver/motor.h"
extern char status;

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
  
  Ki=0.00f;
  Kp=0.41f;
  Kd=0.032f;//0.032
  
  lastErrRoll=0;
  lastErrPitch=0;
  lastErrYaw=0;
  
  intRoll=0;
  intPitch=0;
  intYaw=0;
  
  iMax = 0;
}

void controlLoop(void)
{
  int16_t thr,Motor1,Motor2,Motor3,Motor4;
  int16_t rollOut,pitchOut,yawOut;
  
  if(status!=0xff)
  {
    thr=status*100;
    
    rollOut   =   pidCalc(roll,0,&intRoll,&lastErrRoll,gyroY);
    pitchOut  =   pidCalc(pitch,0,&intPitch,&lastErrPitch,-gyroX);
    yawOut    =   pidCalc(yaw,0,&intYaw,&lastErrYaw,gyroZ);
    
    
    Motor1 = thr + rollOut            ;//- yawOut;
    Motor2 = thr           + pitchOut ;//+ yawOut;
    Motor3 = thr - rollOut            ;//- yawOut;
    Motor4 = thr           - pitchOut ;//+ yawOut;

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
  
  if(actual>-1 && actual<1)
	{
		*integral = 0;
	}
	*integral += Ki * err;
	iMax = err;
	if(iMax<0)	
	{
		iMax = (-iMax) + 100;
	}
	else
	{
		iMax += 100;
	}
	if(*integral>iMax) 	*integral = iMax;
	if(*integral<-iMax)	*integral = -iMax;
	I = *integral;// integral term
  
  //D = (*lastErr-err)*Kd; // derivative term
  D = gyro*Kd;
  out = P + I - D; // Total drive = P+I+D
  
  *lastErr = err;

  return out;
}
