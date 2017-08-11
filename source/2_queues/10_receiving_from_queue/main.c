

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


void vPrintNumber(int i) {
	switch (i) {
	case 0: vPrintString("0"); break;
	case 1: vPrintString("1"); break;
	case 2: vPrintString("2"); break;
	case 3: vPrintString("3"); break;
	case 4: vPrintString("4"); break;
	case 5: vPrintString("5"); break;
	case 6: vPrintString("6"); break;
	case 7: vPrintString("7"); break;
	case 8: vPrintString("8"); break;
	case 9: vPrintString("9"); break;
	default: vPrintString("UNKNOWN"); break;
	}
}

static xQueueHandle xQueue;

void vSenderTask(void *pvParameters)
{
	int lValueToSend;
	portBASE_TYPE xStatus;
	lValueToSend = (int)pvParameters;
    
    for (;;)
    {
    	xStatus = xQueueSendToBack(xQueue, &lValueToSend, 0);

    	if (xStatus != pdPASS) {
    		vPrintString("Could not send to the queue!\n");
    	}

    	taskYIELD();
    }
}

void vReceiverTask(void *pvParameters)
{
	int lReceivedValue;
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;

	for (;;) {
		if (uxQueueMessagesWaiting(xQueue) != 0) {
			vPrintString("Queue should have been empty!\n");
		}

		xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);

		if (xStatus == pdPASS) {
			vPrintString("Received = ");
			vPrintNumber(lReceivedValue);
			vPrintString("\n");
		}
		else {
			vPrintString("Could not receive from the queue!\n");
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


  setupSWOForPrint();


  xQueue = xQueueCreate(5, sizeof(int));

  if (xQueue != NULL) {

	  xTaskCreate(vSenderTask,  "Sender 1", 40, (void*)1, 1, NULL);
	  xTaskCreate(vSenderTask,  "Sender 2", 40, (void*)2, 1, NULL);

	  xTaskCreate(vReceiverTask,  "Receiver", 40, NULL, 2, NULL);

	  /*Start FreeRTOS Scheduler*/
	  vTaskStartScheduler();

  }
  else {
	  while(1) {/* this should not happen! */};
  }

  return 0;
}
