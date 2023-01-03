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


     /* ----------------- APPLICATION GLOBALS ------------------ */


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
	
		SystemInit();	 					/*initialize the clock */
		BSP_IntInit();					/*initiialize interrupt*/
		BSP_Start(); 						/*initialize kernel system tick timer */

		CPU_IntDis(); 					/*disable interrupt*/
    CPU_Init();   					/*init cpu*/


    Mem_Init();							/*Memory initialization*/
	

    OSInit(&err);						/* Initialize "uC/OS-III, The Real-Time Kernel"         */
	

    /* Create the start task                                */
    




    OSStart(&err);      /* Start multitasking (i.e. give control to uC/OS-III). */

    while(DEF_ON){			/* Should Never Get Here	*/
    };
}






