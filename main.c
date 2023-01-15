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



CPU_REG32 systick_times[6];
CPU_REG32 timer1_times[6];
CPU_REG32 DWT_times[6];

volatile uint32_t SP_values[6];
volatile uint32_t PC_values[6];


unsigned timer_overflows = 0;
unsigned systick_overflows = 0;
//TODO: add overflow arrays?

const CPU_REG32 correct_systick_times[6] = {0x000103AA, 0x000102F9, 0x0001003D, 0x0000FF69, 0x0000BCF3, 0x0000BC4F};
const CPU_REG32 correct_timer1_times[6] = {0x00000008, 0x0000001D, 0x00000076, 0x0000008F, 0x000008DF, 0x000008F3};
const CPU_REG32 correct_DWT_times[6] = {0x00000088, 0x00000134, 0x000003F4, 0x000004C4, 0x00004740, 0x000047E0};

volatile const uint32_t correct_SP_values[6] = {0x2007F040, 0x2007F040, 0x2007F040, 0x2007F040, 0x2007F040, 0x2007F040};
volatile const uint32_t correct_PC_values[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

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

		read_current_values();	//read 2

    CPU_Init();   					/*init cpu - name and timestamp init*/
		
		read_current_values();	// read 3

    Mem_Init();							/*Memory initialization*/
		
		read_current_values();	// read 4

    OSInit(&err);						/* Initialize "uC/OS-III, The Real-Time Kernel"         */
		
		read_current_values();	// read 5
    /* Create the start task */
		
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


//Tasks

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





