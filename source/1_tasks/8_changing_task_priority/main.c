

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

static xTaskHandle xTask2Handle;

void vTask1(void *pvParameters)
{
    unsigned portBASE_TYPE uxPriority;

    uxPriority = uxTaskPriorityGet(NULL);

    for (;;)
    {
        // Print task name: not blocking or delaying
        vPrintString("Task 1 is running\n");

        vPrintString("About to raise the Task 2 priority\n");
        vTaskPrioritySet(xTask2Handle, (uxPriority + 1));

    }
}


void vTask2(void *pvParameters)
{
    unsigned portBASE_TYPE uxPriority;

    uxPriority = uxTaskPriorityGet(NULL);

    for (;;)
    {
        // Print task name: not blocking or delaying
        vPrintString("Task 2 is running\n");

        vPrintString("About to lower the Task 2 priority\n");
        vTaskPrioritySet(NULL, (uxPriority - 2));

    }
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
              2,        // priority
              NULL);    // task handle (not used)

  xTaskCreate(vTask2,   // pointer to the task function
              "Task 2", // task name
              50,      // stack size in words
			  NULL,     // stack parameter
              1,        // priority
              &xTask2Handle);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
