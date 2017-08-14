

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



/* The interrupt number to use for the software interrupt generation.  This
could be any unused number.  In this case the first chip level (non system)
interrupt is used, which happens to be the watchdog on the LPC1768. */
#define mainSW_INTERRUPT_ID		( ( IRQn_Type ) 0 )

/* Macro to force an interrupt. */
#define mainTRIGGER_INTERRUPT()	NVIC_SetPendingIRQ( mainSW_INTERRUPT_ID )

/* Macro to clear the same interrupt. */
#define mainCLEAR_INTERRUPT()	NVIC_ClearPendingIRQ( mainSW_INTERRUPT_ID )

/* The priority of the software interrupt.  The interrupt service routine uses
an (interrupt safe) FreeRTOS API function, so the priority of the interrupt must
be equal to or lower than the priority set by
configMAX_SYSCALL_INTERRUPT_PRIORITY - remembering that on the Cortex M3 high
numeric values represent low priority values, which can be confusing as it is
counter intuitive. */
#define mainSOFTWARE_INTERRUPT_PRIORITY 		( 5 )


xSemaphoreHandle xBinarySemaphore;

void vPeriodicTask(void *pvParameters)
{

    for (;;) {
    	vTaskDelay(500 / portTICK_RATE_MS);

    	vPrintString("Periodic task - About to generate an interrupt.\n");
    	mainTRIGGER_INTERRUPT();
    	vPrintString("Periodic task - Interrupt generated.\n\n");
    }
}

void vHandlerTask(void *pvParameters)
{
	xSemaphoreTake(xBinarySemaphore, 0);

	for (;;) {
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
		vPrintString("Handler task - Processing event.\n");
	}
}

void DMA_IRQHandler(void) {
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);

	mainCLEAR_INTERRUPT();

	// never call taskYIELD() form ISR!
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

static void prvSetupSoftwareInterrupt()
{
	/* The interrupt service routine uses an (interrupt safe) FreeRTOS API
	function so the interrupt priority must be at or below the priority defined
	by configSYSCALL_INTERRUPT_PRIORITY. */
	NVIC_SetPriority( mainSW_INTERRUPT_ID, mainSOFTWARE_INTERRUPT_PRIORITY );

	/* Enable the interrupt. */
	NVIC_EnableIRQ( mainSW_INTERRUPT_ID );
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

  vSemaphoreCreateBinary(xBinarySemaphore);

  if (xBinarySemaphore != NULL) {

	  prvSetupSoftwareInterrupt();

	  xTaskCreate(vHandlerTask,  "Handler",  40, NULL, 3, NULL);
	  xTaskCreate(vPeriodicTask, "Periodic", 40, NULL, 1, NULL);
	  vTaskStartScheduler();

  }
  else {
	  while(1) {/* this should not happen! */};
  }

  return 0;
}
