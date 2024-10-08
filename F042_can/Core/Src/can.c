/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include "configurations.h"
#include "User_montor.h"
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 6;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = ENABLE;
  hcan.Init.AutoWakeUp = ENABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspInit 0 */

  /* USER CODE END CAN_MspInit 0 */
    /* CAN clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_CAN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN interrupt Init */
    HAL_NVIC_SetPriority(CEC_CAN_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(CEC_CAN_IRQn);
  /* USER CODE BEGIN CAN_MspInit 1 */

  /* USER CODE END CAN_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspDeInit 0 */

  /* USER CODE END CAN_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN interrupt Deinit */
    HAL_NVIC_DisableIRQ(CEC_CAN_IRQn);
  /* USER CODE BEGIN CAN_MspDeInit 1 */

  /* USER CODE END CAN_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CAN_Filterinit_And_Start(void)
{
	CAN_FilterTypeDef can1_filter;
	can1_filter.FilterBank = 0;
	can1_filter.FilterMode = CAN_FILTERMODE_IDMASK;
	can1_filter.FilterScale = CAN_FILTERSCALE_32BIT;
	can1_filter.FilterIdHigh = 0x0000;
	can1_filter.FilterIdLow = 0x0000;
	can1_filter.FilterMaskIdHigh = 0x0000;
	can1_filter.FilterMaskIdLow = 0x0000;
	can1_filter.FilterFIFOAssignment = 0;
	can1_filter.FilterActivation = ENABLE;
	can1_filter.SlaveStartFilterBank = 0;
	HAL_CAN_ConfigFilter(&hcan,&can1_filter);//??'?? CAN1 ??????
	HAL_CAN_Start(&hcan);//???? CAN1
	HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING);//????CAN1 FIFO0 ????

	
}
extern Motor user_motor;
void CAN_data_TX(uint32_t Can_id,float motor1_angle,uint8_t enable)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x300+Can_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];
  // 使用指针将 float 的字节表示复制到 Data 数组
  uint8_t* pFloat = (uint8_t*) &motor1_angle;
  Data[0] = pFloat[3]; // 高字节
  Data[1] = pFloat[2];
  Data[2] = pFloat[1];
  Data[3] = pFloat[0]; // 低字节

	Data[4]=enable;
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;

	HAL_CAN_AddTxMessage(&hcan, &tx, Data, &TxMailbox);
}

void CAN_data_TX_u8(uint32_t Can_id,uint8_t data)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x300+Can_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];

  Data[0]= data; // 高字节
  Data[1]= 0;
  Data[2]= 0;
  Data[3]= 0; // 低字节
	Data[4]=0;
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;

	HAL_CAN_AddTxMessage(&hcan, &tx, Data, &TxMailbox);
}
void CAN_data_TX_u16(uint32_t Can_id,uint16_t data)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x300+Can_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];

  Data[0]= data>>8; // 高字节
  Data[1]= data;// 低字节
  Data[2]= 0;
  Data[3]= 0;
	Data[4]=0;
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;

	HAL_CAN_AddTxMessage(&hcan, &tx, Data, &TxMailbox);
}
void CAN_data_TX_float(uint32_t Can_id,float motor1_angle)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x300+Can_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];
  // 使用指针将 float 的字节表示复制到 Data 数组
  uint8_t* pFloat = (uint8_t*) &motor1_angle;
  Data[0] = pFloat[3]; // 高字节
  Data[1] = pFloat[2];
  Data[2] = pFloat[1];
  Data[3] = pFloat[0]; // 低字节

	Data[4]=0;
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;

	HAL_CAN_AddTxMessage(&hcan, &tx, Data, &TxMailbox);
}

uint16_t Can_Send_Sign=0;
float target_angle;
float bytes_to_float(uint8_t *data) 
{
  float value;
  // 使用 memcpy 确保不会发生内存对齐问题
  memcpy(&value, data, sizeof(float));
  return value;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef CAN_RX;
  //static float target_angle;
	if(hcan->Instance==CAN)     //CAN1
	{
    static uint8_t Data[8];
		HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RX,Data);
    if(CAN_RX.StdId-0x500==boardConfig.nodeId)
    {
      switch(Data[0])
      {
        case 0x01:
          boardConfig.nodeId=Data[1];
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x02:
          boardConfig.initPos = bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x03:
          boardConfig.toqueLimit=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x04:
          boardConfig.velocityLimit=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x05:
          boardConfig.adcValAtAngleMin=(Data[1] << 8 | Data[2]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x06:
          boardConfig.adcValAtAngleMax=(Data[1] << 8 | Data[2]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x07:
          boardConfig.mechanicalAngleMin=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x08:
          boardConfig.mechanicalAngleMax=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x09:
          boardConfig.dceKp=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x10:
          boardConfig.dceKv=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x11:
          boardConfig.dceKi=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x12:
          boardConfig.dceKd=bytes_to_float(&Data[1]);
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
        case 0x13:
          boardConfig.enableMotorOnBoot=Data[1];
          boardConfig.configStatus = CONFIG_COMMIT;
        break;
       case 0x14:
          //uint8_t temp1[4] = { Data[1], Data[2], Data[3], Data[4] };  // 按小端序排列
          //target_angle = *(float*)temp1;
          target_angle = bytes_to_float(&Data[1]);

          user_motor.dce.setPointPos = boardConfig.adcValAtAngleMin + 
                  ((target_angle - boardConfig.mechanicalAngleMin) * 
                  (boardConfig.adcValAtAngleMax - boardConfig.adcValAtAngleMin)) / 
                  (boardConfig.mechanicalAngleMax - boardConfig.mechanicalAngleMin);
          if(user_motor.dce.setPointPos>=boardConfig.adcValAtAngleMax) user_motor.dce.setPointPos=boardConfig.adcValAtAngleMax;
          if(user_motor.dce.setPointPos<=boardConfig.adcValAtAngleMin) user_motor.dce.setPointPos=boardConfig.adcValAtAngleMin;
        break;
        default: {break;}	
      }
    }
    else if (CAN_RX.StdId-600==boardConfig.nodeId)
    {
          Can_Send_Sign = Data[0];
    }
	}
}

/* USER CODE END 1 */
