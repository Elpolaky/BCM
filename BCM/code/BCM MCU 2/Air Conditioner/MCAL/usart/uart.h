/*
 * uart.h
 *
 * Created: 11/5/2023 10:33:46 AM
 *  Author: Amr
 */ 


#ifndef UART_H_
#define UART_H_

// Includes

#include "../dio/DIO.h"
#include "uart_config.h"
#include "../MEMORYMAP.h"

extern volatile uint8_t uint8_t_g_receive_arr[20];

// register bits config
#define  RXEN  4
#define  TXEN  3
#define  URSEL 7
#define  UCSZ0 1
#define  UDRE  5
#define  RXC   7
#define  UCSZ1 2

#define USBS	3
#define UPM0	4
#define UPM1	5
#define UMSEL	6

#define UCSZ0	1
#define UCSZ1	2
#define UCSZ2	2

#define U2X		1

#define RXCIE	7
#define TXCIE	6
#define UDRIE	5





typedef enum{
	valid =0,
	invalid,
	failed
}enu_return_error_t;


// Functions prototypes
enu_return_error_t uart_init();
enu_return_error_t uart_denit();
void uart_transmit(uint8_t data);
uint8_t uart_receive(void);
void uart_Transmit_string (uint8_t * str);
uint8_t uart_receive_string (uint8_t *string);

void uart_RX_SetCallBack (void(*local_fptr)(void));
void uart_TX_SetCallBack (void(*local_fptr)(void));

void uart_RX_intEnable (void);
void uart_RX_intDisable(void);

void uart_TX_intEnable (void);
void uart_TX_intDisable(void);

void uart_TX_RX_interrupt_enable(void);
void uart_TX_RX_interrupt_disable(void);
#endif /* UART_H_ */

