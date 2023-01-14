/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: 
 * Note(s):
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "core_cm3.h"
#include "RTE_Device.h"                 // Keil::Device:Startup
#include "includes.h"
#include "BSP.h"


#include "secure_boot/secure_boot.h"

/* ----------------- APPLICATION GLOBALS ------------------ */

CPU_REG32 systick_times[6];
CPU_REG32 timer1_times[6];
CPU_REG32 DWT_times[6];

volatile uint32_t SP_values[6];
volatile uint32_t PC_values[6];


unsigned timer_overflows = 0;
unsigned systick_overflows = 0;
//TODO: add overflow arrays?

const CPU_REG32 correct_systick_times[6] = {0x00010413, 0x0001038F, 0x000101B9, 0x00010109, 0x0000B00B, 0x0000AF8F};
const CPU_REG32 correct_timer1_times[6] = {0x00000005, 0x00000016, 0x00000050, 0x00000066, 0x00000A86, 0x00000A96};
const CPU_REG32 correct_DWT_times[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

volatile const uint32_t correct_SP_values[6] = {0x2007F040, 0x2007F040, 0x2007F040, 0x2007F040, 0x2007F040, 0x2007F040};
volatile const uint32_t correct_PC_values[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/**********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This the main standard entry point.
*
* Note(s)     : none.
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;
	
		SystemInit();	 					/* Initialize the clock - choosing clk source, setting prescaler etc */
		BSP_IntInit();					/* Initialize interrupts - copies vector table from Flash to RAM */
		BSP_Start(); 						/* Initialize kernel system tick timer - also used for the secure_boot */
		init_timer1(0xFFFFFFFF);
		enable_timer1();
	
		read_current_values();	//read 1
	
		CPU_IntDis(); 					/*disable interrupt*/

		read_current_values();	//read 2

    CPU_Init();   					/*init cpu - name and timestamp init*/
		
		read_current_values();	// read 3

    Mem_Init();							/*Memory initialization*/
		
		read_current_values();	// read 4

    OSInit(&err);						/* Initialize "uC/OS-III, The Real-Time Kernel"         */
		
		read_current_values();	// read 5
    /* Create the start task */
    
		//TODO: create start task
		
		read_current_values(); // read 6
			
		/* checking if the source code is the original and starting the OS if it is, 
		   otherwise it stays in an infinite loop */
		if(0 == check_if_startup_was_correct()){
			while(DEF_ON){};
		}
		else {
			OSStart(&err);      /* Start multitasking (i.e. give control to uC/OS-III). */
			
			while(DEF_ON){		/* Should Never Get Here	*/
			};
		}
}






