#include "timer.h"

void Initial_Timer3(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM3, ENABLE); 
	/* TIM4 configuration*/ 
  /* Time Base configuration*/
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xffff;       
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
  TIM_PrescalerConfig(TIM4, 0, TIM_PSCReloadMode_Update);
  /* Disable the TIM4 Update event */
  TIM_UpdateDisableConfig(TIM4, ENABLE);
  /* ----------------------TIM4 Configuration as slave for the TIM3 ----------*/
  /* Select the TIM4 Input Trigger: TIM3 TRGO used as Input Trigger for TIM4*/
  TIM_SelectInputTrigger(TIM4, TIM_TS_ITR2);
  /* Use the External Clock as TIM4 Slave Mode */
  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_External1);
  /* Enable the TIM4 Master Slave Mode */
  TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);	
  TIM_TimeBaseStructure.TIM_Period = 0xffff;     
  TIM_TimeBaseStructure.TIM_Prescaler = 72;	 //1M
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ARRPreloadConfig(TIM3, ENABLE);	

  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	TIM_UpdateRequestConfig(TIM3, TIM_UpdateSource_Regular);
	/* ----------------------TIM3 Configuration as Master for the TIM4 -----------*/
  /* Use the TIM3 Update event  as TIM3 Trigger Output(TRGO) */
  TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
  /* Enable the TIM3 Master Slave Mode */
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);

	TIM_Cmd(TIM3, ENABLE); 
  TIM_Cmd(TIM4, ENABLE);                  
}

uint32_t micros(void)
{
 	uint32_t temp=0 ;
 	temp = TIM4->CNT;
 	temp = temp<<16;
 	temp += TIM3->CNT;
 	return temp;
}
