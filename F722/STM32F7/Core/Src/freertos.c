/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "screen.h"
#include "can.h"
#include "image.h"
#include "User_usb.h"
#include "configurations.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void screen_task(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, screen_task, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
bool User_Usb_Finish;
int cnty=0;
uint8_t isEnabled;
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
		cnty++;
    if(User_Usb_Finish==1)
    {
      // get joint angles
      uint8_t* ptr = GetExtraDataRxPtr();
			memcpy(&boardConfig[0].target_angle, ptr + 1, sizeof(float));

      if (isEnabled != (bool) ptr[0])
      {
          isEnabled = ptr[0];
          Can_Send_uint8(0x01,0x13,isEnabled);
          Can_Send_uint8(0x06,0x13,isEnabled);
          Can_Send_uint8(0x03,0x13,isEnabled);
          Can_Send_uint8(0x04,0x13,isEnabled);
          Can_Send_uint8(0x05,0x13,isEnabled);
          Can_Send_uint8(0x02,0x13,isEnabled);
      }
			Can_Send_float(1,0x14,boardConfig[0].target_angle);
      
//      for (int j = 0; j < 6; j++)
//      {
//        boardConfig[j].target_angle=*((float*) (ptr + 4 * j + 1));
//      }
      User_Usb_Finish=0;
    }


    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_screen_task */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
extern uint8_t gImage_1[4][43200];
extern uint8_t gImage_2[4][43200];

extern bool Screen_isBusy;

extern BoardConfig_t boardConfig[6];
extern struct UsbBuffer_t usbBuffer;

/* USER CODE END Header_screen_task */
void screen_task(void const * argument)
{
  /* USER CODE BEGIN screen_task */
  static int p=0;
  /* Infinite loop */
  for(;;)
  {

//		if(cnt==0)
//		{
//			for (int p = 0; p < 4; p++)
//			{
//        while (Screen_isBusy);
//			if (p == 0)
//					Screen_WriteFrameBuffer(gImage_1[0],43200,0);
//			else
//					Screen_WriteFrameBuffer(gImage_1[p],43200, true);
//			}
//			cnt=2;
//		}
//		else if(cnt==1){
//			for (int p = 0; p < 4; p++)
//			{
//        while (Screen_isBusy);
//			if (p == 0)
//					Screen_WriteFrameBuffer(gImage_2[0],43200,0);
//			else
//					Screen_WriteFrameBuffer(gImage_2[p],43200, true);
//			}
//			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
//			cnt=2;
//		}
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		for (int p = 0; p < 4; p++)
		{
        // send joint angles
        
        for (int j = 0; j < 6; j++)
            for (int i = 0; i < 4; i++)
            {
                unsigned char* b = (unsigned char*) &(boardConfig[j].actual_angle);
                usbBuffer.extraDataTx[j * 4 + i + 1] = *(b + i);

            }
				SendUsbPacket(usbBuffer.extraDataTx, 32);

				ReceiveUsbPacketUntilSizeIs(224); // last packet is 224bytes
        User_Usb_Finish=1;

        
        if(Screen_isBusy==0)
        {
          if (p == 0)
              Screen_WriteFrameBuffer(GetLcdBufferPtr(),
                                            60 * 240 * 3,0);
          else
              Screen_WriteFrameBuffer(GetLcdBufferPtr(),
                                            60 * 240 * 3, true);
        }

		}
		//Can_Send_uint8(1,0x13,cnt12);
		//Can_Send_float(1,0x14,cnt026);
    osDelay(1);
  }
  /* USER CODE END screen_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */











