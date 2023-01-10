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


#include "bare_metal_timer/timer.h"

     /* ----------------- APPLICATION GLOBALS ------------------ */

/************************ ADDED *****************************/
const unsigned correct_overflows = 0;
unsigned systick_overflows = 0;
unsigned timer_overflows = 0;
const CPU_REG32 correct_startup_time_w_loop = 0x0000B1DD;
const CPU_REG32 correct_timer_startup_time_w_loop = 0x00000AB4;

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
	
		SystemInit();	 					/*NEEDED - initialize the clock - choosing clk src setting prescaler etc*/
		init_timer1(0xFFFFFFFF);
		enable_timer1();
	
		BSP_IntInit();					/*NEEDED - initialize interrupt - copies vector table from Flash to RAM*/
		BSP_Start(); 						/*NEEDED - initialize kernel system tick timer - this is what we need, it initializes the systick timer */
		
		/************************ ADDED *****************************/
		CPU_REG32 initial_time = CPU_REG_NVIC_ST_CURRENT; //read current value of the systick counter
		//Potential updates for better precision: increase reload value and decrease prescaler

		CPU_REG32 timer_initial_time = read_timer1();
		/************************************************************/
	
		CPU_IntDis(); 					/*disable interrupt*/
	
    CPU_Init();   					/*init cpu - name and timestamp init*/
    Mem_Init();							/*Memory initialization*/
    OSInit(&err);						/* Initialize "uC/OS-III, The Real-Time Kernel"         */
		
	
		/************************ ADDED *****************************/
		//for(int i = 0; i < 10; i++){}; 										//loop to see if startup time changes with this	
			
		CPU_SR_ALLOC(); 																	//needed for critical section
		CPU_CRITICAL_ENTER(); 														//disabling interrupts for critical section process
		CPU_REG32 startup_time = CPU_REG_NVIC_ST_CURRENT;
		CPU_REG32 timer_startup_time = read_timer1();	
		CPU_CRITICAL_EXIT(); 															//exiting critical section
			
		//this only works if the CPU_CFG_TS_TMR_EN is enabled
	  //CPU_TS32         timestamp;
    //CPU_INT64U       usecs;
    //timestamp = CPU_TS_Get32();           /* Read current timestamp counter value.      */
    //usecs = CPU_TS32_to_uSec(timestamp);  /* Convert timestamp counter to microseconds. */		

		/************************************************************/
	
			
    /* Create the start task                                */
    
			
		/************************ MODIFIED *****************************/			
		if(startup_time != correct_startup_time_w_loop || systick_overflows != correct_overflows 
			 || timer_startup_time != correct_timer_startup_time_w_loop){
			while(DEF_ON){};
		}
		else {
			OSStart(&err);      /* Start multitasking (i.e. give control to uC/OS-III). */
			//while(DEF_ON){			/* Should Never Get Here	*/
			//};
		}
}






