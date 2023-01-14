/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Descriptions:        Function prototypes included in secure_boot.c
** Correlated files:    secure_boot.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "cpu.h"

#define  TIMER1_CURRENT_VALUE      (*(CPU_REG32 *) 0x40008008) 
#define  TIMER1_PRESCALER          (*(CPU_REG32 *) 0x4000800C)

#define  BSP_REG_DWT_CR            (*(CPU_REG32 *) 0xE0001000)
#define  BSP_REG_DWT_CYCCNT        (*(CPU_REG32 *) 0xE0001004)
#define  BSP_REG_DEMCR             (*(CPU_REG32 *) 0xE000EDFC)

/* init_timer.c */
extern void init_timer1(uint32_t timerInterval );
extern void enable_timer1(void);
extern void disable_timer1(void);
extern void reset_timer1(void);
extern CPU_REG32 read_timer1(void);

/* IRQ_timer.c */
extern void TIMER1_IRQHandler (void);


/* Functions to work with the DWT counter */
void Reset_Count_cycles_DWT(void);
void Enable_Count_cycles_DWT(void);
void Disable_Count_cycles_DWT(void);
uint32_t Get_Count_cycles_DWT(void);

/* function to get current program counter */
static uint32_t __get_PC(void);

/* generic reader function to read timer and register values*/
void read_current_values(void);

/* functions to check whether the currenct startup matches 
	 with the predetermined, correct startup time */
int check_if_startup_was_correct(void);
