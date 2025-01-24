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
#include <string.h>
#include "screen.h"
#include "can.h"
#include "image.h"
#include "User_usb.h"
#include "configurations.h"
#include "mpu6050.h"
#include "usart.h"
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
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void screen_task(void const * argument);
void StartTask03(void const * argument);

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

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityAboveNormal, 0, 256);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
bool User_Usb_Finish;
int cnt12=5;
uint8_t isEnabled=0;
uint8_t can_task_static=0;
uint8_t can_task_enable_static=0;


unsigned char t,CleanTime;
uint32_t TimeCounter;
extern void i2c_CfgGpio(void);
short Accel[3];
short Gyro [3];
short Temp;
float AccelData[3];//单位mg
float GyroData[3];//单位mdps


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

		
		MPU6050ReadGyro(Gyro);	 
		for( int i=0;i<3;i++)
		{

		if(Gyro[i]>=0)
		{

			GyroData[i]=Gyro[i]*2000/32768;
		}else
		{

			GyroData[i]=-(-Gyro[i]+1)*2000/32768;
		
		}
	 }	
    if(User_Usb_Finish==1)
    {
      // get joint angles
      uint8_t* ptr = GetExtraDataRxPtr();
			memcpy(&boardConfig[0].target_angle, ptr + 1, sizeof(float));
			memcpy(&boardConfig[1].target_angle, ptr + 5, sizeof(float));
			memcpy(&boardConfig[2].target_angle, ptr + 9, sizeof(float));
			memcpy(&boardConfig[3].target_angle, ptr + 13, sizeof(float));
			memcpy(&boardConfig[4].target_angle, ptr + 17, sizeof(float));
			memcpy(&boardConfig[5].target_angle, ptr + 21, sizeof(float));

      if ((isEnabled != (bool) ptr[0]))
      {
				if(can_task_enable_static==0)
				{
          Can_Send_uint8(0x01,0x13,ptr[0]);
          Can_Send_uint8(0x06,0x13,ptr[0]);
          Can_Send_uint8(0x03,0x13,ptr[0]);
					can_task_enable_static=1;
				}
				else if(can_task_enable_static==1)
				{
          Can_Send_uint8(0x04,0x13,ptr[0]);
          Can_Send_uint8(0x05,0x13,ptr[0]);
          Can_Send_uint8(0x02,0x13,ptr[0]);
					isEnabled = ptr[0];
					can_task_enable_static=0;
				}
      }
			else
			{
			
			
			}
			if(can_task_static==0)
			{
				Can_Send_float(1,0x14,boardConfig[0].target_angle);
				Can_Send_float(2,0x14,boardConfig[1].target_angle);
				Can_Send_float(3,0x14,boardConfig[2].target_angle);
				can_task_static=1;
			}
			else if(can_task_static==1)
			{
				Can_Send_float(4,0x14,boardConfig[3].target_angle);
				Can_Send_float(5,0x14,boardConfig[4].target_angle);
				Can_Send_float(6,0x14,boardConfig[5].target_angle);
				can_task_static=0;
			}
//      for (int j = 0; j < 6; j++)
//      {
//        boardConfig[j].target_angle=*((float*) (ptr + 4 * j + 1));
//      }
      User_Usb_Finish=0;
    }


    osDelay(20);
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
		if(cnt12==5)
		{
			screen_init(2);
			Screen_SetWindow(0, 239, 0, 239);
			cnt12=0;
		}
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

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
extern uint8_t get_motor_date_id;
extern uint8_t get_motor_date_flag;
extern uint8_t get_vofa_flag;
extern uint8_t get_vofa_id;
uint8_t motor_date_send[16];
extern uint8_t set_motor_flag;
extern uint8_t set_motor_id;
extern uint8_t UART1_Rx_Buf[16];
int cnt1520=0;
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
		
		if(get_motor_date_flag!=0)
		{
			//cnt1520++;
			switch (get_motor_date_flag)
			{
				case 1:
					Can_Get_uint8(get_motor_date_id,0x09,0);
					get_motor_date_flag=2;
				HAL_Delay(10);
				break;
				case 2:
					Can_Get_uint8(get_motor_date_id,10,0);
				get_motor_date_flag=3;
				HAL_Delay(10);
				break;
				case 3:
					Can_Get_uint8(get_motor_date_id,11,0);
				get_motor_date_flag=4;
				HAL_Delay(10);
				case 4:
					Can_Get_uint8(get_motor_date_id,12,0);
				get_motor_date_flag=5;
				HAL_Delay(10);
				break;
				case 5:
					motor_date_send[0]=0x81;
					motor_date_send[15]=0x7F;
				
					motor_date_send[2]=get_motor_date_id;
					uint8_t* pFloat;
					float dceKp = boardConfig[(get_motor_date_id-1)].dceKp;
					memcpy(&motor_date_send[3], &dceKp, sizeof(float));
				
					float dceKi = boardConfig[(get_motor_date_id-1)].dceKi;
					memcpy(&motor_date_send[7], &dceKi, sizeof(float));
		
					float dceKd = boardConfig[(get_motor_date_id-1)].dceKd;
					memcpy(&motor_date_send[11], &dceKd, sizeof(float));
								cnt1520++;
					//HAL_UART_Transmit_DMA(&huart1,motor_date_send,sizeof(motor_date_send));
					HAL_UART_Transmit(&huart1,motor_date_send,16u,300);
				
//										uint8_t tail_3=0x00;
//		HAL_UART_Transmit(&huart1,(uint8_t *)&tail_3,1,0x10);

					get_motor_date_flag=0;
				break;
			}
		}
		
		
		
    
		if(get_vofa_flag==1)
		{
				report_SendData(boardConfig[get_vofa_id].actual_angle,boardConfig[get_vofa_id].target_angle);
		}
		
		if(set_motor_flag==1)
		{

			memcpy(&boardConfig[(set_motor_id-1)].set_Kp, &UART1_Rx_Buf[3], sizeof(float));
			memcpy(&boardConfig[(set_motor_id-1)].set_Ki, &UART1_Rx_Buf[7], sizeof(float));
			memcpy(&boardConfig[(set_motor_id-1)].set_Kd, &UART1_Rx_Buf[11], sizeof(float));
			Can_Send_float((set_motor_id),0x09,boardConfig[(set_motor_id-1)].set_Kp);
			HAL_Delay(10);
			Can_Send_float((set_motor_id),0x11,boardConfig[(set_motor_id-1)].set_Ki);
			HAL_Delay(100);
			Can_Send_float((set_motor_id),0x12,boardConfig[(set_motor_id-1)].set_Kd);
			HAL_Delay(10);
			set_motor_flag=2;
		}
		osDelay(50);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

