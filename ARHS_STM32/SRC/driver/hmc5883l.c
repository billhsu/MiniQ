#include <stdint.h>
#include "hmc5883l.h"
#include "i2c.h"

uint8_t hmc5883l_init_ready=0;

uint8_t hmc5883l_detect(void)
{
	uint8_t write, read[3];
	write=0x0A;
	if(i2c_transmit(HMC5883L_ADDRESS, &write, 1, read, 3)){
		if((read[0]=='H') &&
			(read[1]=='4') &&
			(read[2]=='3')){
			hmc5883l_init_ready=1;
			return 1;
		}
	}
	return 0;
}

uint8_t hmc5883l_cal(uint8_t calibration_gain)
{
	uint8_t write[4];
	if(!hmc5883l_init_ready)
		return 0;
	write[0]=ConfigRegA;
	write[1]=(SampleAveraging_8 << 5) | (DataOutputRate_1_5HZ << 2) | PositiveBiasConfig;
	write[2]=calibration_gain;
	write[3]=SingleConversion;
	if(i2c_transmit(HMC5883L_ADDRESS, write, 4, NULL, 0))
		return 1;
	return 0;
}

uint8_t hmc5883l_finish_cal(void)
{
    // leave test mode
	uint8_t write[4];
	if(!hmc5883l_init_ready)
		return 0;
	write[0]=ConfigRegA;
	write[1]=(SampleAveraging_8 << 5) | (DataOutputRate_1_5HZ << 2) | NormalOperation;
	write[2]=magGain;
	write[3]=ContinuousConversion;
	if(i2c_transmit(HMC5883L_ADDRESS, write, 4, NULL, 0))
		return 1;
	return 0;
}

uint8_t hmc5883l_read(int16_t *x, int16_t *y, int16_t *z, int16_t *data)
{
	uint8_t write, read[6];
	if(!hmc5883l_init_ready)
		return 0;
	write=MAG_DATA_REGISTER;
	if(i2c_transmit(HMC5883L_ADDRESS, &write, 1, read, 6)){
		if(data){
			*data=(read[0]<<8)|read[1];
			*(data+1)=(read[2]<<8)|read[3];
			*(data+2)=(read[4]<<8)|read[5];
		}
		if(x){
			*x=(read[0]<<8)|read[1];
			if(y)
				*y=(read[2]<<8)|read[3];
			if(z)
				*z=(read[4]<<8)|read[5];
		}
		if(data || x)
			return 1;
	}
	return 0;
}

