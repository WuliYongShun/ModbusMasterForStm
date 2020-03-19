/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "led.h"
#include "key.h"
#include <stdio.h>
#include <string.h>

#include "ModbusMaster.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t KeyStatus;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */


/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask1_AppHandle;
osThreadId mbMasterServiceHandle;
osThreadId mbMasterAPPTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Task1_App(void const * argument);
void ModbusRtuMasterTask(void const * argument);
void ModbusRtuMasterAPPTask(void const * argument);

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
	Led_Init();
	KeyInit();
       
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

  /* definition and creation of myTask1_App */
  osThreadDef(myTask1_App, Task1_App, osPriorityLow, 0, 128);
  myTask1_AppHandle = osThreadCreate(osThread(myTask1_App), NULL);

  /* definition and creation of mbMasterService */
  osThreadDef(mbMasterService, ModbusRtuMasterTask, osPriorityHigh, 0, 256);
  mbMasterServiceHandle = osThreadCreate(osThread(mbMasterService), NULL);

  /* definition and creation of mbMasterAPPTask */
  osThreadDef(mbMasterAPPTask, ModbusRtuMasterAPPTask, osPriorityNormal, 0, 128);
  mbMasterAPPTaskHandle = osThreadCreate(osThread(mbMasterAPPTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */

  /* Infinite loop */
  for(;;)
  {

    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Task1_App */
/**
* @brief Function implementing the myTask1_App thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task1_App */
void Task1_App(void const * argument)
{
  /* USER CODE BEGIN Task1_App */
  /* Infinite loop */
  for(;;)
  {
	  KeyStatus = ReadKeyStatus();

		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    osDelay(200);
  }
  /* USER CODE END Task1_App */
}

/* USER CODE BEGIN Header_ModbusRtuMasterTask */
/**
* @brief Function implementing the mbMasterService thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ModbusRtuMasterTask */
void ModbusRtuMasterTask(void const * argument)
{
  /* USER CODE BEGIN ModbusRtuMasterTask */
	uint8_t status = 0;
	Modbus_RegMap( );
  /* Infinite loop */
  for(;;)
  {
		if( KeyStatus == OnceKeyDown )
		{
//			RS485_TX_Service( );
			modbus_rtu( );
		}
		else if( KeyStatus == ContiousKeyDown )
		{
			break;
		}
			
    osDelay( 50 );
  }
  /* USER CODE END ModbusRtuMasterTask */
}

/* USER CODE BEGIN Header_ModbusRtuMasterAPPTask */
/**
* @brief Function implementing the mbMasterAPPTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ModbusRtuMasterAPPTask */
void ModbusRtuMasterAPPTask(void const * argument)
{
  /* USER CODE BEGIN ModbusRtuMasterAPPTask */


  /* Infinite loop */
  for(;;)
  {

	  HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		

    osDelay(100);
  }
  /* USER CODE END ModbusRtuMasterAPPTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
