/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef HEXFIVE_PLATFORM_H
#define HEXFIVE_PLATFORM_H


/************************************************************************************
* 			              GD32307C-EVAL PLATFORM GERENIC			
************************************************************************************/

#define CPU_FREQ                        (8000000)              /*!< Hz */
#define RTC_FREQ                        (8000000)              /*!< Hz */

#define MPU_REGIONS                     (8)

#define UART_IRQn                       USART0_IRQn

#define LED                             LED_GREEN
#define LED_PIN                         LED_GREEN_PIN

#define LED_GREEN                       (0x00)
#define LED_BLUE                        (0x00)
#define LED_RED                         (0x00)
#define LED_GREEN_PIN                   (1 << LED_GREEN)
#define LED_BLUE_PIN                    (1 << LED_BLUE)
#define LED_RED_PIN                     (1 << LED_RED)

#define BTN                             BTN0
#define BTN_PIN                         BTN0_PIN
#define BTN_IRQn                        BTN0_IRQn

#define BTN0                            (14U)
#define BTN0_PIN                        (14U)
#define BTN0_IRQn                       EXTI10_15_IRQn

#define SPI_TDI                         (11U) 	                    /*!< in 		    - PE11           */
#define SPI_TCK                         (13U)	                    /*!< out (master)   - PE13           */
#define SPI_TDO                         (15U)	                    /*!< out		    - PE15           */

#define UART_RX_OFFSET                  (0x08)
#define UART_TX_OFFSET                  (0x09)
#define UART_RX                         (1 << UART_RX_OFFSET)
#define UART_TX                         (1 << UART_TX_OFFSET)

#define USART_BAUDRATE                  (115200)



/************************************************************************************
* 			            GD32F30x PERIPHERALS SPECIFIC				
************************************************************************************/

#define PERIPH_BASE                 (0x40000000UL)              /*!< AHB/ABP Peripherals            */
#define APB1PERIPH_BASE             PERIPH_BASE
#define APB2PERIPH_BASE             (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE             (PERIPH_BASE + 0x00018000UL)


/* General-purpose input/output (GPIO) */
#define AFIO_BASE                   (APB2PERIPH_BASE + 0x0000UL)
#define GPIOA_BASE                  (APB2PERIPH_BASE + 0x0800UL)
#define GPIOB_BASE                  (APB2PERIPH_BASE + 0x0C00UL)
#define GPIOC_BASE                  (APB2PERIPH_BASE + 0x1000UL)
#define GPIOD_BASE                  (APB2PERIPH_BASE + 0x1400UL)
#define GPIOE_BASE                  (APB2PERIPH_BASE + 0x1800UL)
#define GPIOF_BASE                  (APB2PERIPH_BASE + 0x1C00UL)
#define GPIOG_BASE                  (APB2PERIPH_BASE + 0x2000UL)
#define AFIO_REG(offset)            _REG32(AFIO_BASE, offset)
#define GPIOA_REG(offset)           _REG32(GPIOA_BASE, offset)
#define GPIOB_REG(offset)           _REG32(GPIOB_BASE, offset)
#define GPIOC_REG(offset)           _REG32(GPIOC_BASE, offset)
#define GPIOD_REG(offset)           _REG32(GPIOD_BASE, offset)
#define GPIOE_REG(offset)           _REG32(GPIOE_BASE, offset)
#define GPIOF_REG(offset)           _REG32(GPIOF_BASE, offset)
#define GPIOG_REG(offset)           _REG32(GPIOG_BASE, offset)

#define AFIO_EC                     (0x00)                      /*!< Event control register                 */
#define AFIO_PCF0                   (0x04)                      /*!< AFIO port configuration register 0     */
#define AFIO_EXTISS0                (0x08)                      /*!< EXTI sources selection register 0      */
#define AFIO_EXTISS1                (0x0C)                      /*!< EXTI sources selection register 1      */
#define AFIO_EXTISS2                (0x10)                      /*!< EXTI sources selection register 2      */
#define AFIO_EXTISS3                (0x14)                      /*!< EXTI sources selection register 3      */
#define AFIO_PCF1                   (0x1C)                      /*!< AFIO port configuration register 1     */
#define AFIO_CPSCTL                 (0x20)                      /*!< IO compensation control register       */

#define AFIO_EXTI14SS_PB14          (0x0100)

