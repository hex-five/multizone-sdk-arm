/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#define LED_INIT(_X_)                                                           \
{                                                                               \
	/* Write to specific pin's PFS register */                                	\
	R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos);									\
}

#define LED_SET(_X_)    R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos) | 	        \
					    (1U << R_PmnPFS_PIDR_Pos) | (1U << R_PmnPFS_PODR_Pos);

#define LED_CLR(_X_)    R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos);

#define LED_OUT(_X_)    (R_PFS_REG(_X_) & (R_PmnPFS_PIDR_Msk)) == (R_PmnPFS_PIDR_Msk)

#define BTN_INIT(_X_)                                                           \
{                                                                               \
	/* Write to specific pin's PFS register */                                  \
	R_PFS_REG(_X_) = (1U << R_PmnPFS_ISEL_Pos);                       			\
	/* IELSR Must be zero when modifying the IRQCR bits */                      \
	R_ICU_REG(R_ICU_IELSR0) = 0;                                                \
	/* Disable digital filter */                                                \
	R_ICU_REG8(R_ICU_IRQCR+R_EVENT_PORT_IRQ13) = 0;                             \
	/* Set IRQCR */ /* TODO - Add Masks */                                      \
	R_ICU_REG8(R_ICU_IRQCR+R_EVENT_PORT_IRQ13) = 0xB1;                          \
	/* Set IELSR */                                                             \
	R_ICU_REG(R_ICU_IELSR0) = R_EVENT_PORT_IRQ13;                               \
}

#define BTN_IRQ_CLR()                                                           \
{                                                                               \
    R_ICU_REG(R_ICU_IELSR0) &= ~(R_ICU_IELSR_IR);                               \
}

#define SPI_INIT(_X_, _Y_, _Z_)                                                 \
{                                                                               \
    /* Config PmnPFS as input (enable pull-up) */                               \
    R_PFS_REG(_X_) = 0;                                                         \
    R_PFS_REG(_X_) = (1U << R_PmnPFS_PCR_Pos);                                  \
    /* Config PmnPFS as output */                                	            \
    R_PFS_REG(_Y_) = (1U << R_PmnPFS_PDR_Pos) | (1U << R_PmnPFS_PODR_Pos);      \
    R_PFS_REG(_Z_) = (1U << R_PmnPFS_PDR_Pos) | (1U << R_PmnPFS_PODR_Pos);      \
}

#define SPI_TDO_SET(_X_)                                                        \
{                                                                               \
    R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos) | (1U << R_PmnPFS_PODR_Pos);      \
}              

#define SPI_TDO_CLR(_X_)                                                        \
{                                                                               \
    R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos);                                  \
}           

#define SPI_TDI_BIT(_X_)    ((R_PFS_REG(_X_) >> R_PmnPFS_PIDR_Pos) & 1U)        \

#define SPI_TCK_HIGH(_X_)                                                       \
{                                                                               \
    R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos);                                  \
}   

#define SPI_TCK_LOW(_X_)                                                       	\
{                                                                               \
    R_PFS_REG(_X_) = (1U << R_PmnPFS_PDR_Pos) | (1U << R_PmnPFS_PODR_Pos);      \
}         

#define UART_IRQ_CLR()      R_ICU_REG(R_ICU_IELSR8) &= ~(R_ICU_IELSR_IR)

#define UART_IRQ_RX()	    1

#endif
