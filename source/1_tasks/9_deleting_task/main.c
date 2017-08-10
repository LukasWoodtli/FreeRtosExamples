

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#include "em_chip.h"
#include "bsp.h"
#include "bsp_trace.h"

#include "sleep.h"

#include "print.h"

void vTask2(void *pvParameters);

static xTaskHandle xTask2Handle;

void vTask1(void *pvParameters)
{
    const portTickType xDelay100ms = 100 / portTICK_RATE_MS;

    for (;;)
    {
        vPrintString("Task 1 is running\n");

        xTaskCreate(vTask2, "Task2", 40, NULL, 2, &xTask2Handle);

        vTaskDelay(xDelay100ms);
    }
}


void vTask2(void *pvParameters)
{

	vPrintString("Task 2 is running and about to delete itself\n");
	vTaskDelete(xTask2Handle); // could just provide NULL as param to delete self

}


int main(void)
{
  /* Chip errata */
  CHIP_Init();
  /* If first word of user data page is non-zero, enable eA Profiler trace */
  BSP_TraceProfilerSetup();

  /* Initialize LED driver */
  BSP_LedsInit();
  /* Setting state of leds*/
  BSP_LedSet(0);

  /* Initialize SLEEP driver, no calbacks are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif


  setupSWOForPrint();

  xTaskCreate(vTask1,   // pointer to the task function
              "Task 1", // task name
              50,      // stack size in words
			  NULL,     // stack parameter
              1,        // priority
              NULL);    // task handle (not used)

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
