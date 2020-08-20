/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef HEXFIVE_PLATFORM_H
#define HEXFIVE_PLATFORM_H


/************************************************************************************
* 			               MIMXRT1020-EVK PLATFORM GERENIC			
************************************************************************************/

#define CPU_FREQ                        (24000000)              /*!< Hz */
#define RTC_FREQ                        (24000000)              /*!< Hz */

#define MPU_REGIONS                     (16)

#define UART_IRQn                       UART1_IRQn

#define LED                             LED0
#define LED_PIN                         LED0_PIN

#define LED0                            (5)
#define LED0_PIN                        (1<<LED0)

#define BTN                             SW4
#define BTN_PIN                         SW4
#define BTN_IRQn                        SW4_IRQn

#define SW4                             (0)
#define SW4_PIN                         (1<<SW4)
#define SW4_IRQn                        (104)

#define SPI_TDI                         (22)	                /*!< in 		    - J17(Pin8) = (D7) GPIO_AD_B1_06/GPIO1_IO22    */
#define SPI_TCK                         (24)	                /*!< out (master)   - J17(Pin2) = (D1) GPIO_AD_B1_08/GPIO1_IO24    */
#define SPI_TDO                         (25)	                /*!< out		    - J17(Pin1) = (D0) GPIO_AD_B1_09/GPIO1_IO25    */



/************************************************************************************
* 			            IMXRT1020 PERIPHERALS SPECIFIC				
************************************************************************************/

#define AIPS1_BASE                      (0x40000000UL)
#define AIPS2_BASE                      (0x40100000UL)
#define AIPS3_BASE                      (0x40200000UL)
#define AIPS4_BASE                      (0x40300000UL)

/* General-purpose input/output (GPIO) */
#define GPIO1_BASE                      (AIPS2_BASE + 0xB8000) 
#define GPIO5_BASE                      (AIPS1_BASE + 0xC0000) 
#define GPIO1_REG(offset)               _REG32(GPIO1_BASE, offset)
#define GPIO5_REG(offset)               _REG32(GPIO5_BASE, offset)

#define GPIO_DR                         (0x00)
#define GPIO_GDIR                       (0x04)
#define GPIO_PSR                        (0x08)
#define GPIO_ICR1                       (0x0C)
#define GPIO_IMR                        (0x14)
#define GPIO_ISR                        (0x18)
#define GPIO_EDGE_SEL                   (0x1C)

/* Input/output multiplexing controller (IOMUXC) */
#define IOMUXC_BASE                     (AIPS2_BASE + 0xF8000)
#define IOMUXC_SNVS_BASE                (AIPS1_BASE + 0xA8000) 
#define IOMUX_REG(offset)               _REG32(IOMUXC_BASE, offset)
#define IOMUX_SNVS_REG(offset)          _REG32(IOMUXC_SNVS_BASE, offset)

#define SW_MUX_CTL_PAD_GPIO_AD_B0_05    (0x0D0)
#define SW_PAD_CTL_PAD_GPIO_AD_B0_05    (0x244)
#define SW_MUX_CTL_PAD_GPIO_AD_B0_06    (0x0D4)
#define SW_PAD_CTL_PAD_GPIO_AD_B0_06    (0x248)
#define SW_MUX_CTL_PAD_GPIO_AD_B0_07    (0x0D8)
#define SW_PAD_CTL_PAD_GPIO_AD_B0_07    (0x24C)

#define SW_MUX_CTL_PAD_WAKEUP           (0x00)
#define SW_PAD_CTL_PAD_WAKEUP           (0x18)

#define SW_MUX_CTL_MUX_MODE             (0)      
#define SW_MUX_CTL_SION                 (4)      

#define SW_PAD_CTL_SRE                  (0)
#define SW_PAD_CTL_DSE                  (3)
#define SW_PAD_CTL_SPEED                (6)
#define SW_PAD_CTL_ODE                  (11)
#define SW_PAD_CTL_PKE                  (12)
#define SW_PAD_CTL_PKU                  (13)
#define SW_PAD_CTL_PUS                  (14)
#define SW_PAD_CTL_HYS                  (16)

