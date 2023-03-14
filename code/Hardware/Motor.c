#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "PID.h"
#include <stdlib.h>
#define DeedLine 3000
int MotorA=0;
int MotorB=0;
void Motor_Init(void){
	PWM_Init();
}

void SetMotorASpeed(int16_t Speed){
	if(Speed<=0){
		Set_TIM3_Compare1(0);
		Set_TIM3_Compare2(abs(Speed)+DeedLine);
	}else{
		Set_TIM3_Compare1(abs(Speed)+DeedLine);
		Set_TIM3_Compare2(0);
	}
}

void SetMotorBSpeed(int16_t Speed){
	if(Speed<=0){
		Set_TIM3_Compare3(0);
		Set_TIM3_Compare4(abs(Speed)+DeedLine);
	}else{
		Set_TIM3_Compare3(abs(Speed)+DeedLine);
		Set_TIM3_Compare4(0);
	}
}

void SetMotor(int Motor_A,int Motor_B){
	SetMotorASpeed(Motor_A);
	SetMotorBSpeed(Motor_B);
}


