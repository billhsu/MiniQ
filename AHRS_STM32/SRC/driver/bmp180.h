#ifndef _BMP180_H_
#define _BMP180_H_

typedef struct _bmp180_cal_data_t_
{
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;
}bmp180_cal_data_t;

#define BMP180_ADDRESS 0xEE

void bmp180_init(void);
uint8_t bmp180_get_tem_and_pressure(long *temp, long *pressure, uint8_t oss);

#endif

