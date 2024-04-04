/// \file		helloworld.c
///
/// \brief		
///
/// \author		Uriel Abe Contardi
/// \date       03-04-2024
///
/// \version    1.0
///
/// \note		Copyright (c) 2024 - All Rights reserved.
/// 
/// \note		Revisions:
///				- 1.0	03-04-2024
///				First revision.

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                               INCLUDES                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "platform.h"
#include "xil_types.h"

// Delay/ Timer
#include "sleep.h"

// GPIO Configuration
#include "xgpiops.h"
#include "xparameters.h"

// Interrupt Configuration
#include "xscugic.h"
#include "xil_exception.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                           DEFINES AND MACROS                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// External PS->PL Pin Offset
#define EMIO_0 54

// Interrupt IRQ_F2P[0:0] ID
#define INTC_INTERRUPT_ID_0 61

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                        LOCAL FUNCTIONS PROTOTYPES                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
static void interruptHandler(void *CallBackRef);
static void _gpioInit(void);
static void _interruptInit(void);

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Variables                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// GPIO Struct Variable
static XGpioPs Gpio;
int actualValue;

// Interrupt Struct Variable
static XScuGic Gic;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              MAIN FUNCTION                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
int main()
{
    init_platform();
    _gpioInit();
    _interruptInit();

    actualValue = 0;

    while(1)
    {
        sleep(1);
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              LOCAL FUNCTIONS                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------
// IRS: Interrupt Routine Service
// ------------------------------------------------------------------
static void interruptHandler(void *CallBackRef)
{
    actualValue = !actualValue;
    XGpioPs_WritePin(&Gpio, EMIO_0, actualValue);
}

static void _gpioInit(void)
{
    XGpioPs_Config *Gpio_Config;

	// Initialize the GPIO driver.
	Gpio_Config = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&Gpio, Gpio_Config, Gpio_Config->BaseAddr);

	// Configure EMIO Pin
    XGpioPs_SetDirectionPin(&Gpio, EMIO_0, 1);
    XGpioPs_SetOutputEnablePin(&Gpio, EMIO_0, 1);
}

static void _interruptInit() 
{

    XScuGic *Gic_ptr = &Gic;
    XScuGic_Config *Gic_Config;

    // Get config for interrupt controller
    Gic_Config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

    // Initialize the interrupt controller driver
    XScuGic_CfgInitialize(Gic_ptr, Gic_Config, Gic_Config->CpuBaseAddress);

    // set the priority of IRQ_F2P[0:0] to 0xA0 (highest 0xF8, lowest 0x00) and a trigger for a rising edge 0x3.
    XScuGic_SetPriorityTriggerType(Gic_ptr, INTC_INTERRUPT_ID_0, 0xA0, 0x3);

    // connect the interrupt service routine isr0 to the interrupt controller
    XScuGic_Connect(Gic_ptr, INTC_INTERRUPT_ID_0, (Xil_ExceptionHandler)interruptHandler, (void *)&Gic);

    // Enable interrupts for IRQ_F2P[0:0]
    XScuGic_Enable(Gic_ptr, INTC_INTERRUPT_ID_0);

    // Initialize the exception table and register the interrupt controller handler with the exception table
    Xil_ExceptionInit();

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, Gic_ptr);

    // enable non-critical exceptions
    Xil_ExceptionEnable();

}
