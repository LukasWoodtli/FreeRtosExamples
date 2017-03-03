

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#include "basic_io.h"

#include "em_chip.h"
#include "bsp.h"
#include "bsp_trace.h"

#include "sleep.h"


#define mainDELAY_LOOP_COUNT		( 0xfffff )

void vTask1(void *pvParameters)
{
    const char *pcTaskName = "Task 1 is running\n";
    volatile unsigned long ul;
    
    for (;;)
    {
        // Print task name
        vPrintString(pcTaskName);
        
        // simple delay
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {
            // just loop for delay
        }
    }
}


void vTask2(void *pvParameters)
{
    const char *pcTaskName = "Task 2 is running\n";
    volatile unsigned long ul;
    
    for (;;)
    {
        // Print task name
        vPrintString(pcTaskName);
        
        // simple delay
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {
            // just loop for delay
        }
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


    
  xTaskCreate(vTask1,   // pointer to the task function
              "Task 1", // task name
              240,      // stack size in words
              NULL,     // stack parameter (not used here)
              1,        // priority
              NULL);    // task handle (not used)

    xTaskCreate(vTask2,   // pointer to the task function
                "Task 2", // task name
                240,      // stack size in words
                NULL,     // stack parameter (not used here)
                1,        // priority
                NULL);
    
    
  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
