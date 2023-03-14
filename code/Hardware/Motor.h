#ifndef __MOTOR_H
#define __MOTOR_H
extern int MotorA;
extern int MotorB;
void Motor_Init(void);
void SetMotorASpeed(int16_t Speed);
void SetMotorBSpeed(int16_t Speed);
void SetMotor(int Motor_A,int Motor_B);
#endif
