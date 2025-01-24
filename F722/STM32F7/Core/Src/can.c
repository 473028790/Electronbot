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
#include <string.h>
BoardConfig_t boardConfig[6];
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 12;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_5TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = ENABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
int cnt62=0;
void CAN1_Filterinit_And_Start(void)
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
	HAL_CAN_ConfigFilter(&hcan1,&can1_filter);//闁跨喐鏋婚幏宄邦潗闁跨喐鏋婚幏? CAN1 闁跨喐鏋婚幏鐑芥晸閺傘倖瀚归柨鐔告灮閹??
	HAL_CAN_Start(&hcan1);//闁跨喐鏋婚幏鐑芥晸閺傘倖瀚? CAN1
	HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);//闁跨喐鏋婚幏鐑芥晸閺傘倖瀚笴AN1 FIFO0 闁跨喐鏋婚幏鐑芥晸閺傘倖瀚?
}

float bytes_to_float(uint8_t *data) 
{
  float value;
  memcpy(&value, data, sizeof(float));
  return value;
}


void Can_Send_uint8(uint8_t motor_id,uint8_t type,uint8_t data)
{
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x500+motor_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];
	Data[0]=type;
	Data[1]=data;
	Data[2]=0;
	Data[3]=0;
	Data[4]=0;
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;
	HAL_CAN_AddTxMessage(&hcan1,&tx,Data,(uint32_t *)CAN_TX_MAILBOX0);
}
void Can_Send_uint16(uint8_t motor_id,uint8_t type,uint16_t data)
{
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x500+motor_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];
	Data[0]=type;
	Data[1]=data>>8;
	Data[2]=data;
	Data[3]=0;
	Data[4]=0;
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;
	HAL_CAN_AddTxMessage(&hcan1,&tx,Data,(uint32_t *)CAN_TX_MAILBOX0);
}
void Can_Send_float(uint8_t motor_id,uint8_t type,float data)
{
	CAN_TxHeaderTypeDef tx;

	tx.StdId = 0x500+motor_id;
	tx.RTR = CAN_RTR_DATA;
	tx.IDE = CAN_ID_STD;
	tx.DLC = 8;

	static uint8_t Data[8];
  uint8_t* pFloat = (uint8_t*) &data;
	Data[0]=type;
  Data[1] = pFloat[0]; // 浣庡瓧鑺?
  Data[2] = pFloat[1];
  Data[3] = pFloat[2];
  Data[4] = pFloat[3]; // 楂樺瓧鑺?
	Data[5]=0;
	Data[6]=0;
	Data[7]=0;
	HAL_CAN_AddTxMessage(&hcan1,&tx,Data,(uint32_t *)CAN_TX_MAILBOX0);
}

//CAN_RxHeaderTypeDef CAN1_RX;
//uint8_t Data[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef CAN1_RX;
  static uint8_t can_recive_id;

	if(hcan->Instance==CAN1)     //CAN1
	{
    static uint8_t Data[8];
		HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&CAN1_RX,Data);
    can_recive_id=CAN1_RX.StdId/0x50;
		switch(CAN1_RX.StdId%0x50)
		{
			case 1:
			  boardConfig[can_recive_id].actual_angle=bytes_to_float(&Data[0]);
        	  boardConfig[can_recive_id].enableMotorOnBoot=Data[4];
			break;
			case 2:
			  boardConfig[can_recive_id].initPos=bytes_to_float(&Data[0]);
			break;
			case 3:
			  boardConfig[can_recive_id].toqueLimit=bytes_to_float(&Data[0]);
			break;
			case 4:
			  boardConfig[can_recive_id].velocityLimit=bytes_to_float(&Data[0]);
			break;



			case 5:
			  boardConfig[can_recive_id].adcValAtAngleMin=(Data[0] << 8 | Data[1]);
			break;
			case 6:
			  boardConfig[can_recive_id].adcValAtAngleMax=(Data[0] << 8 | Data[1]);
			break;
			case 7:
			  boardConfig[can_recive_id].mechanicalAngleMin=bytes_to_float(&Data[0]);
			break;
			case 8:
			  boardConfig[can_recive_id].mechanicalAngleMax=bytes_to_float(&Data[0]);
			break;
			case 9:
			  boardConfig[can_recive_id].dceKp=bytes_to_float(&Data[0]);
			break;
			case 10:
			  boardConfig[can_recive_id].dceKv=bytes_to_float(&Data[0]);
			break;
			case 11:
			  boardConfig[can_recive_id].dceKi=bytes_to_float(&Data[0]);
			break;
			case 12:
			  boardConfig[can_recive_id].dceKd=bytes_to_float(&Data[0]);
			break;
			case 13:
			  boardConfig[can_recive_id].enableMotorOnBoot=Data[0];
			break;

			default: {break;}	
		}
	}
}


/* USER CODE END 1 */
