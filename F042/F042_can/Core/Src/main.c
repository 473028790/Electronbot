/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "User_montor.h"
#include "configurations.h"
#include "stmflash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
BoardConfig_t boardConfig;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint16_t adcData[1];

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_CAN_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	CAN_Filterinit_And_Start();
	HAL_ADCEx_Calibration_Start(&hadc);    //AD??
	HAL_ADC_Start_DMA(&hadc, (uint32_t*)adcData, 1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
	__HAL_TIM_CLEAR_IT(&htim2,TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim2);
	
	//write_board_config_to_flash(FLASH_SAVE_ADDR);
  read_board_config_from_flash(FLASH_SAVE_ADDR);
  if(boardConfig.configStatus != CONFIG_OK)
  {
    user_boardConfig_init();
  }
  Montor_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (boardConfig.configStatus == CONFIG_COMMIT)
    {
        boardConfig.configStatus = CONFIG_OK;
        write_board_config_to_flash(FLASH_SAVE_ADDR);
    }
    HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
extern Motor user_motor;
extern uint16_t Can_Send_Sign;
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
float cnt66=0;
int cnt15=0;
int16_t montor_out_pwm;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  static float User_motor_angle;
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM2) {
  /* USER CODE BEGIN Motor_control */
		//static int16_t montor_out_pwm;
		/* Infinite loop */
		cnt15++;
		HAL_ADC_Start_DMA(&hadc, (uint32_t*)adcData, 1);
		montor_out_pwm=CalcDceOutput(&user_motor, (float)adcData[0]);
		SetPwm(&user_motor, montor_out_pwm);

    User_motor_angle=boardConfig.mechanicalAngleMin +
                      (boardConfig.mechanicalAngleMax - boardConfig.mechanicalAngleMin) *
                      ((float) adcData[0] - (float) boardConfig.adcValAtAngleMin) /
                      ((float) boardConfig.adcValAtAngleMax - (float) boardConfig.adcValAtAngleMin);
		//cnt66=User_motor_angle;
    switch (Can_Send_Sign)
    {
      case 0://默认
				cnt66=0x50*(boardConfig.nodeId-1)+1;
        CAN_data_TX(0x50*(boardConfig.nodeId-1)+1,User_motor_angle,boardConfig.enableMotorOnBoot);
      break;
      case 1:
        CAN_data_TX_u8(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.nodeId);
      break;
      case 2:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.initPos);
      break;
      case 3:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.toqueLimit);
      break;
      case 4:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.velocityLimit);
      break;
      case 5:
        CAN_data_TX_u16(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.adcValAtAngleMin);
      break;
      case 6:
        CAN_data_TX_u16(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.adcValAtAngleMax);
      break;
      case 7:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.mechanicalAngleMin);
      break;
      case 8:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.mechanicalAngleMax);
      break;
      case 9:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.dceKp);
      break;
      case 10:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.dceKv);
      break;
      case 11:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.dceKi);
      break;
      case 12:
        CAN_data_TX_float(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.dceKd);
      break;
      case 13:
        CAN_data_TX_u8(0x50*(boardConfig.nodeId-1)+Can_Send_Sign,boardConfig.enableMotorOnBoot);
      break;
      default:
      break;
    }
    if(Can_Send_Sign!=0)
    {
      Can_Send_Sign=0;
    }
	
		__HAL_TIM_CLEAR_IT(&htim2,TIM_IT_UPDATE);
  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
