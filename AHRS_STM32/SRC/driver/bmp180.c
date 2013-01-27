#include <stdint.h>
#include "bmp180.h"
#include "i2c.h"

bmp180_cal_data_t bmp180_cal_data;
uint8_t bmp180_init_ready=0;

void bmp180_delay_ms(uint16_t ms)
{
	os_dly_wait(ms);
}

uint8_t bmp180_get_cal_data(void)
{
	uint8_t cal_data[22];
	uint8_t reg_write, i;
	uint16_t *d, tmp;
	uint8_t *s;
	reg_write=0xAA;
	if(i2c_transmit(BMP180_ADDRESS, &reg_write, 1, cal_data, 22)){
		d=(uint16_t *)(&bmp180_cal_data);
		s=cal_data;
		for(i=0; i<sizeof(bmp180_cal_data_t)/2; i++){
			tmp=*s;
			tmp=(tmp<<8)|*(s+1);
			*d=tmp;
			d++;
			s+=2;
		}
		bmp180_init_ready=1;
		return 1;
	}
	return 0;
}

uint8_t bmp180_reset(void)
{
	uint8_t write[2];
	if(!bmp180_init_ready)
		return 0;
	write[0]=0xE0;
	write[1]=0xB6;
	if(i2c_transmit(BMP180_ADDRESS, write, 2, NULL, 0))
		return 1;
	return 0;
}

uint8_t bmp180_detect(void)
{
	uint8_t write, read;
	write=0xD0;
	if(i2c_transmit(BMP180_ADDRESS, &write, 1, &read, 1)){
		if(read==0x55)
			return 1;
	}
	return 0;
}

void bmp180_init(void)
{
	if(bmp180_detect()){
		bmp180_reset();
		bmp180_get_cal_data();
	}
}

uint8_t bmp180_get_tem_and_pressure(long *temp, long *pressure, uint8_t oss)
{
	uint8_t write[2];
	uint8_t read[3];
	long ut, up;
	long x1, x2, b5, t, b6, x3, b3, b4, b7, p;
	if(!bmp180_init_ready)
		return 0;
	if(oss>3)
		return 0;
	//first request to convert ut
	write[0]=0xF4;
	write[1]=0x2E;
	if(i2c_transmit(BMP180_ADDRESS, write, 2, NULL, 0)==0)
		goto __error_exit;
	//and then wait for 50ms and then read 0xF6, 0xF7
	bmp180_delay_ms(50);
	write[0]=0xF6;
	if(i2c_transmit(BMP180_ADDRESS, write, 1, read, 2)==0)
		goto __error_exit;
	ut=read[0];
	ut=(ut<<8)|read[1];
	//second request to convert up
	write[0]=0xF4;
	write[1]=0x34+(oss<<6);
	if(i2c_transmit(BMP180_ADDRESS, write, 2, NULL, 0)==0)
		goto __error_exit;
	//and then wait for 50ms and then read 0xF6, 0xF7, 0xF8
	bmp180_delay_ms(50);
	write[0]=0xF6;
	if(i2c_transmit(BMP180_ADDRESS, write, 1, read, 3)==0)
		goto __error_exit;
	up=read[0];
	up=(up<<8)|read[1];
	up=(up<<8)|read[2];
	up>>=(8-oss);
	//and then calculate the temperature and pressure
	x1=(ut-bmp180_cal_data.ac6)*bmp180_cal_data.ac5;
	x1/=(1<<15);
	x2=bmp180_cal_data.mc*(1<<11);
	x2/=(x1+bmp180_cal_data.md);
	b5=x1+x2;
	if(temp){
		t=(b5+8);
		t/=(1<<4);
		*temp=t;
	}
	if(pressure){
		b6=b5-4000;
		x1=(bmp180_cal_data.b2*(b6*b6/(1<<12)));
		x1/=(1<<11);
		x2=bmp180_cal_data.ac2*b6;
		x2/=(1<<11);
		x3=x1+x2;
		b3=bmp180_cal_data.ac1*4+x3;
		b3=((b3<<oss)+2)/4;
		x1=bmp180_cal_data.ac3*b6;
		x1/=(1<<13);
		x2=(bmp180_cal_data.b1*(b6*b6/(1<<12)));
		x2/=(1<<16);
		x3=(x1+x2)+2;
		x3/=(1<<2);
		b4=bmp180_cal_data.ac4*(unsigned long)(x3+32768);
		b4/=(1<<15);
		b7=(unsigned long)up-b3;
		b7*=(50000>>oss);
		p=(b7/b4)*2;
		x1=p/(1<<8);
		x1=x1*x1;
		x1=(x1*3038)/(1<<16);
		x2=(-7357*p)/(1<<16);
		p=p+(x1+x2+3791)/(1<<4);
		*pressure=p;
		return 1;
	}
__error_exit:
	return 0;
}

