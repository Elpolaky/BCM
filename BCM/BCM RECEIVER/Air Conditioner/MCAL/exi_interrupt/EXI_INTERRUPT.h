﻿
#ifndef exi_interrupt_H_
#define exi_interrupt_H_

/*****************************************************************************************************************************************************************
*									Includes																				 *
******************************************************************************************************************************************************************/
#include "../MEMORYMAP.h"
#include "../../UTILITIES/utiles.h"
#include "../DIO/DIO.h"

/*****************************************************************************************************************************************************************
*									Typedefs																				 *
******************************************************************************************************************************************************************/
typedef enum EN_int__error_t {
	ok,
	Error
}EN_int__error_t;

typedef enum {
	LOW_LEVEL,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}EN_trig;

typedef enum{
	EXT_INT_0,
	EXT_INT_1,
	EXT_INT_2,
}EN_int_t;

/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
******************************************************************************************************************************/
extern  uint8_t car_flag   ; 
/*****************************************************************************************************************************************************************
*									Functions declarations																				 *
******************************************************************************************************************************************************************/
EN_int__error_t EXI_Enable (EN_int_t Interrupt);
EN_int__error_t EXI_Disable (EN_int_t Interrupt);
EN_int__error_t EXI_Trigger(EN_int_t Interrupt,EN_trig trigger);
void EXI_SetCallBack(EN_int_t Interrupt,void(*ptrf)(void));

extern uint8_t car_flag ;


#endif 