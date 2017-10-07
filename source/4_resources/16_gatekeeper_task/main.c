#include <stdlib.h>
#include <string.h>

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

#define mainMAX_MSG_LEN 100

static char *pcStringsToPrint[] = {
	"Task 1 *********************************\n",
	"Task 2 =================================\n"
	"Message printed from the tick hook #####\n"
};

xQueueHandle xPrintQueue;

static void prvStdioGatekeeperTask(void* pvParameters) {
	char* pcMessageToPrint;
	static char cBuffer[mainMAX_MSG_LEN];

	for (;;) {
		xQueueReceive(xPrintQueue, &pcMessageToPrint, portMAX_DELAY);
		strncpy(cBuffer, pcMessageToPrint, mainMAX_MSG_LEN);
		vPrintString(cBuffer);
	}
}

static void prvPrintTask(void *pvParameters) {
	int iIndexToString;
	iIndexToString = (int)pvParameters;

	for (;;) {
		xQueueSendToBack(xPrintQueue, &(pcStringsToPrint[iIndexToString]), 0);

		vTaskDelay((rand() & 0x1F));
	}
}

void vApplicationTickHook(void) {
	static int iCount = 0;
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	iCount++;
	if (iCount >= 200) {
		xQueueSendToFrontFromISR(xPrintQueue,
					&(pcStringsToPrint[2]),
					&xHigherPriorityTaskWoken); // not needed
		iCount = 0;
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

  xPrintQueue = xQueueCreate(5, sizeof(char*));

  srand(0x42);

  if (xPrintQueue != NULL) {

	  xTaskCreate(prvPrintTask, "Print1", 40, (void*)0, 1, NULL);
	  xTaskCreate(prvPrintTask, "Print2", 40, (void*)1, 2, NULL);

	  xTaskCreate(prvStdioGatekeeperTask, "Gatekeeper", 40, NULL, 0, NULL);

	  vTaskStartScheduler();
  }

  return 0;
}
