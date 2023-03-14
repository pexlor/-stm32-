#include "OLED.h"
#include "My_I2C.h"
#include "OLED_font.h"
#include "stm32f10x.h"                  
#include "mpu6050.h"
void WriteCmd(unsigned char I2C_Command)//???
 {

		//HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,COM,I2C_MEMADD_SIZE_8BIT,&I2C_Command,1,100);
	 MPU_Write_Len(OLED0561_ADD>>1,COM,1,&I2C_Command);
//	IIC_Start();
//	IIC_Send_Byte(OLED0561_ADD);		//´Ó»úµØÖ·
//	IIC_Send_Byte(COM);		//Ð´ÃüÁî
//	IIC_Send_Byte(I2C_Command); 
//	IIC_Stop();
 }
		
void WriteDat(unsigned char I2C_Data)//???
 {

		//HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,DAT,I2C_MEMADD_SIZE_8BIT,&I2C_Data,1,100);
	 MPU_Write_Len(OLED0561_ADD>>1,DAT,1,&I2C_Data);
//	IIC_Start();
//	IIC_Send_Byte(OLED0561_ADD);		//´Ó»úµØÖ·
//	IIC_Send_Byte(DAT);		//Ð´Êý¾Ý
//	IIC_Send_Byte(I2C_Data);
//	IIC_Stop();
  }
 
	void OLED_Init(void)
{

	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //???? 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

void OLED_SetPos(unsigned char x, unsigned char y) //???????
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char fill_Data)//????
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}


void OLED_CLS(void)//??
{
	OLED_Fill(0x00);
}

void OLED_ON(void)
{
	WriteCmd(0X8D);  //?????
	WriteCmd(0X14);  //?????
	WriteCmd(0XAF);  //OLED??
}

void OLED_OFF(void)
{
	WriteCmd(0X8D);  //?????
	WriteCmd(0X10);  //?????
	WriteCmd(0XAE);  //OLED??
}


// Parameters     : x,y -- ?????(x:0~127, y:0~7); ch[] -- ???????; TextSize -- ????(1:6*8 ; 2:8*16)
// Description    : ??codetab.h??ASCII??,?6*8?8*16???
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}


// Parameters     : x,y -- ?????(x:0~127, y:0~7); N:???.h????
// Description    : ??ASCII_8x16.h????,16*16??
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}



// Parameters     : x0,y0 -- ?????(x0:0~127, y0:0~7); x1,y1 -- ?????(???)???(x1:1~128,y1:1~8)
// Description    : ??BMP??
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}






void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//???????			
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_SetPos(x,y);	
			for(i=0;i<8;i++)
			WriteDat(F8X16[c*16+i]);
			OLED_SetPos(x,y+1);
			for(i=0;i<8;i++)
			WriteDat(F8X16[c*16+i+8]);
			}
			else {	
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
				WriteDat(F6x8[c][i]);
				
			}
}
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(6*size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(6*size2/2)*t,y,temp+'0',size2); 
	}
} 
void OLED_ShowFloat(uint8_t x,uint8_t y,float num, uint8_t len, uint8_t size2)
{
	uint32_t temp;
	float num1=num;
	float temp2;
	temp=(int)num1;
	OLED_ShowNum(x,y,temp,len,size2);
	temp2=num-temp;
	temp2=temp2*100;
	temp=(int)(temp2);
	OLED_ShowChar(x+(6*size2/2)*len,y,'.',2);
	OLED_ShowNum(x+(6*size2/2)*(len+1),y,temp,2,size2);
}
