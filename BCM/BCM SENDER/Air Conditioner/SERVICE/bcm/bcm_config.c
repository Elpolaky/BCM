/*
 * bcm_config.c
 *
 * Created: 5/27/2023 9:30:15 PM
 *  Author: moham
 */ 

#include "bcm_config.h"
#include "../../MCAL/dio/DIO.h"

enu_uart_interrupt_flag  gl_uart_state = READY ;
enu_uart_interrupt_flag  gl_uart_state2 = READY ;

str_bcm_instance_t str_bcm_init_t = {
	
	uart_init, 
	uart_TX_RX_interrupt_enable,
};


//--------------------------- UART INTERRUPT HANDLING -------------------- //

void uart_isr_send_func (void){
	DIO_INITPIN(pinc1,OUTPUT);
	DIO_WRITEPIN(pinc1,HIGH);
	gl_uart_state = TX_DONE ;
	
}

void uart_isr_recieve_func (void){
	
	DIO_INITPIN(pinc5,OUTPUT);
	DIO_WRITEPIN(pinc5,HIGH);
	gl_uart_state2 = RX_DONE ;
	
	
}


 //uart_TX_SetCallBack (uart_isr_send_func);

//-----------------------------------------------------------//
