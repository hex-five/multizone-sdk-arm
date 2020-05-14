/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#include <fcntl.h>	// open()
#include <unistd.h> // read() write()
#include <string.h>	// strxxx()
#include <stdio.h>	// printf() sprintf()
#include <stdlib.h> // qsort() strtoul()
#include <limits.h> // UINT_MAX ULONG_MAX
#include <math.h> // round()

#include <unistd.h>

#include <platform.h>
#include "multizone.h"
#include "gpio_driver.h"

#define BUFFER_SIZE 16
static struct{
	char data[BUFFER_SIZE];
	volatile int p0; // read
	volatile int p1; // write
} buffer;

static char inputline[32+1]="";


#define CMD_LINE_SIZE 32
#define MSG_SIZE 4


// ------------------------------------------------------------------------
void hardfault_handler(void) __attribute__ ((interrupt ("irq"))); 
void hardfault_handler(void){
// ------------------------------------------------------------------------

	register uint32_t *sp __asm ("sp");

	const uint32_t pc = *(sp+10);

	printf("Hard fault : 0x%08x \n", pc);

	printf("Press any key to restart ... \n");
	char c='\0'; while(read(0, &c, 1) ==0 ){;} __asm volatile("b reset_handler");

}

// ------------------------------------------------------------------------
void memmanage_handler(void) __attribute__ ((interrupt ("irq"))); 
void memmanage_handler(void){
// ------------------------------------------------------------------------

	register uint32_t *sp __asm ("sp");

	uint32_t pc = *(sp+10);

	printf("Memory protection fault : 0x%08x \n", pc);

	printf("Press any key to restart ... \n");
	char c='\0'; while(read(0, &c, 1) ==0 ){;} __asm volatile("b reset_handler");

}

// ------------------------------------------------------------------------
void busfault_handler(void) __attribute__ ((interrupt ("irq"))); 
void busfault_handler(void){
// ------------------------------------------------------------------------

	register uint32_t *sp __asm ("sp");

	const uint32_t pc = *(sp+10);

	printf("Bus fault : 0x%08x \n", pc);

	printf("Press any key to restart ... \n");
	char c='\0'; while(read(0, &c, 1) ==0 ){;} __asm volatile("b reset_handler");

}

void usagefault_handler(void) __attribute__ ((interrupt ("irq"))); 
void usagefault_handler(void){

	register uint32_t *sp __asm ("sp");

	const uint32_t pc = *(sp+10);

	printf("Usage fault : 0x%08x \n", pc);

	printf("Press any key to restart ... \n");
	char c='\0'; while(read(0, &c, 1) ==0 ){;} __asm volatile("b reset_handler");

}

void systick_handler(void) __attribute__ ((interrupt ("irq"))); 
void systick_handler(void){

	const uint64_t T = MZONE_RDTIME();

	write(1, "\e7", 2); 	// save curs pos
	write(1, "\e[r", 3); 	// scroll all screen
	write(1, "\e[2M", 4); 	// scroll up up
	write(1, "\e8", 2);   	// restore curs pos
	write(1, "\e[2A", 4); 	// curs up 2 lines
	write(1, "\e[2L", 4); 	// insert 2 lines

	printf("\rZ1 > timer expired : %lu!\n", (uint32_t)(T*(1000.0/RTC_FREQ)));

	write(1, "\e8", 2);   	// restore curs pos

}

void uart_handler(void) __attribute__ ((interrupt ("irq"))); 
void uart_handler(void){

	UART_IRQ_CLR();
	if(UART_IRQ_RX()) {
		if (buffer.p0==buffer.p1) {buffer.p0=0; buffer.p1=0;}
		read(0, &buffer.data[buffer.p1++], 1);
		if (buffer.p1 > BUFFER_SIZE-1) buffer.p1 = BUFFER_SIZE-1;
	}
}


