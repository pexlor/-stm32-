#ifndef __PWM_H
#define __PWM_H
void PWM_Init(void);
void Set_TIM3_Compare1(uint16_t Compare);
void Set_TIM3_Compare3(uint16_t Compare);
void Set_TIM3_Compare4(uint16_t Compare);
void Set_TIM3_Compare2(uint16_t Compare);
void PWM_Limiting(int *motor1,int *motor2);
#endif
