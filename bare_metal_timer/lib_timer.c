/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "cpu.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 1
** Returned value:		None
**
******************************************************************************/
void enable_timer1(void)
{
	LPC_TIM1->TCR = 1;
	return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0
** Returned value:		None
**
******************************************************************************/
void disable_timer1(void)
{
	LPC_TIM1->TCR = 0;
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer1(void)
{
  uint32_t regVal;
	
	regVal = LPC_TIM1->TCR;
	regVal |= 0x02;
	LPC_TIM1->TCR = regVal;
  return;
}

uint32_t init_timer1 (uint32_t TimerInterval)
{
	#define  TIMER1_PRESCALER           (*((CPU_REG32 *)(0x4000800C))) 
	
	TIMER1_PRESCALER = 0x00000001; //setting the prescaler to the smallest possible value
	LPC_TIM1->MR0 = TimerInterval;
	LPC_TIM1->MCR = 3; //TC reset and interrupt generated
	NVIC_EnableIRQ(TIMER1_IRQn);
	return (1);
	
//*** <<< Use Configuration Wizard in Context Menu >>> ***
// <h> timer0 MCR
//   <e.0> MR0I
//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
//	 <i> 0 This interrupt is disabled.
//   </e>
//   <e.1> MR0R
//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.2> MR0S
//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.3> MR1I
//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC.
//	 <i> 0 This interrupt is disabled.
//   </e>
//   <e.4> MR1R
//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.5> MR1S
//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.6> MR2I
//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
//	 <i> 0 This interrupt is disabled.
//   </e>
//   <e.7> MR2R
//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.8> MR2S
//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.9> MR3I
//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
//	 <i> 0 This interrupt is disabled.
//   </e>
//   <e.10> MR3R
//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.11> MR3S
//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC.
//	 <i> 0 Feature disabled.
//   </e>
// </h>
//*** <<< end of configuration section >>>    ***
}


CPU_REG32 read_timer1(void) {
	#define  TIMER1_CURRENT_VALUE           (*((CPU_REG32 *)(0x40008008))) 
	CPU_REG32 ret_val = TIMER1_CURRENT_VALUE;
	return ret_val;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
