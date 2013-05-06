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


/**************************实现函数********************************************
*函数原型:		void Initial_UART1(u32 baudrate)
*功　　能:		初始化STM32-SDK开发板上的RS232接口
输入参数：
		u32 baudrate   设置RS232串口的波特率
输出参数：没有	
*******************************************************************************/
void Initial_UART1(u32 baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* 使能 UART1 模块的时钟  使能 UART1对应的引脚端口PA的时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

  /* 配置UART1 的发送引脚
	配置PA9 为复用输出  刷新频率50MHz
	*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  /* 
	配置UART1 的接收引脚
	配置PA10为浮地输入 
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	/* 
  UART1的配置:
  1.波特率为调用程序指定的输入 baudrate;
  2. 8位数据			  USART_WordLength_8b;
  3.一个停止位			  USART_StopBits_1;
  4. 无奇偶效验			  USART_Parity_No ;
  5.不使用硬件流控制	  USART_HardwareFlowControl_None;
  6.使能发送和接收功能	  USART_Mode_Rx | USART_Mode_Tx;
  */
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//应用配置到UART1
	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//启动UART1
  USART_Cmd(USART1, ENABLE);
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
	//将要发送的字节写到UART1的发送缓冲区
	//USART_SendData(USART1, (unsigned char) DataToSend);
	//等待发送完成
  	//while (!(USART1->SR & USART_FLAG_TXE));

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
/*
	//判断Str指向的数据是否有效.
	while(*Str){
	//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
	if(*Str=='\r')USART_SendData(USART1, 0x0d);
		else if(*Str=='\n')USART_SendData(USART1, 0x0a);
			else USART_SendData(USART1, *Str);
	//等待发送完成.
  	while (!(USART1->SR & USART_FLAG_TXE));
	//指针++ 指向下一个字节.
	Str++;
	}		 */
}


//------------------------------------------------------
void USART1_IRQHandler(void)
{

  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    char recvData;
    // clear receive interrupt flag
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    recvData = USART_ReceiveData(USART1) & 0x7F;
    USART_SendData(USART1, recvData);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
  }

  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
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
