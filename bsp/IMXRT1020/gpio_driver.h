/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#define LED_INIT(_X_)                                                           \
{																				\
	/* Enable the IOMUXC Clock */												\
	CCM_REG(CCM_CCGR4) |= (0x3 << CCM_CCGR4_CG1);								\
	/* GPIO_AD_B0_05 is configured as GPIO1_IO05 */								\
	IOMUX_REG(SW_MUX_CTL_PAD_GPIO_AD_B0_05) |= (0x5 << SW_MUX_CTL_MUX_MODE);	\
	IOMUX_REG(SW_MUX_CTL_PAD_GPIO_AD_B0_05) &= ~(1 << SW_MUX_CTL_SION);			\
	/* GPIO_AD_B0_05 PAD functional properties */								\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) &= ~(1 << SW_PAD_CTL_SRE);			\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) |=  (0x6 << SW_PAD_CTL_DSE);		\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) |=  (1 << SW_PAD_CTL_SPEED);		\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) &= ~(1 << SW_PAD_CTL_ODE);			\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) |=  (1 << SW_PAD_CTL_PKE);			\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) &= ~(1 << SW_PAD_CTL_PKU);			\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) &= ~(3 << SW_PAD_CTL_PUS);			\
	IOMUX_REG(SW_PAD_CTL_PAD_GPIO_AD_B0_05) &= ~(1 << SW_PAD_CTL_HYS);			\
	/* Enable the GPIO_LED Clock */												\
	CCM_REG(CCM_CCGR1) |= (0x3 << CCM_CCGR1_CG13);								\
	/* Register reset to default value */										\
	GPIO1_REG(GPIO_IMR) &= ~(1 << _X_);											\
	/* Configure GPIO pin direction as digital output */						\
	/* Set pin output to low level.*/											\
	GPIO1_REG(GPIO_DR) &= ~(1 << _X_);											\
	GPIO1_REG(GPIO_GDIR) |= (1 << _X_);											\
}

#define LED_SET(_X_)	GPIO1_REG(GPIO_DR) &= ~(1 << _X_)

#define LED_CLR(_X_)	GPIO1_REG(GPIO_DR) |= (1 << _X_)

#define LED_OUT(_X_)	(GPIO1_REG(GPIO_DR) & (1 << _X_)) == 0

#define BTN_INIT(_X_)                                                          	\
{                                                                               \
	/* Enable the IOMUXC Clock */												\
	CCM_REG(CCM_CCGR2) |= (0x3 << CCM_CCGR2_CG2);								\
	/* SNVS_WAKEUP is configured as GPIO5_IO00 */								\
	IOMUX_SNVS_REG(SW_MUX_CTL_PAD_WAKEUP) |=  (0x5 << SW_MUX_CTL_MUX_MODE); 	\
	IOMUX_SNVS_REG(SW_MUX_CTL_PAD_WAKEUP) &= ~(1 << SW_MUX_CTL_SION);			\
	/* GPIO_AD_B0_05 PAD functional properties */								\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) &= ~(1 << SW_PAD_CTL_SRE);			\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) &= ~(0x7 << SW_PAD_CTL_DSE);			\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) &= ~(1 << SW_PAD_CTL_ODE);			\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) |=  (1 << SW_PAD_CTL_PKE);			\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) |=  (1 << SW_PAD_CTL_PKU);			\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) |=  (3 << SW_PAD_CTL_PUS);			\
	IOMUX_SNVS_REG(SW_PAD_CTL_PAD_WAKEUP) &= ~(1 << SW_PAD_CTL_HYS);			\
	/* Enable the GPIO_LED Clock */												\
	CCM_REG(CCM_CCGR1) |= (0x3 << CCM_CCGR1_CG15);								\
	/* Register reset to default value */										\
	GPIO5_REG(GPIO_IMR) &= ~(1 << _X_);											\
	/* Configure GPIO pin direction as digital input */							\
	GPIO5_REG(GPIO_GDIR) &= ~(1 << _X_);										\
	/* Configure GPIO pin interrupt */											\
	GPIO5_REG(GPIO_ICR1) &= ~(0x3 << _X_);										\
	GPIO5_REG(GPIO_ICR1) |= (0x2 << _X_);										\
	/* Enable GPIO pin interrupt */												\
	GPIO5_REG(GPIO_IMR) |= (1 << _X_);											\
	GPIO5_REG(GPIO_EDGE_SEL) &= ~(0x1 << _X_);									\
}

#define BTN_IRQ_CLR()                                                           \
{                                                                               \
    GPIO5_REG(GPIO_ISR) |=  (1 << BTN);											\
}

#define SPI_INIT(_X_, _Y_, _Z_)                                                 \
{                                                                               \
	/* Enable the GPIO1 Clock */												\
	CCM_REG(CCM_CCGR1) |= (0x3 << CCM_CCGR1_CG13);								\
	/* Register reset to default value */										\
	GPIO1_REG(GPIO_IMR) &= ~(1 << _X_);											\
	GPIO1_REG(GPIO_IMR) &= ~(1 << _Y_);											\
	GPIO1_REG(GPIO_IMR) &= ~(1 << _Z_);											\
	/* Configure GPIO pin direction as digital output */						\
	/* Set pin output to low level.*/											\
	GPIO1_REG(GPIO_DR) &= ~(1 << _Y_);											\
	GPIO1_REG(GPIO_GDIR) |= (1 << _Y_);											\
	GPIO1_REG(GPIO_DR) &= ~(1 << _Z_);											\
	GPIO1_REG(GPIO_GDIR) |= (1 << _Z_);											\
	/* Configure GPIO pin direction as digital input */							\
	GPIO1_REG(GPIO_GDIR) &= ~(1 << _X_);										\
}

#define SPI_TDO_SET(_X_)	GPIO1_REG(GPIO_DR) |= (0x1 << _X_)

#define SPI_TDO_CLR(_X_)	GPIO1_REG(GPIO_DR) &= ~(0x1 << _X_)

#define SPI_TDI_BIT(_X_)	(GPIO1_REG(GPIO_PSR) >> _X_) & 1U

#define SPI_TCK_LOW(_X_) 	GPIO1_REG(GPIO_DR) |= (0x1 << _X_)
#define SPI_TCK_HIGH(_X_)	GPIO1_REG(GPIO_DR) ^= (0x1 << _X_)

#define UART_IRQ_CLR()															\
{																				\
	UART1_REG(UART_STAT);														\
	UART1_REG(UART_FIFO);														\
}

#define UART_IRQ_RX()		(((UART1_REG(UART_WATER) & UART_WATER_RXCOUNT_MASK) \
								>> UART_WATER_RXCOUNT_SHIFT) != 0)

#endif
