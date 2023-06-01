#include "APP.h"
#include <stdlib.h>
#include <string.h>
/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
************************************************************************************************************************/

/***********************************************************************************************************************
                                   FUNCTION IMPLMENTATION
************************************************************************************************************************/

	uint8_t  a[3] ="BCM" ;
	uint8_t  b[7] = "CONFIRM" ;
	uint8_t  c[9] = "OPERATING" ;
	uint8_t  d[1] = "&" ;
	uint8_t y	= sizeof(a);
	uint8_t x	= sizeof(b);
	uint8_t z	= sizeof(c);
	uint8_t o	= sizeof(d);
void app_Init(void){
	sei();
	bcm_init(&str_bcm_init_t);

	bcm_send_n(&str_bcm_init_t,a, y);
	bcm_send_n(&str_bcm_init_t,b, x);
	bcm_send_n(&str_bcm_init_t,c, z);
	bcm_send_n(&str_bcm_init_t,d, o);
	LED_INIT(pina0 );
	LED_INIT(pina1 );

}
	
void app_Start(void){
	 uint8_t x =   bcm_disbatcher(&str_bcm_init_t,RECEVING_FIRST);
	  if (x == BUFFER_SENT_OK)
	  {
		LED_ON(pina0);
	  }
	  if (x == BUFFER_RECEIVED_OK)
	  {
		LED_ON(pina1);
	  }
	
}
		


