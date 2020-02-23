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
		/* Enable the IOMUXC Clock */
		CCM_REG(CCM_CCGR4) |= (0x3 << CCM_CCGR4_CG1); //(iomuxc_clk_enable)
		/* GPIO_AD_B0_06 is configured as LPUART1_TX  */
		IOMUX_REG(SW_MUX_CTL_PAD_GPIO_AD_B0_06) = (0x2 << SW_MUX_CTL_MUX_MODE); //ALT6: LPUART1_TX of instance: gpio1
		IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_06) = 0x10B0;
		/* GPIO_AD_B0_07 is configured as LPUART1_RX  */
		IOMUX_REG(SW_MUX_CTL_PAD_GPIO_AD_B0_07) = (0x2 << SW_MUX_CTL_MUX_MODE); //ALT7: LPUART1_TX of instance: gpio1
		IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_07) = 0x10B0;

		CCM_REG(CCM_CSCDR1) &= ~CCM_CSCDR1_UART_CLK_PODF_MASK;
		CCM_REG(CCM_CSCDR1) &= ~CCM_CSCDR1_UART_CLK_SEL_MASK;

		/* Enable the UART Clock */
		CCM_REG(CCM_CCGR5) |= (0x3 << CCM_CCGR5_CG12); //(uartmuxc_clk_enable)
		/* write the sbr value to the BAUD registers */
		UART1_REG(UART_BAUD) = UART_BAUD_VAL;
		/* Set bit count and parity mode. */
		UART1_REG(UART_BAUD) &= ~UART_BAUD_M10_MASK;
		UART1_REG(UART_CTRL) = 0;
		UART1_REG(UART_WATER) = 0;

		/* Enable tx/rx FIFO */
		UART1_REG(UART_FIFO) |= (UART_FIFO_TXFE_MASK | UART_FIFO_RXFE_MASK);
		/* Flush FIFO */
		UART1_REG(UART_FIFO) |= (UART_FIFO_TXFLUSH_MASK | UART_FIFO_RXFLUSH_MASK);
		UART1_REG(UART_MODIR) = 0;

		UART1_REG(UART_STAT) |= UART_STAT_VAL;
		UART1_REG(UART_CTRL) = UART_CTRL_VAL;
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

		while( count<len && (UART1_REG(UART_WATER) & UART_WATER_RXCOUNT_MASK) ){
			rxfifo = UART1_REG(UART_DATA);
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

			while ((UART1_REG(UART_STAT) & UART_STAT_TDRE_MASK) == 0){;}

			UART1_REG(UART_DATA) = (char) buff[i];

			if (buff[i] == '\n') {
				while ((UART1_REG(UART_STAT) & UART_STAT_TDRE_MASK) == 0){;}
				UART1_REG(UART_DATA) = '\r';
			}
		}

		return len;

	}

	return -1;
}
