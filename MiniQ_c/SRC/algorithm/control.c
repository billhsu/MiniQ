#include "control.h"
#include "../driver/motor.h"
extern char baseThr;

#include "extern_variable.h"


PID PID_RP;

void PID_INIT(void)
{
	PID_RP.P = 7;
	PID_RP.I = 0;
	PID_RP.D = 3;
	
	PID_RP.POUT = 0;
	PID_RP.IOUT = 0;
	PID_RP.DOUT = 0;
	
	PID_RP.IMAX = 300;
	PID_RP.LastError = 0;
	PID_RP.PrerError = 0;
}
void PID_CAL(void)
{
	static float thr=0,roll=0,pitch=0,yaw=0;
	static float roll_i=0,pitch_i=0;
	
	int16_t Motor1,Motor2,Motor3,Motor4;
	

////////////////////////////////////////////////////////////////////////////////PID计算
	roll 	= PID_RP.P * DIF_ANGLE.X;
	
	if(Q_ANGLE.Roll>-0.1 && Q_ANGLE.Roll<0.1)
	{                                                                            
		roll_i = 0;
	}
	roll_i -= PID_RP.I * Q_ANGLE.Roll;
	PID_RP.IMAX = DIF_ANGLE.X * 10;
	if(PID_RP.IMAX<0)	
	{
		PID_RP.IMAX = (-PID_RP.IMAX) + 100;
	}
	else
	{
		PID_RP.IMAX += 100;
	}
	if(roll_i>PID_RP.IMAX) 	roll_i = PID_RP.IMAX;
	if(roll_i<-PID_RP.IMAX)	roll_i = -PID_RP.IMAX;
	roll += roll_i;
	
	roll -= PID_RP.D * GYRO_F.X;
///////////	
	pitch 	= PID_RP.P * DIF_ANGLE.Y;
		
	if(Q_ANGLE.Pitch>-0.1 && Q_ANGLE.Pitch<0.1)
	{
		pitch_i = 0;
	}
	pitch_i -= PID_RP.I * Q_ANGLE.Pitch;
	if(PID_RP.IMAX<0)	
	{
		PID_RP.IMAX = (-PID_RP.IMAX) + 100;
	}
	else
	{
		PID_RP.IMAX += 100;
	}
	if(PID_RP.IMAX<0)	PID_RP.IMAX = -PID_RP.IMAX;
	if(pitch_i>PID_RP.IMAX) 	pitch_i = PID_RP.IMAX;
	if(pitch_i<-PID_RP.IMAX)	pitch_i = -PID_RP.IMAX;
	pitch += pitch_i;
	
	pitch -= PID_RP.D * GYRO_F.Y;
/////////////
	GYRO_I[0].Z += EXP_ANGLE.Z/3000;
	yaw = -10 * GYRO_I[0].Z;
	
	yaw -= 3 * GYRO_F.Z;
//	
	thr = (baseThr-1)*10;
////////////////////////////////////////////////////////////////////////////////将输出值融合到四个电机
	Motor1=(int16_t)(thr + roll - pitch + yaw);
	Motor2=(int16_t)(thr + roll + pitch - yaw);
	Motor3=(int16_t)(thr - roll + pitch + yaw);
	Motor4=(int16_t)(thr - roll - pitch - yaw);
	if(baseThr>0)
		setPWM(Motor4,Motor1,Motor2,Motor3);
	else
		setPWM(0,0,0,0);
}

