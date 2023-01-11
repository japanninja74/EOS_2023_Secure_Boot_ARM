/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           secure_boot.c
** Description:         Function that provide a basice secure_boot for Micrium OS, with restrictions
** Correlated files:    secure_boot.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "secure_boot.h"
#include "cpu.h"
#include "bsp.h" //not sure if it is needed

extern unsigned timer_overflows;

extern CPU_REG32 systick_times[6];
extern CPU_REG32 timer1_times[6];
extern CPU_REG32 DWT_times[6];

/* FUNCTIONS TO WORK WITH TIMER 1 */

/* Enable timer 1 */
void enable_timer1(void)
{
	LPC_TIM1->TCR = 1; /* set control register bit 1 to 1 */
	return;
}

/* Disable timer 1 */
void disable_timer1(void)
{
	LPC_TIM1->TCR = 0; /* set control register bit 1 to 0 */
  return;
}

/* reset timer 1 */
void reset_timer1(void)
{
  uint32_t regVal;
	
	regVal = LPC_TIM1->TCR;
	regVal |= 0x02;
	LPC_TIM1->TCR = regVal;
  return;
}

/* initialize timer 1 */
void init_timer1 (uint32_t TimerInterval)
{
	TIMER1_PRESCALER = 0x00000001; //setting the prescaler to the smallest possible value
	LPC_TIM1->MR0 = TimerInterval;
	LPC_TIM1->MCR = 3; //TC reset and interrupt generated
	NVIC_EnableIRQ(TIMER1_IRQn);
	
	return;
}

/* Read timer 1's value */
CPU_REG32 read_timer1(void) {
	CPU_REG32 ret_val = TIMER1_CURRENT_VALUE;
	
	return ret_val;
}


/* Interrupt handler for Timer 1 */
void TIMER1_IRQHandler (void)
{
	timer_overflows++; 		/* increment timer overflows */
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/* FUNCTIONS TO WORK WITH THE DWT */

/* Reset the DWT Cycle Counter's value to zero */
void Reset_Count_cycles_DWT (void){
	
	BSP_REG_DWT_CYCCNT  = 0; //Reset this values for counting
		
}

/* Enable the Cycle counter */
void Enable_Count_cycles_DWT (void){
	
	BSP_REG_DEMCR  |= DEF_BIT_24; //Activate debug exception and monitor control --set the bit 24 to 1
  BSP_REG_DWT_CR |= DEF_BIT_00; //Enable the CYYCCNT counter by setting bit 1 to 1
	
	return;
}

/* disable the Cycle counter */
void Disable_Count_cycles_DWT (void){
	BSP_REG_DWT_CR &= ~DEF_BIT_00; //Disable the CYYCCNT counter by setting bit 1 to 0
	
	return;
}

/* retrieve the Cycle counter's current value */
uint32_t Get_Count_cycles_DWT (void){
	uint32_t cycles = BSP_REG_DWT_CYCCNT;
	
	return cycles;
	
	//this only works if the CPU_CFG_TS_TMR_EN is enabled
	//CPU_TS32         timestamp;
	//CPU_INT64U       usecs;
	//timestamp = CPU_TS_Get32();           /* Read current timestamp counter value.      */
	//usecs = CPU_TS32_to_uSec(timestamp);  /* Convert timestamp counter to microseconds. */	
}

void read_current_values(void)
{
	//static variable to index current value arrays
	static int array_index = 0;
	
	CPU_SR_ALLOC(); 																	//needed for critical section
	CPU_CRITICAL_ENTER(); 														//disabling interrupts for critical section process
	
	systick_times[array_index] = CPU_REG_NVIC_ST_CURRENT;
	timer1_times[array_index] = read_timer1();
	DWT_times[array_index] = Get_Count_cycles_DWT();
	
	CPU_CRITICAL_EXIT(); 															//exiting critical section	
	
	array_index++;																		//before exiting incremnt index
	
	return;
}

int check_if_startup_was_correct(void)
{
	if(0){
		//TODO: fill out condition correctly
		return 1;
	}
	else {
		return 0;
	}
}
/******************************************************************************
**                            End Of File
******************************************************************************/
