
#ifndef app_H_
#define app_H_



/*****************************************************************************************************************************************************************
*									Includes																				 *
******************************************************************************************************************************************************************/
#include "../MCAL/DIO/DIO.h"
#include "../HAL/lcd/LCD.h"
#include "../MCAL/timers/timer.h"
#include "../HAL/buzzer/buzzer.h"
#include "../MCAL/usart/uart.h"
#include "../SERVICE/bcm/bcm.h"
#include "../MCAL/MEMORYMAP.h"
 
void app_Init(void);
void app_Start(void);
#endif








