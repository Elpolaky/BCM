/*
 * bcm.c
 *
 * Created: 5/27/2023 8:07:34 PM
 *  Author: moham
 */ 
#include "bcm.h"

static enu_bcm_communciation_protocol gl_protocol ;


static str_sending_receving_queue_t *str_sending_buffer ;
static str_sending_receving_queue_t *str_receving_buffer ;


enu_sysem_status_t bcm_init(str_bcm_instance_t *ptr_bcm_instance_t){
	
	enu_sysem_status_t l_bcm_status = BCM_VALID ;
	
	if(ptr_bcm_instance_t  != NULL){
		
			ptr_bcm_instance_t->ptr_func_init();
			ptr_bcm_instance_t->ptr_func_interrupt_enable();

	}
	
	else {
		
		l_bcm_status = BCM_FAILD;
	}
		
		
	return l_bcm_status ;
	
}


enu_sysem_status_t bcm_denit(str_bcm_instance_t *ptr_bcm_instance_t){
	
	enu_sysem_status_t l_bcm_status = BCM_VALID ;
	if(ptr_bcm_instance_t != NULL){
		
		
		ptr_bcm_instance_t->ptr_func_denit();
		ptr_bcm_instance_t->ptr_func_interrupt_disable();
		
	}
	
	else {
		
		l_bcm_status = BCM_FAILD;
	}
	
	
	return l_bcm_status ;
	
}

	
enu_bcm_send_state_t bcm_send( str_bcm_instance_t *ptr_bcm_instance_t ,uint8_t * ptr_buffer){
	
static enu_bcm_send_state_t l_send_state_ = IDLE ;
	if(ptr_bcm_instance_t != NULL){
		if(ptr_bcm_instance_t->ptr_func_init== uart_init)                 								/*   using uart  */
		{	
			if(l_send_state_ == IDLE ){													
				
				uart_transmit(* ptr_buffer);															// sending a byte
				uart_TX_SetCallBack (uart_isr_send_func);												// callback set gl_uart_state to TX_DONE if tx complete
				l_send_state_= SENDING;
					 
			}
			else if (l_send_state_ == SENDING)
			{
				 if (gl_uart_state == TX_DONE)
				 {
						 
					 l_send_state_  = DATA_SENT_OK;
					 gl_uart_state = READY ;

						 
				 } 
				 else if(gl_uart_state != TX_DONE && gl_uart_state != READY ) 
				 {
					l_send_state_=DATA_SENT_FAILD; 
				 }

			}
		
			}
		}
		
		else {
			
			l_send_state_ = BCM_FAILD;
		}
		
	return l_send_state_;
}


enu_bcm_send_state_t bcm_send_n( str_bcm_instance_t *ptr_bcm_instance_t ,uint8_t * ptr_buffer,uint8_t a_buffer_length){
	
		static enu_bcm_send_state_t l_sendState = FIRST_TIME_SENDING ;
		static uint8_t l_bufferNum = FIRST_BUFFER ;
		
	if(ptr_bcm_instance_t != NULL){
		
		if(ptr_bcm_instance_t->ptr_func_init== uart_init)
			{
				if (l_sendState == FIRST_TIME_SENDING && ptr_buffer != NULL)													// check if it is the first use to bcm_send_n
				{		
					str_sending_buffer->ptr_data_buffer[l_bufferNum] = ptr_buffer;												// saving buffer pointer in queue
					str_sending_buffer->u8_dataSize[l_bufferNum] = a_buffer_length ;											// saving buffer size in queue
					gl_uart_state = TX_DONE ;																					// set uart send flag to tx done to make dispatcher start sending
					l_bufferNum++;																								// accessing the next pointer to save in it if we use this func again
					l_sendState = NOT_FIRST_TIME_SENDING ;																		// to enter the NOT_FIRST_TIME_SENDING state
					
				} 
				else if (l_sendState == NOT_FIRST_TIME_SENDING && ptr_buffer != NULL)											// check if it is not the first use to bcm_send_n
				{
					str_sending_buffer->ptr_data_buffer[l_bufferNum]= ptr_buffer;												// saving buffer pointer in queue
					str_sending_buffer->u8_dataSize[l_bufferNum]=a_buffer_length;											    // saving buffer size in queue
					l_bufferNum++;																								// accessing the next pointer to save in it if we use this func again
					str_sending_buffer->ptr_data_buffer[l_bufferNum]=NULL;
				}
				else if (ptr_buffer == NULL)																					
				{
					str_sending_buffer->ptr_data_buffer[l_bufferNum]=NULL;
					l_sendState = SEND_FAILD_NULL_PTR;
				}	
			}
		}
		else 
		{	
			l_sendState = BCM_FAILD;
		}
		
		return l_sendState;
	
	
	
}


