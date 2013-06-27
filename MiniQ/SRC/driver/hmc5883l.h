#ifndef _HMC5883L_H_
#define _HMC5883L_H_

#include <stdint.h>

#define HMC5883L_Addr   0x3C
 
#define HMC5883L_REGA   0x00
#define HMC5883L_REGB   0x01
#define HMC5883L_MODE   0x02
#define HMC5883L_HX_H   0x03
#define HMC5883L_HX_L   0x04 
#define HMC5883L_HZ_H   0x05
#define HMC5883L_HZ_L   0x06
#define HMC5883L_HY_H   0x07
#define HMC5883L_HY_L   0x08
#define HMC5883L_STATE  0x09
#define HMC5883L_IRA    0x0a    //读序列号使用的寄存器
#define HMC5883L_IRB    0x0b
#define HMC5883L_IRC    0x0c 

/*---------------------* 
*   HMC5883 校正参数   * 
*----------------------*/
// 漂移系数。单位：1单位地磁场强度
#define HMC5883L_OFFSET_X   (9)
#define HMC5883L_OFFSET_Y   (149)

//比例因子
#define HMC5883L_GAIN_X     1f
//#define HMC5883L_GAIN_Y   1.04034582
#define HMC5883L_GAIN_Y     10403     //实际1.04034582,这里便于整除 

void HMC5883L_Init(void);
void HMC5883L_Calibrate(void);
void HMC5883L_Read(void);


#endif

