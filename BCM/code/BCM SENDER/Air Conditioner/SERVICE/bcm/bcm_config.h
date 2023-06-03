/*
 * bcm_config.h
 *
 * Created: 5/27/2023 9:30:32 PM
 *  Author: moham
 */ 


#ifndef BCM_CONFIG_H_
#define BCM_CONFIG_H_

#include "../../MCAL/usart/uart.h"


typedef struct {
	
	void (*ptr_func_init)();
	void (*ptr_func_interrupt_enable)();
	void (*ptr_func_denit)();
	void (*ptr_func_interrupt_disable)();
	
}str_bcm_instance_t;

typedef enum {
	READY,
	TX_DONE,
	RX_DONE,
}enu_uart_interrupt_flag;



extern str_bcm_instance_t str_bcm_init_t;
extern enu_uart_interrupt_flag gl_uart_state ;
extern enu_uart_interrupt_flag gl_uart_state2 ;

void uart_isr_send_func (void);

void uart_isr_recieve_func (void);

#endif /* BCM_CONFIG_H_ */