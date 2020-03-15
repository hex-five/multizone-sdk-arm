/* Copyright(C) 2018 Hex Five Security, Inc. - All Rights Reserved */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include <platform.h>

// ----------------------------------------------------------------------------
int _close(int file) {
// ----------------------------------------------------------------------------

	return -1;
}

// ----------------------------------------------------------------------------
int _fstat(int file, struct stat *st) {
// ----------------------------------------------------------------------------

	st->st_mode = S_IFCHR;
	return 0;
}

// ----------------------------------------------------------------------------
void * _sbrk(int incr) {
// ----------------------------------------------------------------------------

	extern char _end[];
	extern char _heap_end[];
	static char *_heap_ptr = _end;

	if ((_heap_ptr + incr < _end) || (_heap_ptr + incr > _heap_end))
		return  (void *) -1;

	_heap_ptr += incr;
	return _heap_ptr - incr;
}

// ----------------------------------------------------------------------------
int _isatty(int file) {
// ----------------------------------------------------------------------------

	return (file == STDIN_FILENO || file == STDOUT_FILENO || file == STDERR_FILENO) ? 1 : 0;

}

// ----------------------------------------------------------------------------
int _lseek(int file, off_t ptr, int dir) {
// ----------------------------------------------------------------------------

	return 0;
}

// ----------------------------------------------------------------------------
int _open(const char* name, int flags, int mode) {
// ----------------------------------------------------------------------------

	if (strcmp(name, "UART")==0){

		/* connect port to USART0_Tx - PA.09 */
		//GPIOA_REG(GPIO_CTL1) = (0xB << 4);
		GPIOA_REG(GPIO_CTL1) = ((GPIO_CTL_CTL_AFIOPP|GPIO_CTL_MD_O50MHZ) << 4);

		/* connect port to USART0_Rx - PA.10 */
		GPIOA_REG(GPIO_CTL1) |= (GPIO_CTL_CTL_IFI << 8);

		/* 
		* configure USART baud rate value 
		* Assuming PCLK = SYS_CLK = 8MHz and BR=115200
		* USARTDIV = PLCK / (16 * BR) = 8000000 / (16*115200) = 4.340277778
		* INTDIV = INT(USARTDIV) = 4
		* FRADIV = INT(16 * REMAINING(INTDIV)) = INT(16*0.340277778) = 5
		* USART_BAUD = (INTDIV << 4) | (FRADIV) = 0x45
		*/
		USART0_REG(USART_BAUD) = 0x45;

		/* configure USART receiver */
		USART0_REG(USART_CTL0) &= ~(USART_CTL0_REN); 
		USART0_REG(USART_CTL0) |= (USART_CTL0_REN);

		/* configure USART transmitter */
		USART0_REG(USART_CTL0) &= ~(USART_CTL0_TEN); 
		USART0_REG(USART_CTL0) |= (USART_CTL0_TEN);

		/* enable USART */
		USART0_REG(USART_CTL0) |= (USART_CTL0_UEN);

		/* enable USART interrupt */
		USART0_REG(USART_CTL0) |= (USART_CTL0_RBNEIE);
		
		return 0;
	}

	return -1;
}

// ----------------------------------------------------------------------------
int _read(int file, char *ptr, size_t len) {
// ----------------------------------------------------------------------------
	if (isatty(file)) {

		ssize_t count = 0;
		int rxfifo = -1;

		while( count<len && (USART0_REG(USART_STAT0) & USART_STAT0_RBNE) ){
			rxfifo = USART0_REG(USART_DATA);
			*ptr++ = (char)rxfifo;
			count++;
		}

		return count;

	}
	return -1;
}

// ----------------------------------------------------------------------------
size_t _write(int file, const void *ptr, size_t len) {
// ----------------------------------------------------------------------------

	if (isatty(file)) {

		const uint8_t * buff = (uint8_t *)ptr;

		for (size_t i = 0; i < len; i++) {

			while ((USART0_REG(USART_STAT0) & USART_STAT0_TBE) == 0){;}

			USART0_REG(USART_DATA) = (char) buff[i];

			if (buff[i] == '\n') {
				while ((USART0_REG(USART_STAT0) & USART_STAT0_TBE) == 0){;}
				USART0_REG(USART_DATA) = '\r';
			}
		}

		return len;

	}

	return -1;
}
