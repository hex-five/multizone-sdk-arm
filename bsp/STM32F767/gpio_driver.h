/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#define LED_INIT(_X_)                                                                   	\
{                                                                                        	\
        /* Enable the GPIO_LED Clock */                                                  	\
	    RCC_REG(RCC_AHB1ENR) |= RCC_AHB1ENR_GPIOBEN;                                     	\
	    /* Configure the IO Output Type */                                               	\
	    GPIOB_REG(GPIO_MODER)	&= ~(GPIO_MODER_MODER0 << (_X_ * 2));                    	\
	    GPIOB_REG(GPIO_MODER) |= ((GPIO_MODE_OUTPUT) << (_X_ * 2));                      	\
 	    /* Configure the IO Speed */                                                     	\
	    GPIOB_REG(GPIO_OSPEEDR) &= ~(GPIO_OSPEEDER_OSPEEDR0 << (_X_ * 2));               	\
	    GPIOB_REG(GPIO_OSPEEDR) |= (GPIO_SPEED_FREQ_VERY_HIGH<< (_X_ * 2));              	\
        /* Configure the IO Output Type */                                               	\
        GPIOB_REG(GPIO_OTYPER) &= ~(GPIO_OTYPER_OT_0 << _X_) ;                           	\
        GPIOB_REG(GPIO_OTYPER) |= (((GPIO_MODE_OUTPUT & GPIO_OUTPUT_TYPE) >> 4) << _X_); 	\
	    /* Activate the Pull-up or Pull down resistor for the current IO */              	\
        GPIOB_REG(GPIO_PUPDR) &= ~(GPIO_PUPDR_PUPDR0 << (_X_ * 2));                      	\
        GPIOB_REG(GPIO_PUPDR) |= ((GPIO_NOPULL) << (_X_ * 2));                           	\
}

#define LED_SET(_X_)	GPIOB_REG(GPIO_BSRR) = (1 << _X_)

#define LED_CLR(_X_)    GPIOB_REG(GPIO_BSRR) = (uint32_t) (1 << _X_) << GPIO_NUMBER

#define LED_OUT(_X_) 	(GPIOB_REG(GPIO_ODR) & (1 << _X_)) == (1 << _X_)

#define BTN_INIT(_X_)                                                          				\
{                                                                               			\
	    /* Enable the GPIO_LED Clock */                                         			\
	    RCC_REG(RCC_AHB1ENR) |= RCC_AHB1ENR_GPIOCEN;                            			\
        /* APB2 Peripheral Clock Enable Disable */                              			\
	    RCC_REG(RCC_APB2ENR) |= RCC_APB2ENR_SYSCFGEN;                           			\
	    /* Configure source input for the EXTI external interrupt. */           			\
        SYSCFG_REG(SYSCFG_EXTICR3) &= ~(SYSCFG_EXTI_LINE13 >> 16U);             			\
        SYSCFG_REG(SYSCFG_EXTICR3) |= SYSCFG_EXTI_PORTC << 4U;                  			\
        /* Enable IT on provided Lines */                                       			\
        EXTI_REG(EXTI_EMR) &= ~(EXTI_IMR_MR13);                                 			\
        EXTI_REG(EXTI_IMR) |= EXTI_IMR_MR13;                                    			\
        /* Enable Rising Trigger on provided Lines */                           			\
        EXTI_REG(EXTI_FTSR) &= ~(EXTI_IMR_MR13);                                			\
        EXTI_REG(EXTI_RTSR) |= EXTI_IMR_MR13;                                   			\
        GPIOC_REG(GPIO_PUPDR) &= ~(GPIO_PUPDR_PUPDR0 << (_X_ * 2U));            			\
        GPIOC_REG(GPIO_PUPDR) |= (GPIO_NOPULL << (_X_ * 2U));                   			\
        GPIOC_REG(GPIO_MODER) &= ~(GPIO_MODER_MODER0 << (_X_ * 2U));            			\
        GPIOC_REG(GPIO_MODER) |= (GPIO_MODE_INPUT << (_X_ * 2U));               			\
}

#define BTN_IRQ_CLR()                                                               		\
{                                                                                   		\
    EXTI_REG(EXTI_PR) |= EXTI_IMR_MR13;                                             		\
}