void print_cpu_info(void) {


	/* SCB->CPUID Special register access (read-only) */
	//uint32_t cpuid = LOAD_SCB(SCS_SCB_CPUID);			// mzone api
	uint32_t cpuid = *(volatile uint32_t *)SCB_CPUID;	// trap&emul

	/* Decoding SCB->CPUID */
	uint16_t partno = (cpuid&0xfff0)>>4;

	const char *partno_str = (partno==0xC23 ? "Cortex-M3.\n\0" : \
				  partno==0xC24 ? "Cortex-M4.\n\0" : \
				  partno==0xC27 ? "Cortex-M7.\n\0" : "Undefined.\n\0");

	printf("Implementer    : 0x%X, Arm.\n", (cpuid >> 24));
	printf("Variant        : 0x%X, Revision %d.\n", ((cpuid&0x00ffffff)>>20),((cpuid&0x00ffffff)>>20));
	printf("PartNo         : 0x%X, %s", partno, partno_str);
	printf("Revision       : 0x%X, Patch %d.\n", ((cpuid&0x7)),((cpuid&0x7)));

}


int cmpfunc(const void* a , const void* b){

    const int ai = *(const int* )a;
    const int bi = *(const int* )b;
    return ai < bi ? -1 : ai > bi ? 1 : 0;
}


void print_stats(void){

	const int COUNT = 10+1; // odd values for median
	#define MHZ (CPU_FREQ/1000000)

	int cycles[COUNT], instrs[COUNT];

	for (int i=0; i<COUNT; i++){	
		
		volatile unsigned int C1 = MZONE_RDCYCCNT();
		MZONE_YIELD();
		volatile unsigned int C2 = MZONE_RDCYCCNT();

		cycles[i] = C2-C1; instrs[i] = cycles[i]>>1;
	}

	int max_cycle = 0;
	for (int i=0; i<COUNT; i++)	max_cycle = (cycles[i] > max_cycle ? cycles[i] : max_cycle);
	char str[16]; sprintf(str, "%lu", max_cycle); const int col_len = strlen(str);


	for (int i=0; i<COUNT; i++)
		printf("%*d instr %*d cycles %*d us \n", col_len, instrs[i], col_len, cycles[i], col_len-1, cycles[i]/MHZ);

	qsort(cycles, COUNT, sizeof(int), cmpfunc);
	qsort(instrs, COUNT, sizeof(int), cmpfunc);

	printf("-----------------------------------------\n");
	int min = instrs[0], med = instrs[COUNT/2], max = instrs[COUNT-1];
	printf("instrs  min/med/max = %d/%d/%d \n", min, med, max);
		min = cycles[0], med = cycles[COUNT/2], max = cycles[COUNT-1];
	printf("cycles  min/med/max = %d/%d/%d \n", min, med, max);
	printf("time    min/med/max = %d/%d/%d us \n", min/MHZ, med/MHZ, max/MHZ);

	const unsigned int k_cycles  = MZONE_RDKCYCCNT();
	const unsigned int k_instr   = MZONE_RDKINSTR();
	const unsigned int irq_instr = 0;
	const unsigned int irq_cycle = 0;

	// Kernel stats - may not be available (#ifdef STATS)
	if (k_cycles>0){
		const unsigned int irq_instr = MZONE_RDKINSTR_IRQ();
		const unsigned int irq_cycle = MZONE_RDKCYCCNT_IRQ();

		printf("\n");
		printf("Kernel\n");
		printf("-----------------------------------------\n");
		printf("instrs = %lu \n", k_instr);
		printf("cycles = %lu \n", k_cycles);
		printf("time   = %lu us\n", k_cycles/MHZ);
		printf("-----------------------------------------\n");
		printf("irq lat instrs = %lu \n", irq_instr);
		printf("irq lat cycles = %lu \n", irq_cycle);
		printf("time           = %lu us\n", irq_cycle/MHZ);
	}

}


