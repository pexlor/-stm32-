#ifndef __ENCODER_H
#define __ENCODER_H
extern int16_t Encoder_A;
extern int16_t Encoder_B;
void Encoder_Init(void);
int16_t Encoder_Get_A(void);
int16_t Encoder_Get_B(void);
#endif
