#include "stm32f10x_lib.h"
#include "driver/UARTs.h"
#include "driver/delay.h"
#include "driver/ioi2c.h"

#include "driver/mpu6050.h"
#include "driver/hmc5883l.h"
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void WWDG_Configuration(void);
void Delay(u32 nTime);
void Delayms(vu32 m);
 
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
  
  int16_t data[3] = {0,0,0};
  RCC_Configuration();
  delay_init(72);
  GPIO_Configuration();
  Initial_UART1(115200L);
  I2C_GPIO_Config();
  NVIC_Configuration();
  
  delay_ms(10);
  Init_MPU6050();
  
  delay_ms(10);
  HMC5883L_Init();
    
  while(1)
  {
    UART1_Put_Char(0xa5);
    UART1_Put_Char(0x5a);
    UART1_Put_Char(0x12);
    UART1_Put_Char(0xa1);
    
    Read_MPU6050_ACC(data);
    out_int16_t(&data[0]);
    out_int16_t(&data[1]);
    out_int16_t(&data[2]);
    
    Read_MPU6050_GYRO(data);
    out_int16_t(&data[0]);
    out_int16_t(&data[1]);
    out_int16_t(&data[2]);
    
    
    HMC5883L_Read(data);
    out_int16_t(&data[0]);
    out_int16_t(&data[1]);
    out_int16_t(&data[2]);
    
    UART1_Put_Char(0xed);
    
    delay_ms(5);
  }
		     
}

void RCC_Configuration(void)
{   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
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
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Init(&NVIC_InitStructure);


  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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


