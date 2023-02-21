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



CPU_REG32 systick_times[10];
CPU_REG32 timer1_times[10];
CPU_REG32 DWT_times[10];

volatile uint32_t SP_values[10];


unsigned timer_overflows = 0;
unsigned systick_overflows = 0;

const CPU_REG32 average_systick_times[10] = {0x000103A1, 0x000100C1,	0x0000FFE6,	0x0000CA54,	0x0000BE99,	0x0000BC1A,	0x0000B2B5,	0x0000B12B};
const int max_deviation_systick_times[10] = {1, 1, 1, 1, 1, 1, 1, 1};

const CPU_REG32 average_timer1_times[10] = {0x00000008,	0x00000064,	0x0000007F,	0x00000732,	0x000008A9,	0x000008F9,	0x00000A26,	0x00000A57};
const int max_deviation_timer1_times[10] = {1, 1, 1, 1, 1, 1, 1, 1};

const CPU_REG32 average_DWT_times[10] = {0x0000008F,	0x0000036F,	0x00000447,	0x000039DB,	0x00004597,	0x00004817,	0x0000517B,	0x00005307};
const int max_deviation_DWT_times[10] = {1, 1, 1, 1, 1, 1, 1, 1};

const uint32_t average_SP_values[10] = {0x2007F41C,	0x2007F41C,	0x2007F41C,	0x2007F394,	0x2007F394,	0x2007F41C,	0x2007F3D4,	0x2007F41C};
const int max_deviation_SP_values[10] = {1, 1, 1, 1, 1, 1, 1, 1};
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
		init_timer1(0xFFFFFFFF);
		Reset_Count_cycles_DWT();
		enable_timer1();
	
		read_current_values();	//read 1
	
		CPU_IntDis(); 					/*disable interrupt*/
    CPU_Init();   					/*init cpu - name and timestamp init*/
		
		read_current_values();	// read 2

    Mem_Init();							/*Memory initialization*/
		
		read_current_values();	// read 3

    OSInit(&err);						/* Initialize "uC/OS-III, The Real-Time Kernel"         */
		
		read_current_values();	// read 4
		
    OSTaskCreate((OS_TCB     *)&START_TSK_TCB,
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