void print_mpu(void){


	/* RBAR|RASR Masks */
	#define RBAR_ADDR	 		0xFFFFFFE0
	#define RBAR_REGION	 		0xF
	#define RASR_AP_XN	 		0x17000000 	//clear mask
	#define RASR_AP_XN_NA 	 	0x11000000 	//---  
	#define RASR_AP_XN_R 	 	0x12000000 	//r-- 
	#define RASR_AP_XN_X 	 	0x01000000 	//--x 
	#define RASR_AP_XN_RW 	 	0x13000000 	//rw- 
	#define RASR_AP_XN_RX 	 	0x02000000 	//r-x 
	#define RASR_AP_XN_RWX 	 	0x03000000 	//rwx
	#define RASR_SIZE	 		0x3E


	uint32_t mpu_config[MPU_REGIONS*2];

	/* SCB->MPU_TYPE Special register access (read-only) */
	uint32_t mpu_regions = *(volatile uint32_t *)MPU_TYPE;
	mpu_regions = ((mpu_regions & 0x0000FF00) >> 8);

	for(int i=0, j=0; i<mpu_regions; i++, j=j+2)
	{
		mpu_config[j] = LOAD_MPURBAR(i);
		mpu_config[j+1] = LOAD_MPURASR(i);
	}

	printf("\n");
	for(int i=0; i<(16); i+=2)
	{
		uint8_t  region_n = (mpu_config[i] & RBAR_REGION);
		uint32_t start = (mpu_config[i] & RBAR_ADDR);
		uint32_t end = ((mpu_config[i+1] & RASR_SIZE) >> 1);
		char *rwx = ((end) ==  0)  ? "---" : \
				((mpu_config[i+1] & RASR_AP_XN) ==  RASR_AP_XN_NA)  ? "---" : \
			    	((mpu_config[i+1] & RASR_AP_XN) ==  RASR_AP_XN_R)   ? "r--" : \
			    	((mpu_config[i+1] & RASR_AP_XN) ==  RASR_AP_XN_X)   ? "--x" : \
			    	((mpu_config[i+1] & RASR_AP_XN) ==  RASR_AP_XN_RW)  ? "rw-" : \
			    	((mpu_config[i+1] & RASR_AP_XN) ==  RASR_AP_XN_RX)  ? "r-x" : \
			    	((mpu_config[i+1] & RASR_AP_XN) ==  RASR_AP_XN_RWX) ? "rwx" : "ERR";
		uint32_t size = (1 << (end+1));

		if(size < 32) size =0;
		else end = (size + start) - 1;

		if(end != 0x0)
			printf("0x%08X 0x%08X %s \n", start, end, rwx);
	}
}



void msg_handler() {

	// Message handler
	for (int zone=2; zone<=4; zone++){

		char msg[16];

		if (MZONE_RECV(zone, msg)) {

			if (strcmp("ping", msg) == 0)
				MZONE_SEND(zone, "pong");

			else {
				write(1, "\e7\e[2K", 6);   // save curs pos & clear entire line
				printf("\rZ%d > %.16s\n", zone, msg);
				write(1, "\nZ1 > %s", 6); write(1, inputline, strlen(inputline));
				write(1, "\e8\e[2B", 6);   // restore curs pos & curs down 2x
			}
		}

	}

}


