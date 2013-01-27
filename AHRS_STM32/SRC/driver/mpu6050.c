#include "mpu6050.h"
#include "ioi2c.h"


void Init_MPU6050(void)
{
  Single_Write(MPU6050_Addr,PWR_MGMT_1, 0x00);	//½â³ýÐÝÃß×´Ì¬
	Single_Write(MPU6050_Addr,SMPLRT_DIV, 0x07);
	Single_Write(MPU6050_Addr,CONFIG, 0x06);
	Single_Write(MPU6050_Addr,GYRO_CONFIG, 0x18);
	Single_Write(MPU6050_Addr,ACCEL_CONFIG, 0x01);
}

void Read_MPU6050_ACC(int16_t *data)
{
  uint8_t read[6];
  //Read Accel
  read[0]=Single_Read(MPU6050_Addr,ACCEL_XOUT_L); 
  read[1]=Single_Read(MPU6050_Addr,ACCEL_XOUT_H);
  data[0]=	(read[1]<<8)|read[0];
  //data[0]/=16.4; 						   //Read x accel

  read[2]=Single_Read(MPU6050_Addr,ACCEL_YOUT_L);
  read[3]=Single_Read(MPU6050_Addr,ACCEL_YOUT_H);
  data[1]=	(read[3]<<8)|read[2];
  //data[1]/=16.4; 						   //Read y accel
   
  read[4]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_L);
  read[5]=Single_Read(MPU6050_Addr,ACCEL_ZOUT_H);
  data[2]=	(read[5]<<8)|read[4];
  //data[2]/=16.4; 					       //Read z accel
}

void Read_MPU6050_GYRO(int16_t *data)
{
  uint8_t read[6];
  //Read Gyro
  read[0]=Single_Read(MPU6050_Addr,GYRO_XOUT_L); 
  read[1]=Single_Read(MPU6050_Addr,GYRO_XOUT_H);
  data[0]=	(read[1]<<8)|read[0];
  data[0]/=32.8; 						   //Read x Gyro

  read[2]=Single_Read(MPU6050_Addr,GYRO_YOUT_L);
  read[3]=Single_Read(MPU6050_Addr,GYRO_YOUT_H);
  data[1]=	(read[3]<<8)|read[2];
  data[1]/=32.8; 						   //Read y Gyro
   
  read[4]=Single_Read(MPU6050_Addr,GYRO_ZOUT_L);
  read[5]=Single_Read(MPU6050_Addr,GYRO_ZOUT_H);
  data[2]=	(read[5]<<8)|read[4];
  data[2]/=32.8; 					       //Read z Gyro
}
