#ifndef __USER_MONTOR_H__
#define __USER_MONTOR_H__
#include "main.h"

typedef struct {
    float setPointPos;
    float lastError;
    float integralPos;
    float kp;
    float ki;
    float kd;
    float output;
} Dce;

typedef struct {
    Dce dce;
    float limitTorque;
} Motor;


void Montor_init(void);
float CalcDceOutput(Motor* motor, float inputPos);
void SetPwm(Motor* motor, int16_t pwm);
void user_boardConfig_init(void);
#endif
