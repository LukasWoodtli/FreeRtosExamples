

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

void setupSWOForPrint(void)

{

  /* Enable GPIO clock. */
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;

  /* Enable Serial wire output pin */
  GPIO->ROUTE |= GPIO_ROUTE_SWOPEN;


#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_LEOPARD_FAMILY) || defined(_EFM32_WONDER_FAMILY)

  /* Set location 0 */
  GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | GPIO_ROUTE_SWLOCATION_LOC0;

  /* Enable output on pin - GPIO Port F, Pin 2 */
  GPIO->P[5].MODEL &= ~(_GPIO_P_MODEL_MODE2_MASK);
  GPIO->P[5].MODEL |= GPIO_P_MODEL_MODE2_PUSHPULL;
#else
  /* Set location 1 */
  GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) |GPIO_ROUTE_SWLOCATION_LOC1;

  /* Enable output on pin */
  GPIO->P[2].MODEH &= ~(_GPIO_P_MODEH_MODE15_MASK);
  GPIO->P[2].MODEH |= GPIO_P_MODEH_MODE15_PUSHPULL;
#endif

  /* Enable debug clock AUXHFRCO */
  CMU->OSCENCMD = CMU_OSCENCMD_AUXHFRCOEN;

  /* Wait until clock is ready */
  while (!(CMU->STATUS & CMU_STATUS_AUXHFRCORDY));

  /* Enable trace in core debug */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  ITM->LAR  = 0xC5ACCE55;
  ITM->TER  = 0x0;
  ITM->TCR  = 0x0;
  TPI->SPPR = 2;
  TPI->ACPR = 0xf;
  ITM->TPR  = 0x0;
  DWT->CTRL = 0x400003FE;
  ITM->TCR  = 0x0001000D;
  TPI->FFCR = 0x00000100;
  ITM->TER  = 0x1;
}

void vPrintString(char const * const str) {
    char const * i = str;
    
    while (*i != '\0') {
        ITM_SendChar(*i);
        i++;
    }
}


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

void vTask3(void *pvParameters);

void vTask2(void *pvParameters)
{
    const char *pcTaskName = "Task 2 is running\n";
    volatile unsigned long ul;
    
    // it's also possible to create tasks in other tasks
    xTaskCreate(vTask3,   // pointer to the task function
                    "Task 3", // task name
                    40,      // stack size in words
                    NULL,     // stack parameter (not used here)
                    1,        // priority
                    NULL);

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

void vTask3(void *pvParameters)
{
    const char *pcTaskName = "Task 3 is running\n";
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


  setupSWOForPrint();

  xTaskCreate(vTask1,   // pointer to the task function
              "Task 1", // task name
              40,      // stack size in words
              NULL,     // stack parameter (not used here)
              1,        // priority
              NULL);    // task handle (not used)

    xTaskCreate(vTask2,   // pointer to the task function
                "Task 2", // task name
                40,      // stack size in words
                NULL,     // stack parameter (not used here)
                1,        // priority
                NULL);
    
    
  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;
}
