/* UARTs.C file

功能：实现	STM32-SDK 开发板上的 UART1-RS232 接口操作

---------硬件上的引脚连接:----------
RS232接口：
RS232TXD  -->  PA9  (UART1-TXD)
RS232RXD  -->  PA10 (UART1-RXD)
------------------------------------
 */

#include "UARTs.h"

u8 TxBuffer[258];
u8 TxCounter=0;
u8 count=0; 

extern char status;
/**************************实现函数********************************************
*函数原型:		void Initial_UART1(u32 baudrate)
*功　　能:		初始化STM32-SDK开发板上的RS232接口
输入参数：
		u32 baudrate   设置RS232串口的波特率
输出参数：没有	
*******************************************************************************/
void Initial_UART1(u32 baudrate)
{
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 |RCC_APB2Periph_USART1, ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// 时钟低电平活动
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// 时钟低电平
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// 时钟第二个边沿进行数据捕获
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// 最后一位数据的时钟脉冲不从SCLK输出
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART1, &USART_ClockInitStructure);					// 时钟参数初始化设置
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // 波特率为：115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART1, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//使能USART1中断源
USART_Cmd(USART1, ENABLE);							//USART1总开关：开启 
}

/**************************实现函数********************************************
*函数原型:		void UART1_Put_Char(unsigned char DataToSend)
*功　　能:		RS232发送一个字节
输入参数：
		unsigned char DataToSend   要发送的字节数据
输出参数：没有	
*******************************************************************************/
void UART1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);   
}

/**************************实现函数********************************************
*函数原型:		u8 UART1_Get_Char(void)
*功　　能:		RS232接收一个字节  一直等待，直到UART1接收到一个字节的数据。
输入参数：		 没有
输出参数：       UART1接收到的数据	
*******************************************************************************/
u8 UART1_Get_Char(void)
{
	while (!(USART1->SR & USART_FLAG_RXNE));
	return(USART_ReceiveData(USART1));
}

/**************************实现函数********************************************
*函数原型:		void UART1_Put_String(unsigned char *Str)
*功　　能:		RS232发送字符串
输入参数：
		unsigned char *Str   要发送的字符串
输出参数：没有	
*******************************************************************************/
void UART1_Put_String(unsigned char *Str)
{
	//判断Str指向的数据是否有效.
	while(*Str){
	//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
	if(*Str=='\r')UART1_Put_Char(0x0d);
		else if(*Str=='\n')UART1_Put_Char(0x0a);
			else UART1_Put_Char(*Str);
	//等待发送完成.
  	//while (!(USART1->SR & USART_FLAG_TXE));
	//指针++ 指向下一个字节.
	Str++;
	}

}


//------------------------------------------------------
void USART1_IRQHandler(void)
{

	char RX_dat;
  uint16_t pwm;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
  
  
		USART_ClearITPendingBit(USART1,   USART_IT_RXNE);

		RX_dat=USART_ReceiveData(USART1);// & 0x7F;
    status = RX_dat;
		//USART_SendData(USART1, RX_dat);

		//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
	}
  else if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    
    USART_SendData(USART1, TxBuffer[TxCounter++]);                    

    /* Clear the USART1 transmit interrupt */
    USART_ClearITPendingBit(USART1, USART_IT_TXE); 

    if(TxCounter == count)
    {
      /* Disable the USART1 Transmit interrupt */
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    }    

  }
  


}


//------------------End of File----------------------------
