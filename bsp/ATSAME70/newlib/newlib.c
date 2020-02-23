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

    	uint32_t tmp;
		
		tmp = EFC_REG(EEFC_FMR);
		tmp &= ~EEFC_FMR_FWS_Msk;
		tmp |= EEFC_FMR_FWS(CONF_EFC_WAIT_STATE);
		EFC_REG(EEFC_FMR) = tmp;

		/*_pmc_init*/
		uint32_t data = 0;

		data = PMC_REG(CKGR_MOR) & ~CKGR_MOR_MOSCXTBY;
		data |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCXTST(62);
    	PMC_REG(CKGR_MOR) = data;
    	while (!((PMC_REG(PMC_SR) & PMC_SR_MOSCXTS) > 0)) {
			/* Wait until the XTAL to stabilize */
		}

    	PMC_REG(CKGR_MOR) |= (CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL);

		/* Peripheral clock enable */
		data = CKGR_PLLAR_MULA(CONF_PLLACK_MUL - 1) | CKGR_PLLAR_DIVA(CONF_PLLACK_DIV) | CKGR_PLLAR_PLLACOUNT(PLL_COUNT);
		/* Stop PLL first */
		tmp = PMC_REG(CKGR_PLLAR);
		tmp &= ~CKGR_PLLAR_MULA_Msk;
		tmp |= CKGR_PLLAR_MULA(0);
		PMC_REG(CKGR_PLLAR) = tmp;

    	PMC_REG(CKGR_PLLAR) =  (CKGR_PLLAR_ONE | data);
		while (!((PMC_REG(PMC_SR) & PMC_SR_LOCKA) > 0)) {
		  	/* Wait until PLLACK stabilize */
		}

		tmp = PMC_REG(PMC_MCKR);
		tmp &= ~PMC_MCKR_PRES_Msk;
		tmp |= PMC_MCKR_PRES(CONF_MCKR_PRESC);
		PMC_REG(PMC_MCKR) = tmp;
		while (!(PMC_REG(PMC_SR) & PMC_SR_MCKRDY) > 0) {
			/* Wait until master clock is ready */
		}

		tmp = PMC_REG(PMC_MCKR);
		tmp &= ~PMC_MCKR_MDIV_Msk;
		tmp |= PMC_MCKR_MDIV(CONF_MCK_DIV);

		PMC_REG(PMC_MCKR) = tmp;
    	while (!(PMC_REG(PMC_SR) & PMC_SR_MCKRDY) > 0) {
			/* Wait until master clock is ready */
		}

		tmp =  PMC_REG(PMC_MCKR);
		tmp &= ~PMC_MCKR_CSS_Msk;
		tmp |= PMC_MCKR_CSS(CONF_CLK_GEN_MCKR_SRC);
		PMC_REG(PMC_MCKR)= tmp;
    	while (!(PMC_REG(PMC_SR) & PMC_SR_MCKRDY) > 0) {
			/* Wait until master clock is ready */
		}

		PMC_REG(PMC_PCER0) = 1 << ID_USART1;

		/**UART GPIO Configuration  
		 *	UART_RX
		 *	UART_TX 
		*/
		PIOA_REG(PIO_ABCDSR0) &= ~(1U << USART1_RX_PIN);
		PIOA_REG(PIO_ABCDSR1) &= ~(1U << USART1_RX_PIN);
		PIOA_REG(PIO_PDR) = 1U << USART1_RX_PIN;

		MATRIX_REG(CCFG_SYSIO) |= 1U << USART1_TX_PIN;

		PIOB_REG(PIO_ABCDSR0) |= 1U << USART1_TX_PIN;
		PIOB_REG(PIO_ABCDSR1) |= 1U << USART1_TX_PIN;
		PIOB_REG(PIO_PDR) = 1U << USART1_TX_PIN;

		/* Configure the USART driver */
    		/* Disable the Write Protect. */
		USART1_REG(US_WPMR) = US_WPMR_WPKEY_PASSWD;
		/* Reset registers that could cause unpredictable behavior after reset. */
		USART1_REG(US_MR) = 0x0;
		USART1_REG(US_RTOR) = 0x0;
    	USART1_REG(US_TTGR) = 0x0;

		/* Disable and reset TX and RX. */
		USART1_REG(US_CR) = (US_CR_RSTRX | US_CR_RXDIS | US_CR_RSTTX | US_CR_TXDIS);
		/* Reset status bits. */
		USART1_REG(US_CR) = US_CR_RSTSTA;
		/* Turn off RTS and DTR if exist. */
		USART1_REG(US_CR) = US_CR_USART_RTSDIS;

		USART1_REG(US_MR) =  US_MR_Val; //
		USART1_REG(US_BRGR) = (US_BRGR_Val);
	
		USART1_REG(US_CR) = (US_CR_RXEN | US_CR_TXEN);

		USART1_REG(US_IER) = US_IMR_RXRDY;
    	
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

		while( count<len && (USART1_REG(US_CSR) & US_CSR_RXRDY) ){
			rxfifo = USART1_REG(US_RHR);
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
	        	while(!((USART1_REG(US_CSR) & US_CSR_TXRDY) > 0)) {;}

			USART1_REG(US_THR) = (char) buff[i];

			if (buff[i] == '\n') {
				while(!((USART1_REG(US_CSR) & US_CSR_TXRDY) > 0)) {;}
				USART1_REG(US_THR) = (char) '\r';
			}
		}

		return len;

	}

	return -1;
}