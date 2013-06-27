#include "hmc5883l.h"
#include "ioi2c.h"
#include "delay.h"
#include "../Extern_Variable.h"
#include <stdint.h>

S_INT16_XYZ 	HMC5883L_LAST;		

void  HMC5883L_Init(void)
{
   Single_Write(HMC5883L_Addr,HMC5883L_REGA,0x14);   //30Hz
   Single_Write(HMC5883L_Addr,HMC5883L_MODE,0x00);   //连续测量模式
   HMC5883L_LAST.X=100;
   HMC5883L_LAST.Y=0;
   HMC5883L_LAST.Z=0;
}

void HMC5883L_Calibrate(void)
{
   Single_Write(HMC5883L_Addr,HMC5883L_REGA,0x15);   //30Hz,启动自检模式
   Single_Write(HMC5883L_Addr,HMC5883L_MODE,0x01);   //单一测量模式
   delay_ms(10);
   Single_Write(HMC5883L_Addr,HMC5883L_REGA,0x14);
   Single_Write(HMC5883L_Addr,HMC5883L_MODE,0x00);   //回到工作模式
}

void HMC5883L_Read()
{
    uint8_t tmp[6];
    int32_t s32Val;
    
    Single_Write(HMC5883L_Addr,HMC5883L_REGA,0x14);   //30Hz
    Single_Write(HMC5883L_Addr,HMC5883L_MODE,0x00);   //连续测量模式
    //delay_ms(10);
    
    tmp[0]=Single_Read(HMC5883L_Addr,HMC5883L_HX_H);//OUT_X_L_A
    tmp[1]=Single_Read(HMC5883L_Addr,HMC5883L_HX_L);//OUT_X_H_A
    
    tmp[2]=Single_Read(HMC5883L_Addr,HMC5883L_HZ_H);//OUT_Z_L_A
    tmp[3]=Single_Read(HMC5883L_Addr,HMC5883L_HZ_L);//OUT_Z_H_A
    
    tmp[4]=Single_Read(HMC5883L_Addr,HMC5883L_HY_H);//OUT_Y_L_A
    tmp[5]=Single_Read(HMC5883L_Addr,HMC5883L_HY_L);//OUT_Y_H_A

    HMC5883L_LAST.X  = (int16_t)((tmp[0] << 8) | tmp[1])+HMC5883L_OFFSET_X;
    s32Val = (int16_t)((tmp[4] << 8) | tmp[5])+HMC5883L_OFFSET_Y;    
    s32Val = (s32Val*HMC5883L_GAIN_Y)/10000;
    HMC5883L_LAST.Y    = (int16_t)s32Val;
    HMC5883L_LAST.Z    = (int16_t)((tmp[2] << 8) | tmp[3]);
}
