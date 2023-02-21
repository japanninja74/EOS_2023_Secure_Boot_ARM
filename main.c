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



//Defition of the Task Control Blocks for the tasks
static OS_TCB				START_TSK_TCB;
static OS_TCB				LED_TASK_TCB;


// Definition of the Stacks for the START TASK
static  CPU_STK_SIZE  START_TSK_STACK[START_CFG_TASK_STK_SIZE];

// Definition of the Stacks for the LED TASK
static  CPU_STK_SIZE  LED_TASK_STACK[LED_CFG_TASK_STK_SIZE];


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void START_TSK(void *p_arg);
static void LED_TASK(void * p_arg);

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
	
		CPU_IntDis(); 					/*disable interrupt*/

    CPU_Init();   					/*init cpu - name and timestamp init*/

    Mem_Init();							/*Memory initialization*/

    OSInit(&err);						/* Initialize "uC/OS-III, The Real-Time Kernel"         */
		
    OSTaskCreate((OS_TCB     *)&START_TSK_TCB,               /* Create the start task                                */
                 (CPU_CHAR   *)"START_TASK",
                 (OS_TASK_PTR ) START_TSK,
                 (void       *) 0,
                 (OS_PRIO     ) START_CFG_TASK_PRIO,
                 (CPU_STK    *)&START_TSK_STACK[0],
                 (CPU_STK     )(START_CFG_TASK_STK_SIZE / 10u),
                 (CPU_STK_SIZE) START_CFG_TASK_STK_SIZE,
                 (OS_MSG_QTY  ) 0,
                 (OS_TICK     ) 0,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);		
			
		OSStart(&err);      /* Start multitasking (i.e. give control to uC/OS-III). */
		
		while(DEF_ON){		/* Should Never Get Here	*/
		};
}


static void START_TSK (void *p_arg) {
		
	OS_ERR	err;
	LED_init(); 
	
	//Creation of the LED task
  OSTaskCreate((OS_TCB     *)&LED_TASK_TCB,               /* Create the start task                                */
               (CPU_CHAR   *)"LED_TASK",
               (OS_TASK_PTR ) LED_TASK,
               (void       *) 0,
               (OS_PRIO     ) LED_CFG_TASK_PRIO,
               (CPU_STK    *)&LED_TASK_STACK[0],
               (CPU_STK     )(LED_CFG_TASK_STK_SIZE / 10u),
               (CPU_STK_SIZE) LED_CFG_TASK_STK_SIZE,
               (OS_MSG_QTY  ) 0,
							 (OS_TICK     ) 0,
               (void       *) 0,
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               (OS_ERR     *)&err);			

}

static void LED_TASK(void * p_args){
	LED_Out(0xA);
}