void cmd_handler(){

	char * tk1 = strtok (inputline, " ");
	char * tk2 = strtok (NULL, " ");
	char * tk3 = strtok (NULL, " ");

	if (tk1 == NULL) tk1 = "help";

	// --------------------------------------------------------------------
	if (strcmp(tk1, "load")==0){
	// --------------------------------------------------------------------
		if (tk2 != NULL){
			uint8_t data = 0x00;
			const unsigned long addr = strtoull(tk2, NULL, 16);
			__asm volatile ("ldrb %0, [%1]" : "+r"(data) : "r"(addr));
			printf("0x%08x : 0x%02x \n", (unsigned int)addr, data);
		} else printf("Syntax: load address \n");

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "store")==0){
	// --------------------------------------------------------------------
		if (tk2 != NULL && tk3 != NULL){
			const uint32_t data = (uint32_t)strtoul(tk3, NULL, 16);
			const unsigned long addr = strtoull(tk2, NULL, 16);

			if ( strlen(tk3) <=2 )
				__asm volatile ("strb %0, [%1]" : : "r"(data), "r"(addr));
			else if ( strlen(tk3) <=4 )
				__asm volatile ("strh %0, [%1]" : : "r"(data), "r"(addr));
			else
				__asm volatile ("str %0, [%1]" : : "r"(data), "r"(addr));
			
			printf("0x%08x : 0x%02x \n", (unsigned int)addr, (unsigned int)data);
		} else printf("Syntax: store address data \n");

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "exec")==0){
	// --------------------------------------------------------------------
		if (tk2 != NULL){
			const unsigned long addr = strtoull(tk2, NULL, 16);
			__asm volatile( "bx %0" : : "r"(addr));
		} else printf("Syntax: exec address \n");

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "send")==0){
	// --------------------------------------------------------------------
		if (tk2 != NULL && tk2[0]>='1' && tk2[0]<='4' && tk3 != NULL){
			char msg[16]; strncpy(msg, tk3, 16);
			if (!MZONE_SEND( tk2[0]-'0', msg) )
				printf("Error: Inbox full.\n");
		} else printf("Syntax: send {1|2|3|4} message \n");

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "recv")==0){
	// --------------------------------------------------------------------
		if (tk2 != NULL && tk2[0]>='1' && tk2[0]<='4'){
			char msg[16];
			if (MZONE_RECV(tk2[0]-'0', msg))
				printf("msg : %.16s\n", msg);
			else
				printf("Error: Inbox empty.\n");
		} else printf("Syntax: recv {1|2|3|4} \n");

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "yield")==0){
	// --------------------------------------------------------------------
		const unsigned long C1 = MZONE_RDCYCCNT();
		MZONE_YIELD();
		const unsigned long C2 = MZONE_RDCYCCNT();
		const int TC = (C2-C1)/(CPU_FREQ/1000000);
		printf( (TC>0 ? "yield : elapsed time %dus \n" : "yield : n/a \n"), TC);

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "timer")==0){
	// --------------------------------------------------------------------
		if (tk2 != NULL){
			const uint64_t ms = abs(strtoull(tk2, NULL, 10));
			const uint64_t T0 = MZONE_RDTIME();
			const uint64_t T1 = T0 + (RTC_FREQ*(ms/1000.0));
			MZONE_WRTIMECMP(T1);
		
			printf("timer set to T0=%lu ms, T1=%lu ms\n", (unsigned long)(T0*1000.0/RTC_FREQ), (unsigned long)(T0*1000.0/RTC_FREQ)+ms);
		} else printf("Syntax: timer ms \n");

	// --------------------------------------------------------------------
	} else if (strcmp(tk1, "stats")==0)	print_stats();
	// --------------------------------------------------------------------

	// --------------------------------------------------------------------
	else if (strcmp(tk1, "restart")==0) __asm volatile ("b reset_handler");
	// --------------------------------------------------------------------

	// --------------------------------------------------------------------
	else if (strcmp(tk1, "mpu")==0) print_mpu();
	// --------------------------------------------------------------------

	else printf("Commands: yield send recv mpu load store exec stats timer restart \n");

}


