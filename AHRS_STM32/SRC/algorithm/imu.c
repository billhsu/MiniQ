#include "imu.h"

#include "./driver/mpu6050.h"
#include "./driver/hmc5883L.h"
#include "./driver/UARTs.h"
#include "./driver/delay.h"
#include "./driver/timer.h"

volatile float exInt, eyInt, ezInt;
volatile float q0, q1, q2, q3;
volatile uint32_t lastUpdate, now;
extern int16_t _hlt;
#include <math.h>
#define M_PI  3.1416f


float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void IMU_init(void)
{	 
  // initialize quaternion
  q0 = 1.0f;
  q1 = 0.0f;
  q2 = 0.0f;
  q3 = 0.0f;
  exInt = 0.0f;
  eyInt = 0.0f;
  ezInt = 0.0f;
  lastUpdate = micros();
  now = micros();
}


#define Kp 2.0f   // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.005f   // integral gain governs rate of convergence of gyroscope biases

void IMU_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {
  float norm;
  float hx, hy, hz, bx, bz;
  float vx, vy, vz, wx, wy, wz;
  float ex, ey, ez;
  float iq0, iq1, iq2, iq3;
  float halfT;

  // auxiliary variables to reduce number of repeated operations
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
  
  

  now = micros();
  halfT =  ((float)(now - lastUpdate) / 2000000.0f);
  lastUpdate = now;
  halfT = 0.025;
  norm = sqrt(ax*ax + ay*ay + az*az);       
  ax = ax / norm;
  ay = ay / norm;
  az = az / norm;
  
  norm = sqrt(mx*mx + my*my + mz*mz);          
  mx = mx / norm;
  my = my / norm;
  mz = mz / norm;
  
  // compute reference direction of flux
  hx = 2*mx*(0.5 - q2q2 - q3q3) + 2*my*(q1q2 - q0q3) + 2*mz*(q1q3 + q0q2);
  hy = 2*mx*(q1q2 + q0q3) + 2*my*(0.5 - q1q1 - q3q3) + 2*mz*(q2q3 - q0q1);
  hz = 2*mx*(q1q3 - q0q2) + 2*my*(q2q3 + q0q1) + 2*mz*(0.5 - q1q1 - q2q2);         
  bx = sqrt((hx*hx) + (hy*hy));
  bz = hz;     
  
  // estimated direction of gravity and flux (v and w)
  vx = 2*(q1q3 - q0q2);
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3;
  wx = 2*bx*(0.5 - q2q2 - q3q3) + 2*bz*(q1q3 - q0q2);
  wy = 2*bx*(q1q2 - q0q3) + 2*bz*(q0q1 + q2q3);
  wz = 2*bx*(q0q2 + q1q3) + 2*bz*(0.5 - q1q1 - q2q2);  
  
  // error is sum of cross product between reference direction of fields and direction measured by sensors
  ex = (ay*vz - az*vy) + (my*wz - mz*wy);
  ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
  ez = (ax*vy - ay*vx) + (mx*wy - my*wx);
  
  // integral error scaled integral gain
  exInt = exInt + ex*Ki;
  eyInt = eyInt + ey*Ki;
  ezInt = ezInt + ez*Ki;
  
  // adjusted gyroscope measurements
  gx = gx + Kp*ex + exInt;
  gy = gy + Kp*ey + eyInt;
  gz = gz + Kp*ez + ezInt;
  
  // integrate quaternion rate and normalise
  iq0 = (-q1*gx - q2*gy - q3*gz)*halfT;
  iq1 = (q0*gx + q2*gz - q3*gy)*halfT;
  iq2 = (q0*gy - q1*gz + q3*gx)*halfT;
  iq3 = (q0*gz + q1*gy - q2*gx)*halfT;  
  
  q0 += iq0;
  q1 += iq1;
  q2 += iq2;
  q3 += iq3;
  
  // normalise quaternion
  
  norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;
  
}


void IMU_getQ(float * q,float* mygetqval) {
  IMU_AHRSupdate(mygetqval[3] * M_PI/180.0f, mygetqval[4] * M_PI/180.0f, mygetqval[5] * M_PI/180.0f,
   mygetqval[0], mygetqval[1], mygetqval[2], mygetqval[6], mygetqval[7], mygetqval[8]);

  q[0] = q0;
  q[1] = q1;
  q[2] = q2;
  q[3] = q3;
}


void IMU_getYawPitchRoll(int16_t * angles,int16_t *data) {
  float q[4];
  float f_data[9];
  int i;
  volatile float gx=0.0, gy=0.0, gz=0.0;
  for(i=0;i<9;++i)
  {
    if(data[i]<0)
    {
      data[i]+=32768;
      data[i]=-data[i];
      
    }
    f_data[i]=(float)data[i];
  }
  
  IMU_getQ(q,f_data);
  
  angles[0] = (int16_t)(atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1) * 1800.0f/M_PI); // psi
  angles[1] = (int16_t)(-asin(2 * q[1] * q[3] + 2 * q[0] * q[2]) * 1800.0f/M_PI); // theta
  angles[2] = (int16_t)(atan2(2 * q[2] * q[3] - 2 * q[0] * q[1], 2 * q[0] * q[0] + 2 * q[3] * q[3] - 1) * 1800.0f/M_PI); // phi


  /*gx = 2 * (q[1]*q[3] - q[0]*q[2]);
  gy = 2 * (q[0]*q[1] + q[2]*q[3]);
  gz = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];
  
  angles[0] = (int16_t)(atan2(2 * q[1] * q[2] - 2 * q[0] * q[3], 2 * q[0]*q[0] + 2 * q[1] * q[1] - 1) * 900/M_PI);
  angles[1] = (int16_t)(atan(gx / sqrt(gy*gy + gz*gz))  * 900/M_PI);
  angles[2] = (int16_t)(atan(gy / sqrt(gx*gx + gz*gz))  * 900/M_PI);*/

}

