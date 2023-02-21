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
#include "bsp.h"

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
	
}

/* Read timer 1's value */
CPU_REG32 read_timer1(void) {
	
	return 0;
}


/* Interrupt handler for Timer 1 */
void TIMER1_IRQHandler (void)
{

}

/* FUNCTIONS TO WORK WITH THE DWT */

/* Reset the DWT Cycle Counter's value to zero */
void Reset_Count_cycles_DWT (void){
		
}

/* Enable the Cycle counter */
void Enable_Count_cycles_DWT (void){

}

/* disable the Cycle counter */
void Disable_Count_cycles_DWT (void){

}

/* retrieve the Cycle counter's current value */
uint32_t Get_Count_cycles_DWT (void){
	return 0;
}

void read_current_values(void)
{

}

int check_if_startup_was_correct(void)
{
	return 0;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
