/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#define LED_INIT(_X_)                                                		\
{                                                                    		\
	    /* Enable PIO to control PIN8 of PIOC */                     		\
	    PIOC_REG(PIO_PER) |= (1<<_X_);                               		\
	    /* Enable the output on PIN8 line of PIOC */            			\
	    PIOC_REG(PIO_OER) |= (1<<_X_);                              		\
}

#define LED_SET(_X_)    	PIOC_REG(PIO_CODR) |= (1<<_X_)

#define LED_CLR(_X_)    	PIOC_REG(PIO_SODR) |= (1<<_X_)

#define LED_OUT(_X_)		(PIOC_REG(PIO_ODSR) & (1<<_X_)) != (1<<_X_)

#define BTN_INIT(_X_)                                                   	\
{                                                                       	\
	    PIOA_REG(PIO_IDR) = (1<<_X_);                           			\
	    /* Enable PULL-UP on PA11(SW0_PIN) of PIOA */                   	\
	    PIOA_REG(PIO_PUER) = (1<<_X_);                                		\
	    /* Enable DE-GLITCH & DEBOUNCE on PA11(SW0_PIN) of PIOA */     		\
	    PIOA_REG(PIO_IFER) = (1<<_X_);                               		\
	    PIOA_REG(PIO_IFSCER) = (1<<_X_);                              		\
	    /* Read interrupt status to clear pending */                      	\
	    PIOA_REG(PIO_ISR);                                                	\
	    PIOA_REG(PIO_IMR);                                                	\
	    /* Enable the input on PA11(SW0_PIN) of PIOA */           			\
	    PIOA_REG(PIO_ODR) = (1<<_X_);                               		\
	    PIOA_REG(PIO_PER) = (1<<_X_);                                   	\
	    /* Configure interrupt of PA11(SW0) as edge-detection event*/ 		\
	    PIOA_REG(PIO_AIMER) = (1<<_X_);                             		\
	    PIOA_REG(PIO_FELLSR) = (1<<_X_);                                	\
	    PIOA_REG(PIO_ESR) = (1<<_X_);                                   	\
	    /* Enable interrupt on input PA11(SW0_PIN) of PIOA */          		\
	    PIOA_REG(PIO_IER) = (1<<_X_);                              			\
}

#define BTN_IRQ_CLR()                                                  		\
{                                                                      		\
	/* Read interrupt status to clear pending */                       		\
	PIOA_REG(PIO_ISR);                                                 		\
	PIOA_REG(PIO_IMR);                                                 		\
}

#define SPI_INIT(_X_, _Y_, _Z_)                                   			\
{                                                                    		\
	/* Enable PIO to control PD11, PD27 of PIOD */                 			\
	PIOD_REG(PIO_PER) |= (1 << _Y_) | (1 << _X_);                			\
	/* Enable PIO to control PA6 of PIOA */                            		\
	PIOA_REG(PIO_PER) |= (1 << _Z_);                      					\
	/* Enable the output on PD27 and PA6 */                            		\
	PIOD_REG(PIO_OER) |= (1 << _Y_);                                 		\
	PIOA_REG(PIO_OER) |= (1 << _Z_);                                  		\
	/* Enable the input on PD11 of PIOD */                               	\
	PIOD_REG(PIO_ODR) |= (1 << _X_);                                 		\
	/* Enable the pull-up input on PD11 of PIOD */                   		\
	PIOD_REG(PIO_PUER) |= (1 << _X_);                                		\
}

#define SPI_TDO_SET(_X_)	PIOA_REG(PIO_SODR) |= (0x1 << _X_)

#define SPI_TDO_CLR(_X_)  	PIOA_REG(PIO_CODR) |= (0x1 << _X_)

#define SPI_TDI_BIT(_X_)	(PIOD_REG(PIO_PDSR) >> _X_) & 1U 

#define SPI_TCK_LOW(_X_)	PIOD_REG(PIO_SODR) |= (0x1 << _X_)
#define SPI_TCK_HIGH(_X_) 	PIOD_REG(PIO_CODR) |= (0x1 << _X_)

#define UART_IRQ_CLR()														\
{																			\
}

#define UART_IRQ_RX()		(USART1_REG(US_CSR) & US_CSR_RXRDY)


#endif
