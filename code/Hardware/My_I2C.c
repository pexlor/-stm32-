#include "stm32f10x.h"                  // Device header
#include "My_I2C.h"
#define GPIO_PORT_IIC     GPIOB                       //GPIO端口 
#define IIC_SCL_PIN       GPIO_Pin_8                  // 连接到SCL时钟线的GPIO 
#define IIC_SDA_PIN       GPIO_Pin_9                  // 连接到SDA数据线的GPIO 


#define IIC_SCL_1()  GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1))		// SCL = 1 
#define IIC_SCL_0()  GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(0))	// SCL = 0 

#define IIC_SDA_1()  GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(1))		// SDA = 1 
#define IIC_SDA_0()  GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(0))		// SDA = 0 

#define IIC_SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_IIC, IIC_SDA_PIN)	//读SDA口线状态

static void IIC_Delay(void)
{
    uint8_t i;
    for (i = 0; i < 1 ; i++);
}


void IIC_Start(void)
{
    
    IIC_SDA_1();
    IIC_SCL_1();
    IIC_Delay();
    IIC_SDA_0();
    IIC_Delay();
    IIC_SCL_0();
    IIC_Delay();
}

void IIC_Stop(void)
{
    IIC_SDA_0();
    IIC_SCL_1();
    IIC_Delay();
    IIC_SDA_1();
}


void IIC_Send_Byte(uint8_t _ucByte)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        if (_ucByte & 0x80)
        {
            IIC_SDA_1();
        }
        else
        {
            IIC_SDA_0();
        }
        IIC_Delay();
        IIC_SCL_1();
        IIC_Delay();
        IIC_SCL_0();
        if (i == 7)
        {
            IIC_SDA_1();
        }
        _ucByte <<= 1;
        IIC_Delay();
    }
}


uint8_t IIC_Read_Byte(uint8_t ack)
{
    uint8_t i;
    uint8_t value;

    
    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        IIC_SCL_1();
        IIC_Delay();
        if (IIC_SDA_READ())
        {
            value++;
        }
        IIC_SCL_0();
        IIC_Delay();
    }
    if(ack==0)
        IIC_NAck();
    else
        IIC_Ack();
    return value;
}


uint8_t IIC_Wait_Ack(void)
{
    uint8_t re;

    IIC_SDA_1();	
    IIC_Delay();
    IIC_SCL_1();	
    IIC_Delay();
    if (IIC_SDA_READ())	
    {
        re = 1;
    }
    else
    {
        re = 0;
    }
    IIC_SCL_0();
    IIC_Delay();
    return re;
}


void IIC_Ack(void)
{
    IIC_SDA_0();	
    IIC_Delay();
    IIC_SCL_1();	
    IIC_Delay();
    IIC_SCL_0();
    IIC_Delay();
    IIC_SDA_1();	
}

void IIC_NAck(void)
{
    IIC_SDA_1();	
    IIC_Delay();
    IIC_SCL_1();	
    IIC_Delay();
    IIC_SCL_0();
    IIC_Delay();
}

void IIC_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_Init(GPIOB, &GPIO_InitStructure); 	/* 开漏输出 */
    IIC_Stop();
}

uint8_t IIC_CheckDevice(uint8_t _Address)
{
    uint8_t ucAck;

    IIC_GPIO_Init();		

    IIC_Start();		

    IIC_Send_Byte(_Address|IIC_WR);
    ucAck = IIC_Wait_Ack();
    IIC_Stop();		

    return ucAck;
}
