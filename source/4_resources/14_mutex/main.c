#include <stdlib.h>

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"


#include "em_chip.h"
#include "em_device.h"
#include "bsp.h"
#include "bsp_trace.h"


#include "core_cm3.h"

#include "sleep.h"

#include "print.h"


static xSemaphoreHandle xMutex;

static void prvNewPrintString(const char* pcString) {

	xSemaphoreTake(xMutex, portMAX_DELAY);
	vPrintString(pcString);
	xSemaphoreGive(xMutex);
}

static void prvPrintTask(void *pvParameters) {
	char *pcStringToPrint;
	pcStringToPrint = (char*)pvParameters;

	for (;;) {
		prvNewPrintString(pcStringToPrint);

		// Just delay with random time
		// Don't use rand() in secure applications. It's not reentrant!
		vTaskDelay(rand() & 0x1F);
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

  xMutex = xSemaphoreCreateMutex();

  srand(0x42);

  if (xMutex != NULL) {

	  xTaskCreate(prvPrintTask, "Print1", 40,
			  "Task 1 ******************************\n", 1, NULL);
	  xTaskCreate(prvPrintTask, "Print2", 40,
			  "Task 2 ==============================\n", 2, NULL);

	  vTaskStartScheduler();
  }

  return 0;
}