/* Clock Controller Module (CCM) */
#define CCM_BASE                        (AIPS1_BASE + 0xFC000) 
#define CCM_REG(offset)                 _REG32(CCM_BASE, offset)

#define CCM_CSCDR1                      (0x24)
#define CCM_CCGR1                       (0x6C)
#define CCM_CCGR2                       (0x70)
#define CCM_CCGR4                       (0x78)
#define CCM_CCGR5                       (0x7C)

#define CCM_CCGR5_CG12                  (24)
#define CCM_CCGR1_CG13                  (26)
#define CCM_CCGR1_CG15                  (30)
#define CCM_CCGR2_CG2                   (4)
#define CCM_CCGR4_CG1                   (2)              

#define CCM_CSCDR1_UART_CLK_PODF_MASK   (0x3F)
#define CCM_CSCDR1_UART_CLK_SEL_MASK    (0x40)

/* Universal Synchronous/Asynchronous Receiver/Transmitter 3 (USART3) */
#define UART1_BASE                      (0x40184000)
#define UART1_REG(offset)               _REG32(UART1_BASE, offset)

#define UART_VERID                      (0x00)                  /*!< Version ID Register                */
#define UART_PARAM                      (0x04)                  /*!< Parameter Register                 */
#define UART_GLOBAL                     (0x08)                  /*!< Global Register                    */
#define UART_PINCFG                     (0x0C)                  /*!< Pin Configuration Register         */
#define UART_BAUD                       (0x10)                  /*!< Baud Rate Register                 */
#define UART_STAT                       (0x14)                  /*!< Status Register                    */
#define UART_CTRL                       (0x18)                  /*!< Control Register                   */
#define UART_DATA                       (0x1C)                  /*!< Data Register                      */
#define UART_MATCH                      (0x20)                  /*!< Match Address Register             */
#define UART_MODIR                      (0x24)                  /*!< Modem IrDA Register                */
#define UART_FIFO                       (0x28)                  /*!< FIFO Register                      */
#define UART_WATER                      (0x2C)                  /*!< Watermark Register                 */

#define UART_BAUD_VAL                   (0x6020005)
#define UART_BAUD_M10_MASK              (0x20000000)

#define UART_FIFO_TXFE_MASK             (0x80)
#define UART_FIFO_TXFLUSH_MASK          (0x8000)
#define UART_FIFO_RXFE_MASK             (0x8)
#define UART_FIFO_RXFLUSH_MASK          (0x4000)

#define UART_FIFO_TXEMPT_MASK           (0x800000)
#define UART_FIFO_RXEMPT_MASK           (0x400000)
#define UART_FIFO_TXOF_MASK             (0x20000)
#define UART_FIFO_RXUF_MASK             (0x10000)

#define UART_FIFO_STATS_MASK            UART_FIFO_TXEMPT_MASK| \
                                        UART_FIFO_RXEMPT_MASK| \
                                        UART_FIFO_TXOF_MASK  | \
                                        UART_FIFO_RXUF_MASK

#define UART_STAT_VAL                   (0xC01fC000)
#define UART_STAT_TDRE_MASK             (0x800000)

#define UART_WATER_RXCOUNT_MASK         (0x7000000)
#define UART_WATER_RXCOUNT_SHIFT        (24)

#define UART_CTRL_RIE_MASK              (0x200000)
#define UART_CTRL_VAL                   (UART_CTRL_RIE_MASK | 0xC0000)

#define UART1_IRQn                      (36)



/************************************************************************************
* 			                CORTEX-M7 ARCH SPECIFIC				
************************************************************************************/

/* System Control Space */
#define SCS_BASE                    (0xE000E000UL)              /*!< System Control Space (0xE000E000-0xE000EFFF) */
#define MISC_BASE                   (SCS_BASE + 0x0000UL)       /*!< Misc System Control Registers (0xE000E000-0xE000E00F) */ 
#define SYSTICK_BASE                (SCS_BASE + 0x0010UL)       /*!< SysTick Timer (0xE000E010-0xE000E01F) */
#define NVIC_BASE                   (SCS_BASE + 0x0100UL)       /*!< Nested Vectored Interrupt Controller (0xE000E100-) */
#define SCB_BASE                    (SCS_BASE + 0x0D00UL)       /*!< System Control Block (0xE000E0D0-) */
#define MPU_BASE                    (SCS_BASE + 0x0D90UL)       /*!< Memory Protection Unit (0xE000ED90-) */

