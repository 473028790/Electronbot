#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <stdbool.h>
#include "main.h"

#define BOARD_CONFIG_SIZE (sizeof(BoardConfig_t))
	

typedef enum configStatus_t
{
    CONFIG_RESTORE = 0,  // 表示恢复默认配置状态
    CONFIG_OK,           // 表示配置正常
    CONFIG_COMMIT        // 表示配置已提交
} configStatus_t;


typedef struct Config_t
{
    configStatus_t configStatus;
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
    bool enableMotorOnBoot;//使能
} BoardConfig_t;

extern BoardConfig_t boardConfig;

#endif

