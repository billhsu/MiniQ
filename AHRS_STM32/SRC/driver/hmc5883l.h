#ifndef _HMC5883L_H_
#define _HMC5883L_H_

#define HMC5883L_ADDRESS 0x3C
#define MAG_DATA_REGISTER 0x03
#define ConfigRegA           0x00
#define ConfigRegB           0x01
#define magGain              0xE0
#define PositiveBiasConfig   0x01
#define NegativeBiasConfig   0x02
#define NormalOperation      0x00
#define ModeRegister         0x02
#define ContinuousConversion 0x00
#define SingleConversion     0x01

// ConfigRegA valid sample averaging for 5883L
#define SampleAveraging_1    0x00
#define SampleAveraging_2    0x01
#define SampleAveraging_4    0x02
#define SampleAveraging_8    0x03

// ConfigRegA valid data output rates for 5883L
#define DataOutputRate_0_75HZ 0x00
#define DataOutputRate_1_5HZ  0x01
#define DataOutputRate_3HZ    0x02
#define DataOutputRate_7_5HZ  0x03
#define DataOutputRate_15HZ   0x04
#define DataOutputRate_30HZ   0x05
#define DataOutputRate_75HZ   0x06

uint8_t hmc5883l_detect(void);
uint8_t hmc5883l_cal(uint8_t calibration_gain);
uint8_t hmc5883l_finish_cal(void);
uint8_t hmc5883l_read(int16_t *x, int16_t *y, int16_t *z, int16_t *data);



#endif

