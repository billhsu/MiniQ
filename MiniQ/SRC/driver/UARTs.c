/* UARTs.C file

功能：实现	STM32-SDK 开发板上的 UART1-RS232 接口操作

---------硬件上的引脚连接:----------
RS232接口：
RS232TXD  -->  PA9  (UART1-TXD)
RS232RXD  -->  PA10 (UART1-RXD)
------------------------------------
 */

#include "UARTs.h"
#include "../algorithm/control.h"
#include "extern_variable.h"
u8 TxBuffer[258];
u8 TxCounter=0;
u8 count=0; 
u8 start_mark[2]={0xff,0xaa};
u8 recvStatus=0;
u8 recvCmd=0;
u8 recvLength=0;
u8 recvPos=0;
u8 recvData[8]={0,0,0,0,0,0,0,0};
extern char baseThr;

extern PID PID_RP;
void parseCmd(u8 cmd, u8 len);
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
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1,   USART_IT_RXNE);

		RX_dat=USART_ReceiveData(USART1);// & 0x7F;
    //status = RX_dat;
    if(recvStatus==0)
    {
      if(RX_dat==0xff) recvStatus=1;
    }
    else if(recvStatus==1)
    {
      if(RX_dat==0xaa) recvStatus=2;
      else recvStatus=0;
    }
    else if(recvStatus==2)
    {
      recvCmd=RX_dat;
      recvStatus=3;
    }
    else if(recvStatus==3)
    {
      recvLength=RX_dat;
      recvStatus=4;
    }
    else if(recvStatus==4)
    {
      if(recvPos<recvLength)
      {
        recvData[recvPos]=RX_dat;
        ++recvPos;
      }
      if(recvPos==recvLength) 
      {
        parseCmd(recvCmd,recvLength);
        recvPos=0;
        recvStatus=0;
      }
    }
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


void parseCmd(u8 cmd, u8 len)
{
  char* temp;
  switch (cmd)
  {
    case 0x01:
      baseThr=recvData[0];
      break;
    case 0x02:
      temp=(char*)(&PID_RP.P);
      temp[0] = recvData[0];
      temp[1] = recvData[1];
      temp[2] = recvData[2];
      temp[3] = recvData[3];
      break;
    case 0x03:
      temp=(char*)(&PID_RP.D);
      temp[0] = recvData[0];
      temp[1] = recvData[1];
      temp[2] = recvData[2];
      temp[3] = recvData[3];
    break;
    case 0x04:
      temp=(char*)(&PID_RP.I);
      temp[0] = recvData[0];
      temp[1] = recvData[1];
      temp[2] = recvData[2];
      temp[3] = recvData[3];
    break;
    case 0x05:
      temp=(char*)(&EXP_ANGLE.X);
      temp[0] = recvData[0];
      temp[1] = recvData[1];
      temp[2] = recvData[2];
      temp[3] = recvData[3];
    break;
    case 0x06:
      temp=(char*)(&EXP_ANGLE.Y);
      temp[0] = recvData[0];
      temp[1] = recvData[1];
      temp[2] = recvData[2];
      temp[3] = recvData[3];
    break;
    case 0x07:
      temp=(char*)(&EXP_ANGLE.Z);
      temp[0] = recvData[0];
      temp[1] = recvData[1];
      temp[2] = recvData[2];
      temp[3] = recvData[3];
    break;
  }
  
}

//------------------End of File----------------------------
