/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Descriptions:        interrupt handlers of Timer/Counter 0 and 1
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"

extern unsigned timer_overflows;

void TIMER1_IRQHandler (void)
{
	timer_overflows++;
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
