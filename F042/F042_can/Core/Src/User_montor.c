#include "User_montor.h"
#include "tim.h"
#include "configurations.h"

Motor user_motor;
void user_boardConfig_init(void)
{
    boardConfig.configStatus=CONFIG_RESTORE;
    boardConfig.nodeId=0x04;//device ID
    boardConfig.initPos=1519;//init position
    boardConfig.toqueLimit=800;//扭矩限制
    boardConfig.velocityLimit=1000.0f;//速度限制
    boardConfig.adcValAtAngleMin=0;//最小角度对应的ADC值
    boardConfig.adcValAtAngleMax=3050;//最大角度对应的ADC值
    boardConfig.mechanicalAngleMin=0;//机械最小角度
    boardConfig.mechanicalAngleMax=180;//机械最大角度
//	    boardConfig.dceKp=2.2;
//    boardConfig.dceKi=0.3;
    boardConfig.dceKp=0.6;
    boardConfig.dceKi=0.05;
    boardConfig.dceKd=0;
    boardConfig.enableMotorOnBoot=0.;//使能
}
void Montor_init(void)
{
	user_motor.dce.kp=boardConfig.dceKp;
	user_motor.dce.ki=boardConfig.dceKi;
	user_motor.dce.kd=boardConfig.dceKd;
	user_motor.dce.setPointPos=boardConfig.initPos;
	user_motor.limitTorque=boardConfig.toqueLimit;
}
//pid
float CalcDceOutput(Motor* motor, float inputPos)
{
    Dce* dce = &(motor->dce);  
    
    float errorPos = inputPos - dce->setPointPos;
    float deltaPos = errorPos - dce->lastError;
    dce->lastError = errorPos;


    dce->integralPos += errorPos;
    if (dce->integralPos > boardConfig.velocityLimit) 
        dce->integralPos = boardConfig.velocityLimit;
    else if (dce->integralPos < -boardConfig.velocityLimit) 
        dce->integralPos = -boardConfig.velocityLimit;


    dce->output = dce->kp * errorPos +
                  dce->ki * dce->integralPos + 
                  dce->kd * deltaPos;

    if (dce->output > motor->limitTorque) 
        dce->output = motor->limitTorque;
    else if (dce->output < -motor->limitTorque) 
        dce->output = -motor->limitTorque;

    return dce->output;
}
// yinyan min
void SetPwm(Motor* motor, int16_t pwm)
{
    if (boardConfig.enableMotorOnBoot==1)
    {
        if (pwm >= 0)
        {//ADC DOWN
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm > 1000 ? 1000 : pwm);
        }
        else
        {//ADC UP
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm < -1000 ? 1000 : -pwm);
        }
    }
    else
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
    }
}



// yinyan plus
//void SetPwm(Motor* motor, int16_t pwm)
//{
//    if (boardConfig.enableMotorOnBoot==1)
//    {
//        if (pwm >= 0)
//        {//ADC DOWN
//            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm > 1000 ? 1000 : pwm);
//        }
//        else
//        {//ADC UP
//            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
//            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm < -1000 ? 1000 : -pwm);
//        }
//    }
//    else
//    {
//        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
//        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//    }
//}