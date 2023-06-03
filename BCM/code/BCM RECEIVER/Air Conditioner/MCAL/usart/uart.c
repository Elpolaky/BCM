/*
 * uart.h
 *
 * Created: 11/5/2023 10:34:00 AM
 *  Author: AMR
 */ 

	
	
#include "uart.h"

volatile uint8_t uint8_t_g_receive_arr[20];
volatile uint8_t *uint8_t_g_send_ptr;
static uint8_t *uint8_t_g_receive_ptr;
static uint8_t uint8_t_flag;
static uint8_t *arr_ptrs [100] = {0};
	 
	 
static void(*uart_RX_fptr)(void) = NULL;
static void(*uart_TX_fptr)(void) = NULL;


enu_return_error_t uart_init()
{
			uint16 baud;
			//Enable writing to UCSRC
			set_bit(UCSRC,URSEL);
			enu_return_error_t retval = valid;

			switch (g_str_uart_config[CHANNEL_0].enu_role_config)
			{
				
				case transmit_enable:
				{
					set_bit(UCSRB,TXEN);
					break;
				}
				case receive_enable:
				{
					set_bit(UCSRB,RXEN);
					break;
				}
				case transmit_receive_enable:
				{
					set_bit(UCSRB,RXEN);
					set_bit(UCSRB,TXEN);
					break;
				}
				default:
				{
					retval = invalid;
				}
			}	
				
			//speed config
			switch (g_str_uart_config[CHANNEL_0].enu_speed_config)
			{
				case normal_speed:
				{
					clear_bit(UCSRA, U2X);
					baud = 51;
					UBRRL = (uint8_t)baud;
					UBRRH = (uint8_t)(baud >> 8);
					break;
				}
				case double_speed:
				{
					set_bit(UCSRA, U2X);
					baud = 0;
					UBRRL = (uint8_t)baud;
					UBRRH = (uint8_t)(baud >> 8);
					break;
				}
				default:
				{
					retval = invalid;
				}
			}
		
			//parity config
			switch (g_str_uart_config[CHANNEL_0].enu_parity_config)
			{
				case no_parity:
				{
					clear_bit(UCSRC,UPM0);
					clear_bit(UCSRC,UPM1);
					break;
				}
				case even_parity:
				{
					clear_bit(UCSRC,UPM0);
					set_bit(UCSRC,UPM1);
					break;
				}
				case odd_parity:
				{
					set_bit(UCSRC,UPM0);
					set_bit(UCSRC,UPM1);
					break;
				}
				default:
				{
					retval = invalid;
				}
			}
			
			//Sync config		
			switch (g_str_uart_config[CHANNEL_0].enu_mode_config)
			{
				case synchronous:
				{
					set_bit(UCSRC, UMSEL);
					break;
				}
				case asynchronous:
				{
					clear_bit(UCSRC, UMSEL);
					break;
				}
				default:
				{
					retval = invalid;
				}
			}
			
			//Stop bits config
			switch (g_str_uart_config[CHANNEL_0].enu_stop_bits_config)
			{
				case one_stop_bit:
				{
					clear_bit(UCSRC, USBS);
					break;
				}
				case two_stop_bit:
				{
					set_bit(UCSRC, USBS);
					break;
				}
				default:
				{
					retval = invalid;
				}
			}
			
			//data bits config
			switch (g_str_uart_config[CHANNEL_0].enu_data_size_config)
			{
				case _5_data_bits:
				{
					clear_bit(UCSRC, UCSZ0);
					clear_bit(UCSRC, UCSZ1);
					clear_bit(UCSRB, UCSZ2);
					break;
				}
				case _6_data_bits:
				{
					set_bit(UCSRC, UCSZ0);
					clear_bit(UCSRC, UCSZ1);
					clear_bit(UCSRB, UCSZ2);
					break;
				}
				case _7_data_bits:
				{
					clear_bit(UCSRC, UCSZ0);
					set_bit(UCSRC, UCSZ1);
					clear_bit(UCSRB, UCSZ2);
					break;
				}
				case _8_data_bits:
				{
					set_bit(UCSRC, UCSZ0);
					set_bit(UCSRC, UCSZ1);
					clear_bit(UCSRB, UCSZ2);
					break;
				}
				case _9_data_bits:
				{
					set_bit(UCSRC, UCSZ0);
					set_bit(UCSRC, UCSZ1);
					set_bit(UCSRB, UCSZ2);
					break;
				}
				default:
				{
					retval = invalid;
				}
			}	

	
	
	return retval;
}

/****************************************************receive*******************************************************/

void uart_RX_intEnable (void)
{
	set_bit(UCSRB,RXCIE);
}
void uart_RX_intDisable(void)
{
	clear_bit(UCSRB,RXCIE);
}


ISR(UART_RXC_vect)
{
	if (uart_RX_fptr != NULL)
	{
		uart_RX_fptr();
	}
}


// Receiving Frames with 5 to 8 Data Bits
uint8_t uart_receive(void)
{
	return UDR;		
}

uint8_t uart_receive_string (uint8_t *string) 
{
	uint8_t_g_receive_ptr = string;
}

void uart_RX_SetCallBack (void(*local_fptr)(void))
{
	uart_RX_fptr = local_fptr;
}


/***************************************************send**********************************************************/


ISR(UART_TX_vect)
{


	
	if (uart_TX_fptr != NULL)
	{
		uart_TX_fptr();
	}
}

void uart_TX_intEnable (void)
{
	set_bit(UCSRB,TXCIE);
}
void uart_TX_intDisable(void)
{
	clear_bit(UCSRB,TXCIE);
}
	
void uart_TX_SetCallBack (void(*local_fptr)(void))
{
	uart_TX_fptr = local_fptr;
}	

// Data Transmission Sending Frames with 5 to 8 Data Bit
void uart_transmit( uint8_t data )
{										// Put data into buffer, sends the data
	UDR = data;	
}




void uart_TX_RX_interrupt_enable(void){
	
	uart_RX_intEnable();
	uart_TX_intEnable();
}


void uart_TX_RX_interrupt_disable(void){
	
	uart_RX_intDisable();
	uart_TX_intDisable();
}
