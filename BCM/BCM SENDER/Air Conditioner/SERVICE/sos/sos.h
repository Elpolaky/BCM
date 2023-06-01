/********************************************************************************************************************************
 *
 * @file    :   sos.h
 * @author  :   kareem magdy
 * @brief   :   Header File Contains all the types and Status Code For small operating system
 * @version :   1.0
 * @date    :   2023-5-30
 * 
 *******************************************************************************************************************************/

#ifndef SOS_H_
#define SOS_H_


#include "../../MCAL/timers/timer.h"
#include "../../MCAL/usart/uart.h"

#define  TASKS_MAX_NUMBER  50    

typedef struct {
	
	uint8_t u8_id;
	uint8_t u8_priority;
	uint8_t u8_periodicity;
	void(* ptr_task_func)(void);

}str_tasks_data_t;


typedef enum {
	SOS_INVALID_STATE,
	SOS_STATUS_SUCCESS,
	SOS_STATUS_ADD_SUCCESS,
	SOS_STATUS_INVALID_TASK,
	SOS_STATUS_INVALID_ID,								// id of a that we want to give to the task
	SOS_STATUS_INVALID_PRIORITY,
	SOS_STATUS_INVALID_PERIDOICITY,
	SOS_STATUS_INVALID_POTINTER_FUNC,
	SOS_STATUS_INVALID_TASK_ID ,						// id of a task added to the database
	SOS_STATUS_INVALID_EMBTY_DATABASE,
	
}enu_system_t;
  
  
  
  
  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to Initialize sos database
  *
  * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation
  *              SOS_STATUS_INVALID_STATE                :   In case of sos is already initialized
  *
  ********************************************************************************************************************************/    
  enu_system_t sos_init (void) ;
  
  

  
  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to denitialize sos database
  *
  * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation
  *              SOS_STATUS_INVALID_STATE                :   In case of sos de-initialized or was not initialized previously
  *
  ********************************************************************************************************************************/  
  enu_system_t sos_denit (void) ;
  
  
 
  
  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to create a new task and add it to database
  *
  * @param[in]   ptr_str_task						     :   Pointer to structure of the new task that wanted to be added
  *
  * @return      SOS_STATUS_ADD_SUCCESS                  :   In case of Successful Operation
  *              SOS_STATUS_INVALID_TASK				 :   In case of The pointer passed is NULL
  *				 SOS_STATUS_INVALID_ID				     :   In case of id of task is invalid
  *				 SOS_STATUS_INVALID_PRIORITY		     :   In case of priority of task is invalid
  *				 SOS_STATUS_INVALID_PERIDOICITY			 :   In case of periodicity of task is invalid
  *				 SOS_STATUS_INVALID_POTINTER_FUNC		 :   In case of pointer to function of task is invalid
  *
  ********************************************************************************************************************************/
  enu_system_t sos_create_task ( str_tasks_data_t * ptr_str_task) ;
  
  
  
  
  
  /******************************************************************************************************************************
  *
  * @brief                                               :   Function Used to modify a previous created task added to database
  *
  * @param[in]   ptr_str_task						     :   Pointer to structure of the new task that wanted to be added
  *				 u8_task_id								 :   uint8_t refers to the task number
  *
  *
  * @return      SOS_STATUS_ADD_SUCCESS                  :   In case of Successful Operation
  *				 SOS_STATUS_INVALID_TASK_ID				 :   In case id of passed task id invalid
  *              SOS_STATUS_INVALID_TASK				 :   In case of The pointer passed is NULL
  *				 SOS_STATUS_INVALID_ID				     :   In case of id of modified task is invalid
  *				 SOS_STATUS_INVALID_PRIORITY		     :   In case of priority of modified task is invalid
  *				 SOS_STATUS_INVALID_PERIDOICITY			 :   In case of periodicity of modified task is invalid
  *				 SOS_STATUS_INVALID_POTINTER_FUNC		 :   In case of pointer to function of modified task is invalid
  *
  ********************************************************************************************************************************/
  enu_system_t sos_modify ( uint8_t u8_task_id , str_tasks_data_t * str_modified_task) ;
  
  
  
  
  
  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to run the scheduler
  *
  * @param[in]   void									 :
  *
  *
  * @return      SOS_STATUS_ADD_SUCCESS                  :   In case of Successful Operation
  *              SOS_STATUS_INVALID_EMBTY_DATABASE		 :   In case of database has no tasks
  *			
  ********************************************************************************************************************************/
  enu_system_t sos_run(void) ;
  
  
    
  /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to disable the scheduler
  *
  * @param[in]   void									 :
  *
  *
  * @return      SOS_STATUS_ADD_SUCCESS                  :   In case of Successful Operation
  *              SOS_INVALID_STATE					 :   In case of scheduler didnt stop
  *			
  ********************************************************************************************************************************/
  enu_system_t sos_disable (void);
  
    /********************************************************************************************************************************
  *
  * @brief                                               :   Function Used to be passed to timer isr
  *
  * @param[in]   void									 :
  *
  *
  * @return     void									 :
  *			
  ********************************************************************************************************************************/
  void scheduler(void);

#endif /* SOS_H_ */