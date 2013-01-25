#include <stdint.h>
#include "mpu6050.h"
#include "rtl.h"
#include "i2c.h"


uint8_t mpu6050_detect(void)
{
	uint8_t write;
	uint8_t read;
	write=0x75;
	if(i2c_transmit(MPU6050_ADDRESS, &write, 1, &read, 1)){
		if(read==0x68)
			return 1;
	}
	return 0;
}

uint8_t mpu6050_reset(void)
{
	uint8_t write[2];
	write[0]=0x6B;
	write[1]=0x80;
	if(i2c_transmit(MPU6050_ADDRESS, write, 2, NULL, 0))
		return 1;
	return 0;
}

uint8_t mpu6050_init(void)
{
	uint8_t write[4];
	uint8_t read;
	if(mpu6050_detect()){
		mpu6050_reset();
		//First Get the production ID
		write[0]=MPU_RA_PRODUCT_ID;
		if(i2c_transmit(MPU6050_ADDRESS, write, 1, &read, 1)==0)
			goto __error_exit; 
		
		//SMPLRT_DIV    -- SMPLRT_DIV = 0  Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
		write[0]=MPU_RA_SMPLRT_DIV;
		write[1]=0x00;
		if(i2c_transmit(MPU6050_ADDRESS, write, 2, NULL, 0)==0)
			goto __error_exit; 
		//PWR_MGMT_1    -- SLEEP 0; CYCLE 0; TEMP_DIS 0; CLKSEL 3 (PLL with Z Gyro reference)
		write[0]=MPU_RA_PWR_MGMT_1;
		write[1]=0x03;
		if(i2c_transmit(MPU6050_ADDRESS, write, 2, NULL, 0)==0)
			goto __error_exit; 
		// INT_PIN_CFG   -- INT_LEVEL_HIGH, INT_OPEN_DIS, LATCH_INT_DIS, INT_RD_CLEAR_DIS, FSYNC_INT_LEVEL_HIGH, FSYNC_INT_DIS, I2C_BYPASS_EN, CLOCK_DIS
		write[0]=MPU_RA_INT_PIN_CFG;
		write[1]=(0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (1 << 1) | (0 << 0);
		if(i2c_transmit(MPU6050_ADDRESS, write, 2, NULL, 0)==0)
			goto __error_exit; 
		//CONFIG        -- EXT_SYNC_SET 0 (disable input pin for data sync) ; default DLPF_CFG = 0 => ACC bandwidth = 260Hz  GYRO bandwidth = 256Hz)
		//GYRO_CONFIG   -- FS_SEL = 3: Full scale set to 2000 deg/sec
		write[0]=MPU_RA_CONFIG;
		write[1]=MPU6050_DLPF_CFG;
		write[2]=0x18;
	    // ACC Init stuff. Moved into gyro init because the reset above would screw up accel config. Oops.
	    // Product ID detection code from eosBandi (or rather, DIYClones). This doesn't cover product ID for MPU6050 as far as I can tell
	    if ((read == MPU6000ES_REV_C4) || (read == MPU6000ES_REV_C5) || (read == MPU6000_REV_C4) || (read == MPU6000_REV_C5)) {
	        // Accel scale 8g (4096 LSB/g)
	        // Rev C has different scaling than rev D
			write[3]=1 << 3;
	    } else {
			write[3]=2 << 3;
	    }
		if(i2c_transmit(MPU6050_ADDRESS, write, 4, NULL, 0)==0)
			goto __error_exit;      
		return 1;
	}
__error_exit:
	return 0;
}

uint8_t mpu6050_read_acc(int16_t *data)
{
	uint8_t write;
	uint8_t read[6];
	write=MPU_RA_ACCEL_XOUT_H;
	if(i2c_transmit(MPU6050_ADDRESS, &write, 1, read, 6)){
	    data[0] = (int16_t)((read[0] << 8) | read[1]) / 4;
	    data[1] = (int16_t)((read[2] << 8) | read[3]) / 4;
	    data[2] = (int16_t)((read[4] << 8) | read[5]) / 4;
		return 1;
	}
	return 0;
}

uint8_t mpu6050_read_gyro(int16_t *data)
{
	uint8_t write;
	uint8_t read[6];
	write=MPU_RA_GYRO_XOUT_H;
	if(i2c_transmit(MPU6050_ADDRESS, &write, 1, read, 6)){
	    data[0] = (int16_t)((read[0] << 8) | read[1]) / 4;
	    data[1] = (int16_t)((read[2] << 8) | read[3]) / 4;
	    data[2] = (int16_t)((read[4] << 8) | read[5]) / 4;
		return 1;
	}
	return 0;
}