int readline() {


	static int p=0;
	static int esc=0;
	static char history[8][sizeof(inputline)]={"","","","","","","",""}; static int h=-1;

	while ( buffer.p1>buffer.p0 || esc!=0 ) {
		if(buffer.p1>buffer.p0) {
			const char c = buffer.data[buffer.p0++];

			if (c=='\e'){
				esc=1;

			} else if (esc==1 && c=='['){
				esc=2;

			} else if (esc==2 && c=='3'){
				esc=3;

			} else if (esc==3 && c=='~'){ // del key
				for (int i=p; i<strlen(inputline); i++) inputline[i]=inputline[i+1];
				write(1, "\e7", 2); // save curs pos
				write(1, "\e[K", 3); // clear line from curs pos
				write(1, &inputline[p], strlen(inputline)-p);
				write(1, "\e8", 2); // restore curs pos
				esc=0;

			} else if (esc==2 && c=='C'){ // right arrow
				esc=0;
				if (p < strlen(inputline)){
					p++;
					write(1, "\e[C", 3);
				}

			} else if (esc==2 && c=='D'){ // left arrow
				esc=0;
				if (p>0){
					p--;
					write(1, "\e[D", 3);
				}

			} else if (esc==2 && c=='A'){ // up arrow (history)
				esc=0;
				if (h<8-1 && strlen(history[h+1])>0){
					h++;
					strcpy(inputline, history[h]);
					write(1, "\e[2K", 4); // 2K clear entire line - cur pos dosn't change
					write(1, "\rZ1 > ", 6);
					write(1, inputline, strlen(inputline));
					p=strlen(inputline);

				}

			} else if (esc==2 && c=='B'){ // down arrow (history)
				esc=0;
				if (h>0 && strlen(history[h-1])>0){
					h--;
					strcpy(inputline, history[h]);
					write(1, "\e[2K", 4); // 2K clear entire line - cur pos dosn't change
					write(1, "\rZ1 > ", 6);
					write(1, inputline, strlen(inputline));
					p=strlen(inputline);
				}

			} else if ((c=='\b' || c=='\x7f') && p>0 && esc==0){ // backspace
				p--;
				for (int i=p; i<strlen(inputline); i++) inputline[i]=inputline[i+1];
				write(1, "\e[D", 3);
				write(1, "\e7", 2);
				write(1, "\e[K", 3);
				write(1, &inputline[p], strlen(inputline)-p);
				write(1, "\e8", 2);

			} else if (c>=' ' && c<='~' && p < sizeof(inputline)-1 && esc==0){
				for (int i = sizeof(inputline)-1-1; i > p; i--) inputline[i]=inputline[i-1]; // make room for 1 ch
				inputline[p]=c;
				write(1, "\e7", 2); // save curs pos
				write(1, "\e[K", 3); // clear line from curs pos
				write(1, &inputline[p], strlen(inputline)-p); p++;
				write(1, "\e8", 2); // restore curs pos
				write(1, "\e[C", 3); // move curs right 1 pos

			} else if (c=='\r') {
				p=0; esc=0;
				write(1, "\n", 1);
				for (int i = sizeof(inputline)-1; i > 0; i--) if (inputline[i]==' ') inputline[i]='\0'; else break;

				if (strlen(inputline)>0 && strcmp(inputline, history[0])!=0){
					for (int i = 8-1; i > 0; i--) strcpy(history[i], history[i-1]);
					strcpy(history[0], inputline);
				}
				h = -1;

				return 1;

			} else esc=0;
		}
	}

	return 0;

}

// ------------------------------------------------------------------------
int main (void) {

	//volatile int w=0; while(1){w++;}
	//while(1) MZONE_YIELD();
	//while(1) MZONE_WFI();

	open("UART", 0, 0);
	STORE_NVICISER(UART_IRQn);

	printf("\e[2J\e[H"); // clear terminal screen
	printf("=====================================================================\n");
	printf("      	             Hex Five MultiZone® Security                    \n");
	printf("    Copyright© 2020 Hex Five Security, Inc. - All Rights Reserved    \n");
	printf("=====================================================================\n");
	printf("This version of MultiZone® Security is meant for evaluation purposes \n");
	printf("only. As such, use of this software is governed by the Evaluation    \n");
	printf("License. There may be other functional limitations as described in   \n");
	printf("the evaluation SDK documentation. The commercial version of the      \n");
	printf("software does not have these restrictions.                           \n");
	printf("=====================================================================\n");

    print_cpu_info();

	write(1, "\n\rZ1 > ", 7);

    while(1){

		if (readline()){
			cmd_handler(); //printf("%s\n", inputline);
			write(1, "\n\rZ1 > ", 7);
			inputline[0]='\0';
		}

		msg_handler();

		MZONE_WFI();

	}

} // main()
