/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#define LED_INIT(_X_)                                                           \
{		                                                                        \
    /* Port output control register - Output (10Mhz) & Push-Pull */             \
    GPIOC_REG(GPIO_CTL0) = ( GPIO_CTL_MD_O10MHZ << (4*_X_) );                   \
    /* Port output control register - Set output high */                        \
    GPIOC_REG(GPIO_OCTL) = ( GPIO_OCTL_OH << _X_ );                             \
}

#define LED_SET(_X_)	GPIOC_REG(GPIO_BOP) = ( GPIO_BOP_SET << _X_ );

#define LED_CLR(_X_)	GPIOC_REG(GPIO_BC) = ( GPIO_BC_CLEAR << _X_ );

#define LED_OUT(_X_)	(GPIOC_REG(GPIO_OCTL) & 1 ) == 1

#define BTN_INIT(_X_)                                                          	\
{                                                                               \
	/* Configure button pin as input */                                         \
	GPIOB_REG(GPIO_CTL1) = (GPIO_CTL_CTL_IFI << ((_X_-8)*4));                	\
	/* Select EXTI source */                                                    \
	AFIO_REG(AFIO_EXTISS3) = AFIO_EXTI14SS_PB14;                                \
	/* Configure EXTI line */                                                   \
	EXTI_REG(EXTI_INTEN) = (1 << _X_);                                          \
	EXTI_REG(EXTI_RTEN) = 0;                                                    \
	EXTI_REG(EXTI_FTEN) = (1 << _X_);                                           \
	EXTI_REG(EXTI_PD) = (1 << _X_);                                             \
}

#define BTN_IRQ_CLR()                                                           \
{                                                                               \
    EXTI_REG(EXTI_PD) = (1 << BTN0_PIN);                                        \
}

/* 
* SPI_INIT(SPI_TDI, SPI_TCK, SPI_TDO); 
* SPI_TDI = PE11, SPI_TCK = PE13, SPI_TDO = PE15
*/
#define SPI_INIT(_X_, _Y_, _Z_)                                                 \
{                                                                               \
	/* SPI_TDI = PE11 as input (enable pull-up) */             					\
	GPIOE_REG(GPIO_CTL1)  = ( GPIO_CTL_CTL_IPP << ((_X_-8)*4) );               	\
	/* SPI_TCK = PE13 - Output (10Mhz) & Push-Pull */             				\
    GPIOE_REG(GPIO_CTL1) |= ( GPIO_CTL_MD_O10MHZ << ((_Y_-8)*4) );          	\
    /* SPI_TCK = PE13 - Set output high */                        				\
    GPIOE_REG(GPIO_OCTL) |= ( GPIO_OCTL_OH << _Y_ );                          	\
	/* SPI_TDO = PE15 - Output (10Mhz) & Push-Pull */             				\
    GPIOE_REG(GPIO_CTL1) |= ( GPIO_CTL_MD_O10MHZ << ((_Z_-8)*4) );          	\
    /* SPI_TDO = PE15 - Set output high */                        				\
    GPIOE_REG(GPIO_OCTL) |= ( GPIO_OCTL_OH << _Z_ );                       		\
}

#define SPI_TDO_SET(_X_)	GPIOE_REG(GPIO_BOP) |= ( GPIO_BOP_SET << _X_ );

#define SPI_TDO_CLR(_X_)	GPIOE_REG(GPIO_BC) |= ( GPIO_BC_CLEAR << _X_ );

#define SPI_TDI_BIT(_X_)	(GPIOE_REG(GPIO_ISTAT) >> _X_) & GPIO_ISTAT_IH

#define SPI_TCK_LOW(_X_) 	GPIOE_REG(GPIO_BOP) = ( GPIO_BOP_SET << _X_ );
#define SPI_TCK_HIGH(_X_)	GPIOE_REG(GPIO_BC) = ( GPIO_BC_CLEAR << _X_ );

#define UART_IRQ_CLR()															\
{																				\
}

#define UART_IRQ_RX()		(USART0_REG(USART_STAT0) & USART_STAT0_RBNE)	

#endif
