/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Descriptions:        Prototypes of functions included in lib_timer.c and IRQ_timer.c
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "cpu.h"

#ifndef __TIMER_H
#define __TIMER_H

/* init_timer.c */
extern uint32_t init_timer1(uint32_t timerInterval );
extern void enable_timer1(void);
extern void disable_timer1(void);
extern void reset_timer1(void);

extern CPU_REG32 read_timer1(void);

/* IRQ_timer.c */
extern void TIMER1_IRQHandler (void);

#endif /* end __TIMER_H */
