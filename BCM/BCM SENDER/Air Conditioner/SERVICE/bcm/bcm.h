/********************************************************************************************************************************
 *
 * @file    :   bcm.h
 * @author  :   kareem magdy
 * @brief   :   Header File Contains all the types and Status Code For bcm
 * @version :   2.0
 * @date    :   2023-1-6
 * 
 *******************************************************************************************************************************/


#ifndef BCM_H_
#define BCM_H_

#include "bcm_config.h"

typedef enum{
	
	_INVALID_PROTOCOL_,
	BCM_VALID,
	BCM_FAILD
}enu_sysem_status_t;

typedef enum{
	_UART_,
	_SPI_,
	_I2C_,
	_NOT_SUPPORTED_
}enu_bcm_communciation_protocol;


typedef enum{
	
	
	IDLE,
	INVALID_STATE,
	INTERRUPT_FAILED,
	SENDING,
	RECEVING,
	DATA_SENT_OK,
	DATA_SENT_FAILD,
	FIRST_TIME_SENDING,
	NOT_FIRST_TIME_SENDING,
	SEND_FAILD_NULL_PTR,
	BUFFER_SENT_OK,
	BUFFER_RECEIVED_OK,
}enu_bcm_send_state_t;


typedef enum{
	SENDING_FIRST = 1,
	RECEVING_FIRST

}enu_bcm_first_use;

#define  FIRST_BUFFER	0 
#define  FIRST_ELEMENT	0

typedef struct {
	
	uint8_t  *ptr_data_buffer[200];
	uint16  u8_dataSize[200];
	uint8_t ptr_dataBASE[20];
}str_sending_receving_queue_t;


  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to Initialize the corresponding communication protocol
  *
  * @param[in]   ptr_bcm_instance_t						 :   Pointer to structure of the corresponding communication protocol
  *
  * @return      BCM_VALID							     :   In case of Successful Operation
  *              BCM_FAILD								 :   In case of structure of the corresponding communication protocol IS NULL
  *
  ********************************************************************************************************************************/   
enu_sysem_status_t bcm_init(str_bcm_instance_t *ptr_bcm_instance_t);


/********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to denitialize the corresponding communication protocol
  *
  * @param[in]   ptr_bcm_instance_t						 :   Pointer to structure of the corresponding communication protocol
  *
  * @return      BCM_VALID							     :   In case of Successful Operation
  *              BCM_FAILD								 :   In case of structure of the corresponding communication protocol IS NULL
  *
  ********************************************************************************************************************************/  
enu_sysem_status_t bcm_denit(str_bcm_instance_t *ptr_bcm_instance_t);



/********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to send a byte
  *
  * @param[in]   ptr_buffer								 :   Pointer to the data buffer
  *
  * @return      DATA_SENT_OK							 :   In case of Successful Operation
  *				 INVALID_STATE							 :   In case of structure of the corresponding communication protocol IS NULL
  *
  ********************************************************************************************************************************/   
enu_bcm_send_state_t bcm_send( str_bcm_instance_t *ptr_bcm_instance_t ,uint8_t * ptr_buffer);



  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used store the pointer of the data buffer in ptr_data_buffer
  *
  * @param[in]   ptr_bcm_instance_t					     :   Pointer to structure of the corresponding communication protocol
  *				 ptr_buffer								 :	 Pointer to the data buffer
  *				 a_buffer_length						 :	 length  of the data buffer
  *
  * @return		 NOT_FIRST_TIME_SENDING					 :   In case of Successful Operation
  *              INVALID_STATE							 :   In case of structure of the corresponding communication protocol IS NULL
  *				 SEND_FAILD_NULL_PTR					 :   In case of ptr_buffer IS NULL	
  *
  ********************************************************************************************************************************/   
enu_bcm_send_state_t bcm_send_n( str_bcm_instance_t *ptr_bcm_instance_t , uint8_t * ptr_buffer,uint8_t a_buffer_length);


  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to Initialize sos database
  *
  * @param[in]   ptr_bcm_instance_t					     :   Pointer to structure of the corresponding communication protocol
  *				 a_first_use							 :	 enum refers to if we will send first or receive first
  *
  * @return     IDLE									 :   In case of Successful Operation
				SENDING									 :   In case of we sending a buffer and not done sending all of it
  *             BUFFER_SENT_OK							 :   In case of all buffer is sent 
  *				RECEVING								 :   In case of we receiving a buffer and not done receiving all of it
  *				BUFFER_RECEIVED_OK                       :   In case of all buffer is received 
  *				INVALID_STATE							 :   In case of a_first_use is not valid
  * 
  ********************************************************************************************************************************/   
enu_bcm_send_state_t bcm_disbatcher(str_bcm_instance_t *ptr_bcm_instance_t , enu_bcm_first_use a_first_use);

#endif /* BCM_H_ */