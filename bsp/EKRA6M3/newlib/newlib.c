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

        /* Write to specific pin's PFS register */
		R_PFS_REG(R_PFS_P613PFS) = 0x0;
        R_PFS_REG(R_PFS_P613PFS) = 0x5010000;

        /* Write to specific pin's PFS register */
        R_PFS_REG(R_PFS_P614PFS) = 0x0;
        R_PFS_REG(R_PFS_P614PFS) = 0x5010000;

    	/* Enable the SCI channel and reset the registers to their initial state. */
		MSTP_REG(R_SCI_SMR) = ~R_MSTP_MSTPCRB_MSTPB24_Msk;

		/* Initialize SCI registers as described in RA6M3 manual (34.3.7) */
		R_SCI7_REG8(R_SCI_SCR) = 0U;
		R_SCI7_REG8(R_SCI_SSR) = 0U;
		R_SCI7_REG8(R_SCI_SIMR1) = 0U;
		R_SCI7_REG8(R_SCI_SIMR2) = 0U;
		R_SCI7_REG8(R_SCI_SIMR3) = 0U;
		R_SCI7_REG16(R_SCI_CDR) = 0U;
		R_SCI7_REG8(R_SCI_DCCR) = SCI_UART_DCCR_DEFAULT_VALUE;

		/* Set the default level of the TX pin to 1. */
		R_SCI7_REG8(R_SCI_SPTR) = (uint8_t) (1U << SPTR_SPB2D_BIT) | SPTR_OUTPUT_ENABLE_MASK;
		
		/* Configure parity and stop bits. */
		R_SCI7_REG8(R_SCI_SMR) = (uint8_t) 0;       // parity = 0, stop_bits = 0
		R_SCI7_REG8(R_SCI_SCMR) = (uint8_t) SCI_UART_SCMR_DEFAULT_VALUE;
		R_SCI7_REG8(R_SCI_SPMR) = 0;
		
		R_SCI7_REG8(R_SCI_SNFR) = 0;
		R_SCI7_REG8(R_SCI_SEMR) = (SCI_UART_START_BIT_FALLING_EDGE & 1U) << 7;
		R_SCI7_REG8(R_SCI_BRR) = 64;
		R_SCI7_REG8(R_SCI_MDDR) = 0xFF;
		R_SCI7_REG8(R_SCI_SEMR) = (uint8_t) ((R_SCI7_REG8(R_SCI_SEMR) & ~(SCI_UART_SEMR_BAUD_SETTING_MASK)) |
									(0x40 & SCI_UART_SEMR_BAUD_SETTING_MASK));

		/* IRQ configure - ICU */
		R_ICU_REG(R_ICU_IELSR8) = R_EVENT_SCI7_RXI;

		R_SCI7_REG8(R_SCI_SCR) |= SCI_SCR_RE_MASK | SCI_SCR_RIE_MASK | SCI_SCR_TE_MASK;

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

		while( count<len && (R_SCI7_REG8(R_SCI_SSR) & R_SCI_SSR_RDRF_Msk) ){
			rxfifo = R_SCI7_REG8(R_SCI_RDR);
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

			while ((R_SCI7_REG8(R_SCI_SSR) & R_SCI_SSR_TDRE_Msk) == 0){;}

			R_SCI7_REG8(R_SCI_TDR) = (char) buff[i];

			if (buff[i] == '\n') {
				while ((R_SCI7_REG8(R_SCI_SSR) & R_SCI_SSR_TDRE_Msk) == 0){;}
				R_SCI7_REG8(R_SCI_TDR) = '\r';
			}
		}

		return len;

	}

	return -1;
}
