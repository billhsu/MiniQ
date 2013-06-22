#include "imu.h"
#include "../driver/timer.h"
#include "../extern_variable.h"
#include <math.h>

#define pi            __PI
#define angletorad    0.01745329252
#define radtoangle    57.295779513
#define Gyr_Gain 	0.015267                                  
#define ACC_Gain 	0.0011963                                
#define FILTER_NUM	10										//滑动窗口滤波窗口大小

uint8_t FLY_ENABLE=0;
uint8_t Imu_DataReady=0;	//IMU数据准备好标志
float IMU_CYCTIME_F;		//两次计算的时间间隔,单位为秒
S_FLOAT_XYZ ACC_F,GYRO_F;	
S_FLOAT_XYZ GYRO_I[3];		//陀螺仪积分
S_INT16_XYZ ACC_AVG,GYRO_AVG;		//滑动窗口滤波后的ACC平均值和处理后的gyro值
S_FLOAT_XYZ ACC_ANGLE;		
S_FLOAT_XYZ EXP_ANGLE;		
S_FLOAT_XYZ DIF_ANGLE;		
int16_t	ACC_X_BUF[FILTER_NUM],ACC_Y_BUF[FILTER_NUM],ACC_Z_BUF[FILTER_NUM];	
volatile uint32_t lastUpdate, now;
void IMU_DataPrepare(void)
{
	static uint8_t filter_cnt=0;
	int32_t temp1=0,temp2=0,temp3=0;
	uint8_t i;

	IMU_CYCTIME_F = (float)micros() / 1000000;
	ACC_F.X = MPU6050_ACC_LAST.X * ACC_Gain;//本次传感器数据转换成单位格式
	ACC_F.Y = MPU6050_ACC_LAST.Y * ACC_Gain;
	ACC_F.Z = MPU6050_ACC_LAST.Z * ACC_Gain;
	GYRO_F.X = MPU6050_GYRO_LAST.X * Gyr_Gain;//为了和acc一直,将gyro读数的x,y交换
	GYRO_F.Y = MPU6050_GYRO_LAST.Y * Gyr_Gain;
	GYRO_F.Z = MPU6050_GYRO_LAST.Z * Gyr_Gain;

	ACC_X_BUF[filter_cnt] = MPU6050_ACC_LAST.X;//更新滑动窗口数组
	ACC_Y_BUF[filter_cnt] = MPU6050_ACC_LAST.Y;
	ACC_Z_BUF[filter_cnt] = MPU6050_ACC_LAST.Z;
	for(i=0;i<FILTER_NUM;i++)
	{
		temp1 += ACC_X_BUF[i];
		temp2 += ACC_Y_BUF[i];
		temp3 += ACC_Z_BUF[i];
	}
	ACC_AVG.X = temp1 / FILTER_NUM;
	ACC_AVG.Y = temp2 / FILTER_NUM;
	ACC_AVG.Z = temp3 / FILTER_NUM;
	filter_cnt++;
	if(filter_cnt==FILTER_NUM)	filter_cnt=0;

	GYRO_I[2].X = GYRO_I[1].X;				
	GYRO_I[2].Y = GYRO_I[1].Y;
	GYRO_I[2].Z = GYRO_I[1].Z;
	GYRO_I[1].X = GYRO_I[0].X;
	GYRO_I[1].Y = GYRO_I[0].Y;
	GYRO_I[1].Z = GYRO_I[0].Z;
	GYRO_I[0].X += GYRO_F.X * IMU_CYCTIME_F;
	GYRO_I[0].Y += GYRO_F.Y * IMU_CYCTIME_F;
	GYRO_I[0].Z += GYRO_F.Z * IMU_CYCTIME_F;

	Imu_DataReady = 1;
}

void IMU_TEST(void)
{
	if(Imu_DataReady)
	{
		Imu_DataReady = 0;
		IMUupdate(GYRO_F.X*0.0174,GYRO_F.Y*0.0174,GYRO_F.Z*0.0174,(float)ACC_AVG.X,(float)ACC_AVG.Y,(float)ACC_AVG.Z);	//*0.0174转成弧度
//	ACC_ANGLE.X = atan2(ACC_AVG.X,ACC_AVG.Z)*radtoangle;
//	ACC_ANGLE.Y = atan2(ACC_AVG.Y,ACC_AVG.Z)*radtoangle;
//	GYRO_I[0].X = GYRO_I[0].X * 0.98 + ACC_ANGLE.X * 0.02;
//	GYRO_I[0].Y = GYRO_I[0].Y * 0.98 + ACC_ANGLE.Y * 0.02;
	}
}
////////////////////////////////////////////////////////////////////////////////
void GET_EXPRAD(void)			//计算期望角度,不加控制时期望角度为0,0
{
	EXP_ANGLE.X = (float)(0.0f);
	EXP_ANGLE.Y = (float)(0.0f);
	EXP_ANGLE.Z = (float)(0.0f);
	DIF_ANGLE.X = EXP_ANGLE.X - Q_ANGLE.Roll;
	DIF_ANGLE.Y = EXP_ANGLE.Y - Q_ANGLE.Pitch;
  DIF_ANGLE.Z = EXP_ANGLE.Z - Q_ANGLE.Yaw;
//	DIF_ANGLE.Z = EXP_ANGLE.Z - GYRO_I[0].Z;
//	DIF_ANGLE.X = EXP_ANGLE.X - GYRO_I[0].X;
//	DIF_ANGLE.Y = EXP_ANGLE.Y - GYRO_I[0].Y;
//	DIF_ANGLE.Z = EXP_ANGLE.Z - GYRO_I[0].Z;
}
////////////////////////////////////////////////////////////////////////////////
#define Kp 10.0f
#define Ki 0.008f
float halfT;

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;   
float exInt = 0, eyInt = 0, ezInt = 0;  
S_FLOAT_ANGLE Q_ANGLE;
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
  float norm;

  float vx, vy, vz;// wx, wy, wz;
  float ex, ey, ez;

  float q0q0 = q0*q0;
  float q0q1 = q0*q1;
  float q0q2 = q0*q2;
  float q0q3 = q0*q3;
  float q1q1 = q1*q1;
  float q1q2 = q1*q2;
  float q1q3 = q1*q3;
  float q2q2 = q2*q2;
  float q2q3 = q2*q3;
  float q3q3 = q3*q3;
  
  norm = sqrt(ax*ax + ay*ay + az*az);
  if(norm<0.0001f && norm>-0.0001f) 
    return;
  now = micros();
  if(now<lastUpdate){
    halfT =  ((float)(now + (0xffff- lastUpdate)) / 2000000.0f);
  }
  else	{
    halfT =  ((float)(now - lastUpdate) / 2000000.0f);
  }
  lastUpdate = now;
  
  ax = ax /norm;
  ay = ay / norm;
  az = az / norm;
           
  vx = 2*(q1q3 - q0q2);												
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;

  ex = (ay*vz - az*vy) ;                           					
  ey = (az*vx - ax*vz) ;
  ez = (ax*vy - ay*vx) ;

  exInt = exInt + ex * Ki;								 
  eyInt = eyInt + ey * Ki;
  ezInt = ezInt + ez * Ki;

  gx = gx + Kp*ex + exInt;					   							
  gy = gy + Kp*ey + eyInt;
  gz = gz + Kp*ez + ezInt;				   							
					   
  q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;
  Q_ANGLE.Yaw = atan2(2 * q1 * q2 - 2 * q0 * q3, 2 * q0 * q0 + 2 * q1 * q1 - 1) * 57.3;// yaw
  Q_ANGLE.Pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
  Q_ANGLE.Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll

}
