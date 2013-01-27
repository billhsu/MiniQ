#include "ioi2c.h"

/******************************************************************************
/ 函数功能:I2C接口配置程序
/ 修改日期:none
/ 输入参数:none
/ 输出参数:none
/ 使用说明:none
******************************************************************************/
void I2C_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
    
  //关闭JTAG使能SWD以释放IO口
  uint32_t u32Temp;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB , ENABLE);
  u32Temp = AFIO->MAPR;
  u32Temp &= ~AFIO_MAPR_SWJ_CFG ;
  u32Temp |= AFIO_MAPR_SWJ_CFG_1;
  AFIO->MAPR = u32Temp;
  
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB , ENABLE);
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
  
  //配置I2C的SCL引脚和SDA引脚
  RCC_APB2PeriphClockCmd(IMU_I2C_GPIO_CLK , ENABLE);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin =  IMU_I2C_SclPin;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Pin =   IMU_I2C_SdaPin;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  SCL_H;SDA_H;    //总线释放
}

/******************************************************************************
/ 函数功能:Simulation IIC Timing series delay
/ 修改日期:none
/ 输入参数:none
/ 输出参数:none
/ 使用说明:none
******************************************************************************/
__inline void I2C_delay(void)
{
        
   u8 i=I2C_DELAY_VAL; //这里可以优化速度   ，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   }  
}


/******************************************************************************
/ 函数功能:延时5ms时间
/ 修改日期:none
/ 输入参数:none
/ 输出参数:none
/ 使用说明:none
******************************************************************************/


/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather  Start
****************************************************************************** */
bool I2C_Start(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    if(!SDA_read)return false;  //SDA线为低电平则总线忙,退出
    SDA_L;
    I2C_delay();
    if(SDA_read) return false;  //SDA线为高电平则总线出错,退出
    SDA_L;
    I2C_delay();
    return true;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Ack(void)
{   
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)
{   
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather  Reserive Slave Acknowledge Single
****************************************************************************** */
bool I2C_WaitAck(void)   //返回为:=1有ACK,=0无ACK
{
    SCL_L;
    I2C_delay();
    SDA_H;          
    I2C_delay();
    SCL_H;
    I2C_delay();
    if(SDA_read)
    {
      SCL_L;
      I2C_delay();
      return false;
    }
    SCL_L;
    I2C_delay();
    return true;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_SendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
uint8_t I2C_RadeByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;              
    while(i--)
    {
        ReceiveByte<<=1;      
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();  
        if(SDA_read)
        {
          ReceiveByte|=0x01;
        }
    }
    SCL_L;
    return ReceiveByte;
} 
/******************************************************************************
/ 函数功能:单字节写入
/ 修改日期:none
/ 输入参数:
/   @arg SlaveAddress   从器件地址
/   @arg REG_Address    寄存器地址
/   @arg REG_data       欲写入的字节数据
/ 输出参数: 读出的字节数据
/ 使用说明:这时一个完整的单字节读取函数
******************************************************************************/
bool Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
    if(!I2C_Start())return false;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return false;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();  
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    return true;
}

/******************************************************************************
/ 函数功能:单字节写入
/ 修改日期:none
/ 输入参数:
/   @arg SlaveAddress   从器件地址
/   @arg REG_Address    寄存器地址
/   @arg REG_data       欲写入的字节数据
/ 输出参数: 读出的字节数据
/ 使用说明:这时一个完整的单字节读取函数
******************************************************************************/
bool Fast_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
    if(!I2C_Start())return false;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return false;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();  
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    return true;
}



/******************************************************************************
/ 函数功能:单字节写入
/ 修改日期:none
/ 输入参数:
/   @arg SlaveAddress   从器件地址
/   @arg REG_Address    寄存器地址
/ 输出参数: 读出的字节数据
/ 使用说明:这时一个完整的单字节读取函数
******************************************************************************/
uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address)
{   
    uint8_t REG_data;       
    if(!I2C_Start())return false;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop();return false;}
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

    REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    //return true;
    return REG_data;
}

/******************************************************************************
/ 函数功能:多字节读出函数
/ 修改日期:none
/ 输入参数:
/   @arg SlaveAddress   从器件地址
/   @arg REG_Address    寄存器地址
/   @arg ptChar         输出缓冲
/   @arg size           读出的数据个数,size必须大于=1
/ 输出参数: 成功失败标记
/ 使用说明:none
******************************************************************************/
bool Mult_Read(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t * ptChar,uint8_t size)
{
    uint8_t i;
    
    if(size < 1)return false;
    if(!I2C_Start())return false;
    I2C_SendByte(SlaveAddress);
    if(!I2C_WaitAck()){I2C_Stop();return false;}
    I2C_SendByte(REG_Address);    
    I2C_WaitAck();
    
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();
    
    //连续读出ax,ay,az数据
    for(i=1;i<size; i++)
    {
        *ptChar++ = I2C_RadeByte();
        I2C_Ack();
    }
    *ptChar++ = I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    return true;    
}




