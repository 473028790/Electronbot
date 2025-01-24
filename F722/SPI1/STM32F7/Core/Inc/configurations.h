#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <stdbool.h>
#include "main.h"

#define BOARD_CONFIG_SIZE (sizeof(BoardConfig_t))

typedef struct Config_t
{
    uint8_t nodeId;//device ID
    float initPos;//init position
    float toqueLimit;//扭矩限制
    float velocityLimit;//速度限制
    uint16_t adcValAtAngleMin;//最小角度对应的ADC值
    uint16_t adcValAtAngleMax;//最大角度对应的ADC值
    float mechanicalAngleMin;//机械最小角度
    float mechanicalAngleMax;//机械最大角度
    float dceKp;
    float dceKv;
    float dceKi;
    float dceKd;
	
		float set_Kp;
		float set_Ki;
		float set_Kd;
    bool enableMotorOnBoot;//使能
    float actual_angle;
    float target_angle;
} BoardConfig_t;

extern BoardConfig_t boardConfig[6];

#endif

