#ifndef __PID_H_
#define __PID_H_
int Vertical_Ring_PD(float pitch,float gyro_y,int mechanicla_balance);
int Vertical_Speed_PI(float pitch,int encoder_left,int encoder_right,int movement);
int Vertical_Turn_PD(u8 CCD,float yaw);
int Turn_off(float pitch);
void PWM_Limiting(int *motor1,int *motor2);
void Get_PID_Data(float pitch,float yaw,float gyro_y,int encoder_left,int encoder_right,int Contrl_Turn,int *Motor_A,int *Motor_B);
#endif
