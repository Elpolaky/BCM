/*
 * uart_config.h
 *
 * Created: 5/1/2023 10:34:27 AM
 *  Author: acer
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_



#define UART_CHANEELS  3

typedef enum{
	CHANNEL_0,
	CHANNEL_1,
	CHANNEL_2
}enu_uart_channels_t;


typedef enum{
	normal_speed =0,
	double_speed,
	total_speed
}enu_speed_mode_selector_t;



typedef enum{
	transmit_enable =0,
	receive_enable,
	transmit_receive_enable,
	total_enable
}enu_role_selector_t;

typedef enum{
	no_parity =0,
	even_parity,
	odd_parity,
	total_parity
}enu_parity_mode_selector_t;


typedef enum{
	synchronous =0,
	asynchronous,
	total_synch
}enu_sync_mode_selector_t;


typedef enum{
	one_stop_bit =0,
	two_stop_bit,
	total_stop
}enu_number_stopBits_selector_t;


typedef enum{
	_5_data_bits =0,
	_6_data_bits,
	_7_data_bits,
	_8_data_bits,
	_9_data_bits,
	total_bits
}enu_number_dataBits_selector_t;




typedef struct
{
	enu_speed_mode_selector_t			    enu_speed_config;
	enu_role_selector_t						enu_role_config;
	enu_parity_mode_selector_t			    enu_parity_config;
	enu_sync_mode_selector_t			    enu_mode_config;
	enu_number_stopBits_selector_t		    enu_stop_bits_config;
	enu_number_dataBits_selector_t		    enu_data_size_config;
}str_uart_config_t;


extern str_uart_config_t g_str_uart_config [UART_CHANEELS];

#endif /* UART_LCFG_H_ */
 