/* System Control Block (SCB) */
#define SCB_CPUID                   (SCB_BASE + 0x00UL)         /*!< CPUID Base Register */
#define SCB_ICSR                    (SCB_BASE + 0x04UL)         /*!< Interrupt Control and State Register */
#define SCB_VTOR                    (SCB_BASE + 0x08UL)         /*!< Vector Table Offset Register */
#define SCB_AIRCR                   (SCB_BASE + 0x0CUL)         /*!< Application Interrupt and Reset Control Register */
#define SCB_SCR                     (SCB_BASE + 0x10UL)         /*!< System Control Register */
#define SCB_CCR                     (SCB_BASE + 0x14UL)         /*!< Configuration and Control Register */
#define SCB_SHPR1                   (SCB_BASE + 0x18UL)         /*!< System Handler Priority Register 1 */
#define SCB_SHPR2                   (SCB_BASE + 0x1CUL)         /*!< System Handler Priority Register 2 */
#define SCB_SHPR3                   (SCB_BASE + 0x20UL)         /*!< System Handler Priority Register 3 */
#define SCB_SHCSR                   (SCB_BASE + 0x24UL)         /*!< System Handler Control and State Register */
#define SCB_CFSR                    (SCB_BASE + 0x28UL)         /*!< Configurable Fault Status Register */
#define SCB_HFSR                    (SCB_BASE + 0x2CUL)         /*!< HardFault Status Register */
#define SCB_DFSR                    (SCB_BASE + 0x30UL)         /*!< Debug Fault Status Register */
#define SCB_MMFAR                   (SCB_BASE + 0x34UL)         /*!< MemManage Fault Address Register */
#define SCB_BFAR                    (SCB_BASE + 0x38UL)         /*!< BusFault Address Register */
#define SCB_AFSR                    (SCB_BASE + 0x3CUL)         /*!< Auxiliary Fault Status Register */
#define SCB_CPACR                   (SCB_BASE + 0x88UL)         /*!< Coprocessor Access Control Register */

/* Memory Protection Unit (MPU) */
#define MPU_TYPE                    (MPU_BASE + 0x00UL)         /*!< MPU Type Register */
#define MPU_CTRL                    (MPU_BASE + 0x04UL)         /*!< MPU Control Register */
#define MPU_RNR                     (MPU_BASE + 0x08UL)         /*!< MPU Region Number Register */
#define MPU_RBAR                    (MPU_BASE + 0x0CUL)         /*!< MPU Region Base Address Register */
#define MPU_RASR                    (MPU_BASE + 0x10UL)         /*!< MPU Region Attribute and Size Register */
#define MPU_RBAR1                   (MPU_BASE + 0x14UL)         /*!< MPU Region Base Address Alias1 Register */
#define MPU_RASR1                   (MPU_BASE + 0x18UL)         /*!< MPU Region Attribute and Size Alias1 Register */
#define MPU_RBAR2                   (MPU_BASE + 0x1CUL)         /*!< MPU Region Base Address Alias2 Register */
#define MPU_RASR2                   (MPU_BASE + 0x20UL)         /*!< MPU Region Attribute and Size Alias2 Register */
#define MPU_RBAR3                   (MPU_BASE + 0x24UL)         /*!< MPU Region Base Address Alias3 Register */
#define MPU_RASR3                   (MPU_BASE + 0x28UL)         /*!< MPU Region Attribute and Size Alias3 Register */



/************************************************************************************
* 			                    HELPERS				
************************************************************************************/

#define _REG64(base, offset)        (*(volatile uint64_t *)((base) + (offset)))
#define _REG32(base, offset)        (*(volatile uint32_t *)((base) + (offset)))
#define _REG16(base, offset)        (*(volatile uint16_t *)((base) + (offset)))
#define _REG8(base, offset)         (*(volatile uint8_t *)((base) + (offset)))

#endif /* HEXFIVE_PLATFORM_H */
