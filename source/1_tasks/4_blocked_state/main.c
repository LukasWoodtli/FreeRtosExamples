

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

#define mainDELAY_LOOP_COUNT		( 0xfffff )

void vTask(void *pvParameters)
{
    const char *pcTaskName;
    
    pcTaskName = (char*)pvParameters;

    for (;;)
    {
        // Print task name
        vPrintString(pcTaskName);
        
        vTaskDelay(250 / portTICK_RATE_MS);
    }
}

static char const * const pcTextForTask1 = "Task 1 is running\n";
static char const * const pcTextForTask2 = "Task 2 is running\n";

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

  xTaskCreate(vTask,   // pointer to the task function
              "Task 1", // task name
              40,      // stack size in words
			  (void*)pcTextForTask1,     // stack parameter
              1,        // priority
              NULL);    // task handle (not used)

    xTaskCreate(vTask,   // pointer to the task function
                "Task 2", // task name
                40,      // stack size in words
				(void*)pcTextForTask2,     // stack parameter
                2,        // priority
                NULL);
    
    
  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
