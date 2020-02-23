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
		/* Peripheral clock enable */
		RCC_REG(RCC_APB1ENR) |= RCC_APB1ENR_USART3EN;
		RCC_REG(RCC_AHB1ENR) |= RCC_AHB1ENR_GPIODEN;
		/**UART GPIO Configuration  
		 *	UART_RX
		 *	UART_TX 
		*/

		/* Configure the GPIO UART_RX */
		GPIOD_REG(GPIO_OSPEEDR) &= ~(GPIO_OSPEEDER_OSPEEDR0 << (UART_RX_OFFSET * 2));
		GPIOD_REG(GPIO_OSPEEDR) |= (GPIO_SPEED_FREQ_VERY_HIGH << (UART_RX_OFFSET * 2));

		GPIOD_REG(GPIO_MODER) &= ~(GPIO_MODER_MODER0 << (UART_RX_OFFSET * 2));
		GPIOD_REG(GPIO_MODER) |= ((GPIO_MODE_ALTERNATE) << (UART_RX_OFFSET * 2));

		GPIOD_REG(GPIO_OTYPER) &= ~(GPIO_OTYPER_OT_0 << UART_RX_OFFSET);
		GPIOD_REG(GPIO_OTYPER) |= (((GPIO_OUTPUT_PUSHPULL & GPIO_OUTPUT_TYPE) >> 4) << UART_RX_OFFSET);

		GPIOD_REG(GPIO_AFR1) &= ~(GPIO_AFRH_AFRH0 << ((UART_RX_OFFSET - 8U) * 4U)),
		GPIOD_REG(GPIO_AFR1) |= (GPIO_AF_7 << ((UART_RX_OFFSET - 8U) * 4U));

		/* Configure the GPIO UART_TX */
		GPIOD_REG(GPIO_OSPEEDR) &= ~(GPIO_OSPEEDER_OSPEEDR0 << (UART_TX_OFFSET * 2));
		GPIOD_REG(GPIO_OSPEEDR) |= (GPIO_SPEED_FREQ_VERY_HIGH<< (UART_TX_OFFSET * 2));

		GPIOD_REG(GPIO_MODER) &= ~(GPIO_MODER_MODER0 << (UART_TX_OFFSET * 2));
		GPIOD_REG(GPIO_MODER) |= ((GPIO_MODE_ALTERNATE) << (UART_TX_OFFSET * 2));

    	GPIOD_REG(GPIO_OTYPER) &= ~(GPIO_OTYPER_OT_0 << UART_TX_OFFSET) ;
	    GPIOD_REG(GPIO_OTYPER) |= (((GPIO_OUTPUT_PUSHPULL & GPIO_OUTPUT_TYPE) >> 4) << UART_RX_OFFSET);

  		GPIOD_REG(GPIO_AFR1) &= ~(GPIO_AFRH_AFRH0 << ((UART_TX_OFFSET - 8U) * 4U)),
        GPIOD_REG(GPIO_AFR1) |= (GPIO_AF_7 << ((UART_TX_OFFSET - 8U) * 4U));

		/* Configure the USART3 */
		USART3_REG(USART_CR1) = USART3_REG(USART_CR1) & ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE | USART_CR1_OVER8)
								 | (USART_DATAWIDTH_8B | USART_PARITY_NONE | USART_DIRECTION_TX_RX | USART_OVERSAMPLING_16);

		USART3_REG(USART_CR2) &= ~(USART_CR2_STOP);
		USART3_REG(USART_CR2) |= USART_STOPBITS_1;

		USART3_REG(USART_CR3) &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
		USART3_REG(USART_CR3) |= USART_HWCONTROL_NONE;

    	USART3_REG(USART_BRR) = (uint16_t)(((USART3_PERIPHCLK) + ((USART_BAUDRATE)/2U))/(USART_BAUDRATE));
	
		/* Configure AsyncMode */
		USART3_REG(USART_CR2) &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
		USART3_REG(USART_CR3) &= ~(USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL);

		/* Enable USART */
		USART3_REG(USART_CR1) |= (USART_CR1_RXNEIE);
		USART3_REG(USART_CR1) |= (USART_CR1_UE);

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

		while( count<len && (USART3_REG(USART_ISR) & USART_ISR_RXNE) ){
			rxfifo = USART3_REG(USART_RDR);
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

			while ((USART3_REG(USART_ISR) & USART_ISR_TXE) == 0){;}

			USART3_REG(USART_TDR) = (char) buff[i];

			if (buff[i] == '\n') {
				while ((USART3_REG(USART_ISR) & USART_ISR_TXE) == 0){;}
				USART3_REG(USART_TDR)= '\r';
			}
		}

		return len;

	}

	return -1;
}

// open("UART", 0, 0); write(1, "Ok >\n", 5); char c='\0'; while(1) if ( read(0, &c, 1) >0 ) write(1, &c, 1);