#define SPI_INIT(_X_, _Y_, _Z_)                                                       		\
{                                                                                     		\
	/* Enable the GPIOA Clock*/                                                       		\
	RCC_REG(RCC_AHB1ENR) |= (RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN);                  	\
	/* Configure the IO Output Type */                                                		\
	GPIOF_REG(GPIO_MODER) &= ~(GPIO_MODER_MODER0 << (_Y_ * 2));  							\
	GPIOE_REG(GPIO_MODER) &= ~(GPIO_MODER_MODER0 << (_Z_ * 2));  							\
	GPIOF_REG(GPIO_MODER) |= (GPIO_MODE_OUTPUT << (_Y_ * 2)); 								\
	GPIOE_REG(GPIO_MODER) |= (GPIO_MODE_OUTPUT << (_Z_ * 2)); 								\
	/* Configure the IO Speed */                                          					\
	GPIOF_REG(GPIO_OSPEEDR) &= ~(GPIO_OSPEEDER_OSPEEDR0 << (_Y_ * 2));						\
	GPIOE_REG(GPIO_OSPEEDR) &= ~(GPIO_OSPEEDER_OSPEEDR0 << (_Z_ * 2));						\
	GPIOF_REG(GPIO_OSPEEDR) |= (GPIO_SPEED_FREQ_VERY_HIGH << (_Y_ * 2)); 					\
	GPIOE_REG(GPIO_OSPEEDR) |= (GPIO_SPEED_FREQ_VERY_HIGH << (_Z_ * 2)); 					\
	/* Configure the IO Output Type */                                                 		\
	GPIOF_REG(GPIO_OTYPER) &= ~(GPIO_OTYPER_OT_0 << _Y_); 									\
	GPIOE_REG(GPIO_OTYPER) &= ~(GPIO_OTYPER_OT_0 << _Z_); 									\
	GPIOF_REG(GPIO_OTYPER) |= (((GPIO_MODE_OUTPUT & GPIO_OUTPUT_TYPE) >> 4) << _Y_);		\
	GPIOE_REG(GPIO_OTYPER) |= (((GPIO_MODE_OUTPUT & GPIO_OUTPUT_TYPE) >> 4) << _Z_);		\
	/* Activate the Pull-up or Pull down resistor for the current IO */            			\
	GPIOF_REG(GPIO_PUPDR) &= ~(GPIO_PUPDR_PUPDR0 << (_Y_ * 2));								\
	GPIOE_REG(GPIO_PUPDR) &= ~(GPIO_PUPDR_PUPDR0 << (_Z_ * 2));								\
    GPIOF_REG(GPIO_PUPDR) |= ((GPIO_NOPULL) << (_Y_ * 2));									\
	GPIOE_REG(GPIO_PUPDR) |= ((GPIO_NOPULL) << (_Z_ * 2));									\
	GPIOF_REG(GPIO_BSRR) |= (0x1 << _Y_);													\
	GPIOE_REG(GPIO_BSRR) |= (0x1 << _Z_);													\
	/* Configure port mode */                                         						\
	GPIOE_REG(GPIO_MODER) &= ~(GPIO_MODER_MODER0 << (_X_ * 2));                 			\
	/* Activate the Pull-up for the current IO */                               			\
	GPIOE_REG(GPIO_PUPDR) &= ~(GPIO_PUPDR_PUPDR0 << (_X_ * 2));                   			\
   	GPIOE_REG(GPIO_PUPDR) |= ((GPIO_PULLUP) << (_X_ * 2));                       			\
}

#define SPI_TDO_SET(_X_)	GPIOE_REG(GPIO_ODR) |= (0x1 << _X_) 

#define SPI_TDO_CLR(_X_)	GPIOE_REG(GPIO_ODR) &= ~(0x1 << _X_)

#define SPI_TDI_BIT(_X_)	(GPIOE_REG(GPIO_IDR) >> _X_) & 1U

#define SPI_TCK_LOW(_X_)	GPIOF_REG(GPIO_ODR) |= (0x1 << _X_)
#define SPI_TCK_HIGH(_X_)	GPIOF_REG(GPIO_ODR) ^= (0x1 << _X_)

#define UART_IRQ_CLR()																		\
{																							\
}

#define UART_IRQ_RX()		((USART3_REG(USART_ISR) & USART_ISR_RXNE) == USART_ISR_RXNE)


#endif
