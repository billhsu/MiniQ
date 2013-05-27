#include "control.h"
#include "../driver/motor.h"
extern char status;

extern int16_t abs (int16_t i);

float Ki,Kp,Kd;

int16_t lastRoll, lastPitch, lastYaw;
int16_t intRoll, intPitch, intYaw;

void initControl(void)
{
  setPWM(0,0,0,0);
  Ki=0.0f;
  Kp=7.0f;
  Kd=3.0f;
  lastRoll=0;
  lastPitch=0;
  lastYaw=0;
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
    thr=status*10;
    
    rollOut = pidCalc(roll,0,30,&intRoll,&lastRoll);
    pitchOut = pidCalc(pitch,0,30,&intPitch,&lastPitch);
    yawOut = pidCalc(yaw,0,30,&intYaw,&lastYaw);
    
    
    Motor1 = thr + rollOut            - yawOut;
    Motor2 = thr           + pitchOut + yawOut;
    Motor3 = thr - rollOut            - yawOut;
    Motor4 = thr           - pitchOut + yawOut;

    setPWM(Motor1,Motor2,Motor3,Motor4);
  }
  else 
  {
    setPWM(0,0,0,0);
  }
}

int16_t pidCalc(int16_t actual, int16_t setPt, 
                int16_t intThresh, int16_t* integral, 
                int16_t* last)
{
  int16_t err,P,I,D,out;
  err = setPt - actual;
  if (abs(err) < intThresh){ // prevent integral 'windup'
    *integral = *integral + err; // accumulate the error integral
  }
  else {
    integral=0; // zero it if out of bounds
  }
  P = err*Kp; // calc proportional term
  I = *integral*Ki; // integral term
  D = (*last-actual)*Kd; // derivative term
  out = P + I + D; // Total drive = P+I+D
  
  *last = actual;
  return out;
}
