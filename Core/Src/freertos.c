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
#include "lamp.h"
#include "chassis.h"
#include "message.h"
#include "tof.h"
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
osThreadId lampTaskHandle;
osThreadId chassisTaskHandle;
osThreadId messageTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLampTask(void const * argument);
void StartChassisTask(void const * argument);
void StartMessageTask(void const * argument);

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
  /* definition and creation of lampTask */
  osThreadDef(lampTask, StartLampTask, osPriorityRealtime, 0, 256);
  lampTaskHandle = osThreadCreate(osThread(lampTask), NULL);

  /* definition and creation of chassisTask */
  osThreadDef(chassisTask, StartChassisTask, osPriorityRealtime, 0, 256);
  chassisTaskHandle = osThreadCreate(osThread(chassisTask), NULL);

  /* definition and creation of messageTask */
  osThreadDef(messageTask, StartMessageTask, osPriorityBelowNormal, 0, 128);
  messageTaskHandle = osThreadCreate(osThread(messageTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartLampTask */
/**
  * @brief  Function implementing the lampTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLampTask */
void StartLampTask(void const * argument)
{
  /* USER CODE BEGIN StartLampTask */
  /* Infinite loop */
  for(;;)
  {
	  LAMP_process();
    osDelay(1);
  }
  /* USER CODE END StartLampTask */
}

/* USER CODE BEGIN Header_StartChassisTask */
/**
* @brief Function implementing the chassisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartChassisTask */
void StartChassisTask(void const * argument)
{
  /* USER CODE BEGIN StartChassisTask */
	CHASSIS_pidInit();
  /* Infinite loop */
  for(;;)
  {
	  CHASSIS_process();
	  CHASSIS_pwmTransimt();
    osDelay(1);
  }
  /* USER CODE END StartChassisTask */
}

/* USER CODE BEGIN Header_StartMessageTask */
/**
* @brief Function implementing the messageTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMessageTask */
void StartMessageTask(void const * argument)
{
  /* USER CODE BEGIN StartMessageTask */
	LAMP_T *lamp = getLampStruct();
	CHASSIS_T *chassis = getChassisStruct();
  /* Infinite loop */
  for(;;)
  {
	  MESSAGE_dataProcess();
	  LAMP_test();
	  MESSAGE_upperComputerControl(uart_buf,lamp,chassis);
    osDelay(1);
  }
  /* USER CODE END StartMessageTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
