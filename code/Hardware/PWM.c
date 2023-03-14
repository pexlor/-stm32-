#include "stm32f10x.h"                  // Device header
uint16_t Compare_1;
uint16_t Compare_2;
void PWM_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//TIME3 CH1234
	
	TIM_InternalClockConfig(TIM3);//使用内部时钟
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=8000-1;//自动重1装器ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//预分频PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=0;//比较的值
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);
	TIM_OC4Init(TIM3,&TIM_OCInitStruct);
	TIM_Cmd(TIM3,ENABLE);
}
void Set_TIM3_Compare1(uint16_t Compare){
	TIM_SetCompare1(TIM3,Compare);
}
void Set_TIM3_Compare2(uint16_t Compare){
	TIM_SetCompare2(TIM3,Compare);
}
void Set_TIM3_Compare3(uint16_t Compare){
	TIM_SetCompare3(TIM3,Compare);
}
void Set_TIM3_Compare4(uint16_t Compare){
	TIM_SetCompare4(TIM3,Compare);
}