#define GPIO_CTL0                   (0x00)                      /*!< Port control register 0                */
#define GPIO_CTL1                   (0x04)                      /*!< Port control register 1                */
#define GPIO_ISTAT                  (0x08)                      /*!< Port input status register             */
#define GPIO_OCTL                   (0x0C)                      /*!< Port output control register           */
#define GPIO_BOP                    (0x10)                      /*!< Port bit operate register              */
#define GPIO_BC                     (0x14)                      /*!< Port bit clear register                */
#define GPIO_LOCK                   (0x18)                      /*!< Port configuration lock register       */
#define GPIO_SPD                    (0x3C)                      /*!< Port bit speed register                */

#define GPIO_CTL_MD_IN              (0x00)
#define GPIO_CTL_MD_O10MHZ          (0x01)
#define GPIO_CTL_MD_O2MHZ           (0x02)
#define GPIO_CTL_MD_O50MHZ          (0x03)

#define GPIO_CTL_CTL_IAM            (0x00)
#define GPIO_CTL_CTL_IFI            (0x04)
#define GPIO_CTL_CTL_IPP            (0x08)

#define GPIO_CTL_CTL_OPP            (0x00)
#define GPIO_CTL_CTL_OOD            (0x04)
#define GPIO_CTL_CTL_AFIOPP         (0x08)
#define GPIO_CTL_CTL_AFIOOD         (0x0C)

#define GPIO_ISTAT_IL               (0x00)
#define GPIO_ISTAT_IH               (0x01)

#define GPIO_OCTL_OL                (0x00)
#define GPIO_OCTL_OH                (0x01)

#define GPIO_BOP_SET                (0x01)

#define GPIO_BC_CLEAR               (0x01)


/* External interrupts (EXTI) */
#define EXTI_BASE                   (APB2PERIPH_BASE + 0x0400UL)
#define EXTI_REG(offset)            _REG32(EXTI_BASE, offset)

#define EXTI_INTEN                  (0x00)                      /*!< Interrupt enable register          */
#define EXTI_EVEN                   (0x04)                      /*!< Event enable register              */
#define EXTI_RTEN                   (0x08)                      /*!< Rising edge trigger enable reg     */
#define EXTI_FTEN                   (0x0C)                      /*!< Falling edge trigger enable reg    */
#define EXTI_SWIEV                  (0x10)                      /*!< Software interrupt event register  */
#define EXTI_PD                     (0x14)                      /*!< Pending register                   */

#define EXTI10_15_IRQn              (0x38)                      /*!< 0x38 = 56 */


/* Universal Synchronous/Asynchronous Receiver/Transmitter (USART) */
#define USART0_BASE                 (APB2PERIPH_BASE + 0x3800UL)
#define USART1_BASE                 (APB1PERIPH_BASE + 0x4400UL)
#define USART2_BASE                 (APB1PERIPH_BASE + 0x4800UL)
#define UART3_BASE                  (APB1PERIPH_BASE + 0x4C00UL)
#define UART4_BASE                  (APB1PERIPH_BASE + 0x5000UL)
#define USART0_REG(offset)          _REG32(USART0_BASE, offset)
#define USART1_REG(offset)          _REG32(USART1_BASE, offset)
#define USART2_REG(offset)          _REG32(USART2_BASE, offset)
#define UART3_REG(offset)           _REG32(UART3_BASE, offset)
#define UART4_REG(offset)           _REG32(UART4_BASE, offset)

#define USART_STAT0                 (0x00)                      /*!< Status register 0                  */
#define USART_DATA                  (0x04)                      /*!< Data register                      */
#define USART_BAUD                  (0x08)                      /*!< Baud rate register                 */
#define USART_CTL0                  (0x0C)                      /*!< Control register 0                 */
#define USART_CTL1                  (0x10)                      /*!< Control register 1                 */
#define USART_CTL2                  (0x14)                      /*!< Control register 2                 */
#define USART_GP                    (0x18)                      /*!< Guard time and prescaler register  */
#define USART_CTL3                  (0x80)                      /*!< Control register 3                 */
#define USART_RT                    (0x84)                      /*!< Receiver timeout register          */
#define USART_STAT1                 (0x88)                      /*!< Status register 1                  */

#define USART_STAT0_TBE             (1 << 7)
#define USART_STAT0_TC              (1 << 6)
#define USART_STAT0_RBNE            (1 << 5)

#define USART_CTL0_REN              (1 << 2)
#define USART_CTL0_TEN              (1 << 3)
#define USART_CTL0_RBNEIE           (1 << 5)
#define USART_CTL0_WL_9             (1 << 12)
#define USART_CTL0_UEN              (1 << 13)

#define USART0_IRQn                 (0x35)                      /*!< 0x35 = 53 */



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
