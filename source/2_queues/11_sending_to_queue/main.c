

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


typedef struct {
	unsigned char ucValue;
	unsigned char ucSource;
} xData;

#define mainSENDER_1 0
#define mainSENDER_2 1

static const xData xStructsToSend[2] = {
		{1, mainSENDER_1},
		{2, mainSENDER_2}
};

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
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    
    for (;;)
    {
    	xStatus = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);

    	if (xStatus != pdPASS) {
    		vPrintString("Could not send to the queue!\n");
    	}

    	taskYIELD();
    }
}

void vReceiverTask(void *pvParameters)
{
	xData xReceivedStructure;
	portBASE_TYPE xStatus;


	for (;;) {
		if (uxQueueMessagesWaiting(xQueue) != 3) {
			vPrintString("Queue should have been full!\n");
		}

		xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);

		if (xStatus == pdPASS) {
			if (xReceivedStructure.ucSource == mainSENDER_1) {
				vPrintString("Received From Sender 1 = ");
				vPrintNumber(xReceivedStructure.ucValue);
				vPrintString("\n");
			}
			else {
				vPrintString("Received From Sender 2 = ");
				vPrintNumber(xReceivedStructure.ucValue);
				vPrintString("\n");
			}
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


  xQueue = xQueueCreate(3, sizeof(xData));

  if (xQueue != NULL) {

	  xTaskCreate(vSenderTask,  "Sender 1", 40, (void*)&(xStructsToSend[0]), 2, NULL);
	  xTaskCreate(vSenderTask,  "Sender 2", 40, (void*)&(xStructsToSend[1]), 2, NULL);

	  xTaskCreate(vReceiverTask,  "Receiver", 40, NULL, 1, NULL);

	  /*Start FreeRTOS Scheduler*/
	  vTaskStartScheduler();

  }
  else {
	  while(1) {/* this should not happen! */};
  }

  return 0;
}
