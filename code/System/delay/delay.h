#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  
#include "stm32f10x.h"                  // Device header

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























