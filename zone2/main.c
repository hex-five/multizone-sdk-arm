/* Copyright(C) 2019 Hex Five Security, Inc. - All Rights Reserved */

#include <string.h>	// strcmp()
#include <inttypes.h> // uint16_t, ...

#include "platform.h"
#include "multizone.h"
#include "gpio_driver.h"

// ------------------------------------------------------------------------
void systick_handler(void) __attribute__ ((interrupt ("irq"))); 
void systick_handler(void){
// ------------------------------------------------------------------------
	/* Set soft-timer */
	const uint64_t T0 = MZONE_RDTIME();
	const uint64_t T1 = T0 + (RTC_FREQ*(500/1000.0)); // 500 ms
	MZONE_WRTIMECMP(T1);
	
	if (LED_OUT(LED))	
	{
		LED_CLR(LED);
	}
	else
	{
		LED_SET(LED);
	}

}

// ------------------------------------------------------------------------
void btn_handler(void) __attribute__ ((interrupt ("irq"))); 
void btn_handler(void){
// ------------------------------------------------------------------------
    BTN_IRQ_CLR();      /* Clear pending */
	
	char msg[16] = "NVIC IRQ [BTN1]";
	MZONE_SEND(1, msg);

	LED_SET(LED);

	/* Set soft-timer */
	const uint64_t T0 = MZONE_RDTIME();
	const uint64_t T1 = T0 + (RTC_FREQ*(3000/1000.0)); // 3000 ms
	MZONE_WRTIMECMP(T1);
}

// ------------------------------------------------------------------------
static void button_init (void) {
// ------------------------------------------------------------------------
    BTN_INIT(BTN_PIN);
	STORE_NVICISER(BTN_IRQn);	/* Enable interrupt on NVIC */
}

// ------------------------------------------------------------------------
static void led_init (void) {
// ------------------------------------------------------------------------
    LED_INIT(LED);
}

// ------------------------------------------------------------------------
int main (void) {
// ------------------------------------------------------------------------

	//volatile int w=0; while(1){w++;}
	//while(1) MZONE_YIELD();
	//while(1) MZONE_WFI();

	int i = 0;
    led_init();
    button_init();

	/* Set soft-timer */
   	const uint64_t T0 = MZONE_RDTIME();
	const uint64_t T1 = T0 + (RTC_FREQ*(500/1000.0)); // 500 ms
	MZONE_WRTIMECMP(T1);

	

	while(1){

		// Message handler
		char msg[16]; if (MZONE_RECV(1, msg)) {
			if (strcmp("ping", msg)==0) MZONE_SEND(1, "pong");
			else if (strcmp("irq=0", msg)==0) __disable_irq();
			else if (strcmp("irq=1", msg)==0) __enable_irq();
			else if (strcmp("block", msg)==0) {volatile int i=0; while(1) i++; }
			else if (strcmp("loop",  msg)==0) {while(1) MZONE_YIELD();}
		}

		// Wait For Interrupt
		MZONE_WFI();

	}


	return 0;
}
