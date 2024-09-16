/// \file		freertos_hello_world.c
///
/// \brief	
///
/// \author		Uriel Abe Contardi (urielcontardi@hotmail.com)
/// \date		16-09-2024
///
/// \version	1.0
///
/// \note		Revisions:
/// 			16-09-2024 <urielcontardi@hotmail.com>
/// 			First revision.
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                               INCLUDES                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

/* Xilinx includes. */
#include "xil_printf.h"
#include "xgpiops.h"
#include "xparameters.h"

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                           DEFINES AND MACROS                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
// External PS->PL Pin Offset
#define EMIO_0 54
#define BUTTON_GPIO 20

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                      LOCAL TYPEDEFS AND STRUCTURES                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                        LOCAL FUNCTIONS PROTOTYPES                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
static void blinkyTask( void *pvParameters );
static void buttonTask( void *pvParameters );
SemaphoreHandle_t xSemaphore;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                      STATIC VARIABLES AND CONSTANTS                      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

static TaskHandle_t blinkyTaskHandle;
static TaskHandle_t buttonTaskHandle;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                            EXPORTED FUNCTIONS                            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
int main( void )
{
	/* Create the tasks as described in the comments at the top of this file. */
	xTaskCreate( 	blinkyTask, 					/* The function that implements the task. */
					( const char * ) "blinkyTask", 	/* Text name for the task, provided to assist debugging only. */
					configMINIMAL_STACK_SIZE, 		/* The stack allocated to the task. */
					NULL, 							/* The task parameter is not used, so set to NULL. */
					tskIDLE_PRIORITY,				/* The task runs at the idle priority. */
					&blinkyTaskHandle );

	xTaskCreate( buttonTask,
				 ( const char * ) "buttonTask",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 tskIDLE_PRIORITY + 1,
				 &buttonTaskHandle );

	/* Create Semaphore */
	xSemaphore = xSemaphoreCreateBinary();
	
	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for( ;; );
}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                              LOCAL FUNCTIONS                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

static void blinkyTask( void *pvParameters )
{
	/* Configure LED Pin */
	int actualValue = 0;
	XGpioPs greenLedGpio;
	XGpioPs_Config *greeenLedCfg = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);

	/* Initialize the greenLedGpio driver. */
	XGpioPs_CfgInitialize(&greenLedGpio, greeenLedCfg, greeenLedCfg->BaseAddr);
    XGpioPs_SetDirectionPin(&greenLedGpio, EMIO_0, 1);
    XGpioPs_SetOutputEnablePin(&greenLedGpio, EMIO_0, 1);

	for( ;; )
	{
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
		{
			actualValue = !actualValue;
    		XGpioPs_WritePin(&greenLedGpio, EMIO_0, actualValue);
		}	
	}
}

static void buttonTask( void *pvParameters )
{
	/* Configure Button Pin */
	XGpioPs btnGpio;
	XGpioPs_Config *btnCfg = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);

	/* Initialize the btnGpio driver. */
	XGpioPs_CfgInitialize(&btnGpio, btnCfg, btnCfg->BaseAddr);
    XGpioPs_SetDirectionPin(&btnGpio, BUTTON_GPIO, 0);

	uint32_t currentPinState = 0;

	for( ;; )
	{
    	if ( XGpioPs_ReadPin(&btnGpio, BUTTON_GPIO) == 1) 
		{
			// Binary Semaphore
			xSemaphoreGive(xSemaphore);

    	    // Debounce Delay
    	    vTaskDelay(pdMS_TO_TICKS(300));
    	}
	}
}