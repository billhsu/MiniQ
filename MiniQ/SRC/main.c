#include <stdint.h>
#include "stm32f10x.h"
#include "driver/UARTs.h"
#include "driver/delay.h"
#include "driver/STM32_I2C.h"
#include "driver/mpu6050.h"
#include "driver/hmc5883l.h"
#include "driver/timer.h"
#include "driver/motor.h"
#include "algorithm/imu.h"
#include "algorithm/control.h"
#include "Extern_Variable.h"

GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

#define uploadSpeed  25   //25Hz
#define uploadTime (1000000/uploadSpeed)  //us

char volatile baseThr;
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void WWDG_Configuration(void);

uint32_t system_microsec;

int16_t _hlt;

void out_int16_t(int16_t * data)
{
  char ctemp;
  if(data[0]<0)data[0]=32768-data[0];
	ctemp=data[0]>>8;
	UART1_Put_Char(ctemp);
	ctemp=data[0];
	UART1_Put_Char(ctemp);
}


int main(void)
{
  int16_t cnt=0;
  int16_t led_cnt=0;
  int16_t result[3];
  uint8_t control_cnt=0;

  SystemInit();
  delay_init(72);
  GPIO_Configuration();
  Initial_UART1(115200L);
  //I2C_GPIO_Config();
  i2cInit();
  NVIC_Configuration();
  
  delay_ms(10);
  HMC5883L_Init();
  delay_ms(10);
  MPU6050_INIT();
  //MPU6050_INIT();
  delay_ms(10);
  HMC5883L_Init();
  delay_ms(10);
  
  //IMU_init();
  
  Initial_TimerTick();
  system_microsec=micros();
  initMotor();
  //initControl();
  baseThr = 0;
  cnt = 0;
  PID_INIT();
  EXP_ANGLE.X = (float)(-2.7f);
	EXP_ANGLE.Y = (float)(0.0f);
	EXP_ANGLE.Z = (float)(0.0f);
  while(1)
  {
    ++cnt;
    ++control_cnt;
    MPU6050_Dataanl();
    MPU6050_READ();
    //HMC5883L_Read();
    IMU_DataPrepare();
    if(control_cnt==2)
    {
      IMU_TEST();
      GET_EXPRAD();
      PID_CAL();
      control_cnt=0;
    }

    if(micros()-system_microsec>uploadTime)
    {
      
      UART1_Put_Char(0xff);
      UART1_Put_Char(0xaa);
      
      result[0]=(int16_t)(Q_ANGLE.Yaw*10.0f);
      result[1]=(int16_t)(Q_ANGLE.Pitch*10.0f);
      result[2]=(int16_t)(Q_ANGLE.Roll*10.0f);
      
      out_int16_t(&result[0]);
      out_int16_t(&result[1]);
      out_int16_t(&result[2]);
      cnt=uploadSpeed*cnt;
      out_int16_t(&cnt);
      cnt = 0;
      if(led_cnt<5)GPIOB->BSRR = GPIO_Pin_1;
      else 
      GPIOB->BRR  = GPIO_Pin_1;
      ++led_cnt;
      if(led_cnt>=50)led_cnt=0;
      
      system_microsec = micros();
    }

    

  }
		     
}




void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );
   /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  |
                                GPIO_Pin_1  |
								GPIO_Pin_2  |
								GPIO_Pin_3  |
								GPIO_Pin_4  |
								GPIO_Pin_5  |
								GPIO_Pin_6  |
								GPIO_Pin_7  |
								GPIO_Pin_8  |
								GPIO_Pin_9  |
								GPIO_Pin_10 |
								GPIO_Pin_11 |
								GPIO_Pin_12 ;			
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


}


void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure; 
          /* Enable the USART1 Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

}


void WWDG_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	
  WWDG_SetPrescaler(WWDG_Prescaler_8);	              //  WWDG clock counter = (PCLK1/4096)/8 = 244 Hz (~4 ms)  
  WWDG_SetWindowValue(0x41);		                 // Set Window value to 0x41
  WWDG_Enable(0x50);		       // Enable WWDG and set counter value to 0x7F, WWDG timeout = ~4 ms * 64 = 262 ms 
  WWDG_ClearFlag();			       // Clear EWI flag
  WWDG_EnableIT();			       // Enable EW interrupt
}


void WWDG_IRQHandler(void)
{
  /* Update WWDG counter */
  WWDG_SetCounter(0x50);
	
  /* Clear EWI flag */
  WWDG_ClearFlag();
  
}