enu_bcm_send_state_t bcm_disbatcher(str_bcm_instance_t *ptr_bcm_instance_t ,enu_bcm_first_use a_first_use)
{
	static enu_bcm_first_use l_first_use ;
	if(l_first_use != 0)																									// used to convert the state of the dispatcher between sending and receiving
	{
		a_first_use = l_first_use;
	}
	else
	{
		l_first_use =a_first_use;
	}
	static uint8_t l_buffer_Num									= FIRST_BUFFER ;
	static uint8_t l_buffer_element								= FIRST_ELEMENT;
	static uint8_t l_rx_buffer_element							= FIRST_ELEMENT;
	static enu_bcm_send_state_t dispatcher_state				= IDLE ;
	 uint16 l_buffer_size										=str_sending_buffer->u8_dataSize[l_buffer_Num];
	
	if(ptr_bcm_instance_t->ptr_func_init == uart_init)																		// if we use uart
	{
		if( l_first_use == SENDING_FIRST)																					// if app select to send first or we activities sending after receiving
		{
			if(gl_uart_state == TX_DONE )																					// if sending is done
			{							
				if(l_buffer_element < l_buffer_size )																		// checking if we not send all buffer yet
				{	
					gl_uart_state								= READY ;                                                   // set flag that passed to isr to ready to let isr change it if tx completed
					uart_transmit(str_sending_buffer->ptr_data_buffer[l_buffer_Num][l_buffer_element]);						// sending buffer elements
					uart_TX_SetCallBack(uart_isr_send_func);					
					l_buffer_element++;
					dispatcher_state							= SENDING ;													// state of dispatcher now is sending 
			
				}
		
				else if ( l_buffer_element >= l_buffer_size )																// checking if we send all buffer 
				{
			
					gl_uart_state								= READY ;													// set flag that passed to isr to ready to let isr change it if tx completed
					dispatcher_state							= BUFFER_SENT_OK ;											// state of dispatcher now is BUFFER_SENT_OK 
					l_buffer_Num++;																							// accessing next buffer to send
					
					if (str_sending_buffer->ptr_data_buffer[l_buffer_Num] != NULL)											// checking if there is another buffer to send				
					{
						
						gl_uart_state							= TX_DONE ;													// to let dispatcher send 
						l_buffer_element						= FIRST_ELEMENT;
						dispatcher_state						= IDLE ;
					}
					else{																									// if there is no other buffer
						gl_uart_state								= READY ;
						l_buffer_element						= FIRST_ELEMENT;
						l_first_use								= RECEVING_FIRST;											// activate receiving
					}
				}
			}
		}
		
		else if( l_first_use == RECEVING_FIRST)																			// if app select to send first or we activities sending after receiving 
		{
			
			uart_RX_SetCallBack(uart_isr_recieve_func);
			if (gl_uart_state2 == RX_DONE)																				// if there is data to read 
			{
		
				str_receving_buffer->ptr_dataBASE[l_rx_buffer_element] = uart_receive();                                // saving data in array
				
				if(str_receving_buffer->ptr_dataBASE[l_buffer_element] != NULL)
				{	
					if(str_receving_buffer->ptr_dataBASE[l_rx_buffer_element]  == '&')									// if we receive the acknowledge of sending is done 
					{
						l_rx_buffer_element							=FIRST_ELEMENT;
						l_first_use									= SENDING_FIRST;									// activate sending again
						gl_uart_state								= TX_DONE;
						dispatcher_state							= BUFFER_RECEIVED_OK;								// state of dispatcher now is BUFFER_RECEIVED_OK 
						gl_uart_state2								= READY;
					}
					else
					{	
						dispatcher_state							= RECEVING;											// state of dispatcher now is BUFFER_RECEIVED_OK
						l_rx_buffer_element++;
						gl_uart_state2								= READY;
					}
						
					
				}
			
			}
		}
		
		else
		{

			dispatcher_state									 = INVALID_STATE;
		}
		
	}
	return dispatcher_state ;
}