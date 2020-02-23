/* Copyright(C) 2018 Hex Five Security, Inc. - All Rights Reserved */

#include <string.h>	// strcmp()

#include "platform.h"
#include "multizone.h"
#include "owi_sequence.h"
#include "gpio_driver.h"

#define MAN_CMD_TIME 250*(RTC_FREQ/1000) // 250ms
#define KEEP_ALIVE_TIME 1*RTC_FREQ // 1 sec
#define LED_TIME 20*(RTC_FREQ/1000) //  20ms

void timer_handler(const uint64_t time);

void systick_handler(void) __attribute__ ((interrupt ("irq"))); 
void systick_handler(void){

	const uint64_t time = MZONE_RDTIME();  
	timer_handler(time);

}

static uint8_t CRC8(const uint8_t const bytes[]){

    const uint8_t generator = 0x1D;
    uint8_t crc = 0;

    for(int b=0; b<3; b++) {

        crc ^= bytes[b]; /* XOR-in the next input byte */

        for (int i = 0; i < 8; i++)
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ generator);
            else
                crc <<= 1;
    }

    return crc;
}

static uint32_t spi_rw(const uint32_t cmd){

	
	const uint8_t const bytes[] = {(uint8_t)cmd, (uint8_t)(cmd>>8), (uint8_t)(cmd>>16)};
	const uint32_t tx_data = bytes[0]<<24 | bytes[1]<<16 | bytes[2]<<8 | CRC8(bytes);

	uint32_t rx_data = 0;

	for (int i=32-1, bit; i>=0; i--){

		bit = (tx_data >> i) & 1U;
		
		if(bit){
			SPI_TDO_SET(SPI_TDO);
		}
		else{
			SPI_TDO_CLR(SPI_TDO);
		}

		SPI_TCK_LOW(SPI_TCK); volatile int w1=0; while(w1<5) w1++;
		SPI_TCK_HIGH(SPI_TCK); volatile int w2=0; while(w2<5) w2++;
		bit = SPI_TDI_BIT(SPI_TDI);
		rx_data = ( bit==1 ? rx_data |  (0x1 << i) : rx_data & ~(0x1 << i) );

	}

	return rx_data;
}

#define CMD_DUMMY 0xFFFFFF
#define CMD_STOP  0x000000

static volatile uint32_t usb_state = 0;
static volatile uint32_t man_cmd = CMD_STOP;

uint64_t task0(); // OWI Sequence
uint64_t task1(); // Manual cmd stop
uint64_t task2(); // Keep alive
uint64_t task3(); // LED off

static struct {
	uint64_t (*task)(void);
	uint64_t timecmp;
} timer[] = {{&task0, UINT64_MAX}, {&task1, UINT64_MAX}, {&task2, UINT64_MAX}, {&task3, UINT64_MAX}};

void timer_set(const int i, const uint64_t timecmp){

	timer[i].timecmp = timecmp;

	uint64_t timecmp_min = UINT64_MAX;
	for (int i=0; i<sizeof(timer)/sizeof(timer[0]); i++)
		timecmp_min = timer[i].timecmp < timecmp_min ? timer[i].timecmp : timecmp_min;

	MZONE_WRTIMECMP(timecmp_min);

}

void timer_handler(const uint64_t time){

	for (int i=0; i<sizeof(timer)/sizeof(timer[0]); i++)
		if(time >= timer[i].timecmp){
			timer_set(i, timer[i].task());
			break;
		}
}

uint64_t task0(){ // OWI sequence

	uint64_t timecmp = UINT64_MAX;

	if (usb_state==0x12670000){

		if (owi_sequence_next()!=-1){
			spi_rw(owi_sequence_get_cmd());
			timecmp = MZONE_RDTIME() + owi_sequence_get_ms()*RTC_FREQ/1000;
		}

	}

	return timecmp;

}

uint64_t task1(){ // Manual cmd stop
	spi_rw(man_cmd = CMD_STOP);
	return UINT64_MAX;
}

uint64_t task2(){ // Keep alive 1sec

	const uint64_t time = MZONE_RDTIME();

	// Send keep alive packet and check ret value
	const uint32_t rx_data = spi_rw(CMD_DUMMY);

    // Update USB state (0xFFFFFFFF no spi/usb adapter)
    if (rx_data != usb_state){
    	if (rx_data==0x12670000 && usb_state==0x0){
    		MZONE_SEND(1, "USB ID 0x12670000");
    	} else if (rx_data==0x0 && usb_state==0x12670000){
    		MZONE_SEND(1, "USB DISCONNECT");
    		owi_sequence_stop();
    	}
    	usb_state=rx_data;
    }

    // Turn on LED & start LED timer
    //GPIO_REG(GPIO_OUTPUT_VAL) |= LED;
    timer_set(3, time + LED_TIME);

	return time + KEEP_ALIVE_TIME;
}

uint64_t task3(){ // LED off
	//GPIO_REG(GPIO_OUTPUT_VAL) &= ~LED;
	return UINT64_MAX;
}

void msg_handler(const char *msg){

	if (strcmp("ping", msg)==0){
		MZONE_SEND(1, "pong");

	} else if (usb_state==0x12670000 && man_cmd==CMD_STOP){

		if (strcmp("stop", msg)==0) owi_sequence_stop_req();

		else if (!owi_sequence_is_running()){

			     if (strcmp("start", msg)==0) {owi_sequence_start(MAIN);   timer_set(0, 0);}
			else if (strcmp("fold",  msg)==0) {owi_sequence_start(FOLD);   timer_set(0, 0);}
			else if (strcmp("unfold",msg)==0) {owi_sequence_start(UNFOLD); timer_set(0, 0);}

			// Manual single-command adjustments
				 if (strcmp("q", msg)==0) man_cmd = 0x000001; // grip close
			else if (strcmp("a", msg)==0) man_cmd = 0x000002; // grip open
			else if (strcmp("w", msg)==0) man_cmd = 0x000004; // wrist up
			else if (strcmp("s", msg)==0) man_cmd = 0x000008; // wrist down
			else if (strcmp("e", msg)==0) man_cmd = 0x000010; // elbow up
			else if (strcmp("d", msg)==0) man_cmd = 0x000020; // elbow down
			else if (strcmp("r", msg)==0) man_cmd = 0x000040; // shoulder up
			else if (strcmp("f", msg)==0) man_cmd = 0x000080; // shoulder down
			else if (strcmp("t", msg)==0) man_cmd = 0x000100; // base clockwise
			else if (strcmp("g", msg)==0) man_cmd = 0x000200; // base counterclockwise
			else if (strcmp("y", msg)==0) man_cmd = 0x010000; // light on

			if (man_cmd != CMD_STOP){
				spi_rw(man_cmd);
				timer_set(1, MZONE_RDTIME() + MAN_CMD_TIME);
			}

		}

	}

}

int main(void)
{

	//volatile int w=0; while(1){w++;}
	//while(1) MZONE_YIELD();
	//while(1) MZONE_WFI();

    SPI_INIT(SPI_TDI, SPI_TCK, SPI_TDO);
	
	// Start task2: Hartbeat LED, USB status, Keep alive pkt
    timer_set(2, 0);

	while(1){

		// Message handler
		char msg[16]; if (MZONE_RECV(1, msg)) msg_handler(msg);

	    MZONE_WFI();

	}
}
