#include "timer.h"

void Initial_TimerTick(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE); 
	/* TIM3 configuration*/ 
  /* Time Base configuration 基本配置 配置定时器的时基单元*/
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xffff; //自动重装值         
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
  
  TIM_PrescalerConfig(TIM3, 0, TIM_PSCReloadMode_Update);
  /* Disable the TIM3 Update event */
  TIM_UpdateDisableConfig(TIM3, ENABLE);
  /* ----------------------TIM3 Configuration as slave for the TIM4 ----------*/
  /* Select the TIM3 Input Trigger: TIM4 TRGO used as Input Trigger for TIM3*/
  TIM_SelectInputTrigger(TIM3, TIM_TS_ITR3);
  /* Use the External Clock as TIM3 Slave Mode */
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_External1);
  /* Enable the TIM3 Master Slave Mode */
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);	
	/* 定时器配置:
	1.设置定时器最大计数值 50000
	2.设置时钟分频系数：TIM_CKD_DIV1
	3. 设置预分频：  1Mhz/50000= 1hz 
	4.定时器计数模式  向上计数模式
	*/		 
  	TIM_TimeBaseStructure.TIM_Period = 0xffff;     
  	TIM_TimeBaseStructure.TIM_Prescaler = 72;	 //1M 的时钟  
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//应用配置到TIM4 
  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// 使能TIM4重载寄存器ARR
  	TIM_ARRPreloadConfig(TIM4, ENABLE);	

	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
	TIM_UpdateRequestConfig(TIM4, TIM_UpdateSource_Regular);
	/* ----------------------TIM4 Configuration as Master for the TIM3 -----------*/
  	/* Use the TIM4 Update event  as TIM4 Trigger Output(TRGO) */
  	TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_Update);
  	/* Enable the TIM4 Master Slave Mode */
  	TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);

  	//启动定时器
	TIM_Cmd(TIM4, ENABLE); 
  	TIM_Cmd(TIM3, ENABLE);  
}

uint32_t micros(void)
{
 	uint32_t temp=0 ;
 	temp = TIM3->CNT; //读高16位时间
 	temp = temp<<16;
 	temp += TIM4->CNT; //读低16位时间
 	return temp;
}
