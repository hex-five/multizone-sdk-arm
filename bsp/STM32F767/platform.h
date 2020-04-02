/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef HEXFIVE_PLATFORM_H
#define HEXFIVE_PLATFORM_H


/************************************************************************************
* 			               NUCLEO-F746ZG PLATFORM GERENIC			
************************************************************************************/

#define CPU_FREQ                        (16000000)              /*!< Hz */
#define RTC_FREQ                        (16000000)              /*!< Hz */

#define MPU_REGIONS                     (8)

#define UART_IRQn                       USART3_IRQn

#define LED                             LED_GREEN
#define LED_PIN                         LED_GREEN_PIN

#define LED_GREEN                       (0x00)
#define LED_BLUE                        (0x07)
#define LED_RED                         (0x0E)
#define LED_GREEN_PIN                   (1 << LED_GREEN)
#define LED_BLUE_PIN                    (1 << LED_BLUE)
#define LED_RED_PIN                     (1 << LED_RED)

#define BTN                             BTN0
#define BTN_PIN                         BTN0_PIN
#define BTN_IRQn                        BTN0_IRQn

#define BTN0                            (13U)
#define BTN0_PIN                        (13U)
#define BTN0_IRQn                       EXTI_IRQn

#define SPI_TDI                         (11) 	                /*!< in 	        - D5 (PE11) */
#define SPI_TCK                         (14)	                /*!< out (master)   - D4 (PF14) */
#define SPI_TDO                         (13)	                /*!< out	        - D3 (PE13)  */

#define UART_RX_OFFSET                  (0x08)
#define UART_TX_OFFSET                  (0x09)
#define UART_RX                         (1 << UART_RX_OFFSET)
#define UART_TX                         (1 << UART_TX_OFFSET)

#define USART_BAUDRATE                  (115200)



/************************************************************************************
* 			            STM32F746ZG PERIPHERALS SPECIFIC				
************************************************************************************/

#define PERIPH_BASE                 (0x40000000UL)              /*!< AHB/ABP Peripherals            */
#define APB1PERIPH_BASE             PERIPH_BASE
#define APB2PERIPH_BASE             (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE             (PERIPH_BASE + 0x00020000U)


/* Clock and reset managements (RCC) */
#define RCC_BASE                    (AHB1PERIPH_BASE + 0x3800U)
#define RCC_REG(offset)             _REG32(RCC_BASE, offset)

#define RCC_AHB1ENR                 (0x30)                      /*!< RCC AHB1 peripheral clock        */
#define RCC_APB1ENR                 (0x40)                      /*!< RCC APB1 peripheral clock enable */
#define RCC_APB2ENR                 (0x44)                      /*!< RCC APB2 peripheral clock enable */

#define RCC_AHB1ENR_GPIOAEN         (0x00000001)
#define RCC_AHB1ENR_GPIOBEN         (0x00000002)
#define RCC_AHB1ENR_GPIOCEN         (0x00000004)
#define RCC_AHB1ENR_GPIODEN         (0x00000008)
#define RCC_AHB1ENR_GPIOEEN         (0x00000010)
#define RCC_AHB1ENR_GPIOFEN         (0x00000020)

#define RCC_APB1ENR_USART3EN        (0x00040000)
#define RCC_APB2ENR_SYSCFGEN        (0x00004000)

#define RCC_USART3_CLKSOURCE        (0x00000030)   


/* System configuration controller (SYSCFG) */
#define SYSCFG_BASE                 (APB2PERIPH_BASE + 0x3800UL)
#define SYSCFG_REG(offset)          _REG32(SYSCFG_BASE, offset)

#define SYSCFG_MEMRMP               (0x00)                      /*!< SYSCFG memory remap                        */
#define SYSCFG_PMC                  (0x04)                      /*!< SYSCFG peripheral mode configuration       */
#define SYSCFG_EXTICR0              (0x08)                      /*!< SYSCFG external interrupt configuration    */
#define SYSCFG_EXTICR1              (0x0C)                      /*!< SYSCFG external interrupt configuration    */
#define SYSCFG_EXTICR2              (0x10)                      /*!< SYSCFG external interrupt configuration    */
#define SYSCFG_EXTICR3              (0x14)                      /*!< SYSCFG external interrupt configuration    */
    /* Reserved, 0x18 */    
#define SYSCFG_CBR                  (0x1C)                      /*!< SYSCFG Class B                             */
#define SYSCFG_CMPCR                (0x20)                      /*!< SYSCFG Compensation cell control           */

#define SYSCFG_EXTI_LINE13          (0x00F0U << 16U | 3U)       /*!< EXTI_POSITION_4  | EXTICR[3]               */
#define SYSCFG_EXTI_PORTC           (2U)                        /*!< EXTI PORT C                                */


/* General-purpose input/output (GPIO) */
#define GPIOA_BASE                  (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE                  (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE                  (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE                  (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE                  (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOF_BASE                  (AHB1PERIPH_BASE + 0x1400UL)
#define GPIOA_REG(offset)           _REG32(GPIOA_BASE, offset)
#define GPIOB_REG(offset)           _REG32(GPIOB_BASE, offset)
#define GPIOC_REG(offset)           _REG32(GPIOC_BASE, offset)
#define GPIOD_REG(offset)           _REG32(GPIOD_BASE, offset)
#define GPIOE_REG(offset)           _REG32(GPIOE_BASE, offset)
#define GPIOF_REG(offset)           _REG32(GPIOF_BASE, offset)

#define GPIO_MODER                  (0x00)                      /*!< GPIO port mode                         */
#define GPIO_OTYPER                 (0x04)                      /*!< GPIO port output type                  */
#define GPIO_OSPEEDR                (0x08)                      /*!< GPIO port output speed                 */
#define GPIO_PUPDR                  (0x0C)                      /*!< GPIO port pull-up/pull-down            */
#define GPIO_IDR                    (0x10)                      /*!< GPIO port input data                   */
#define GPIO_ODR                    (0x14)                      /*!< GPIO port output data                  */
#define GPIO_BSRR                   (0x18)                      /*!< GPIO port bit set/reset                */
#define GPIO_LCKR                   (0x1C)                      /*!< GPIO port configuration lock           */
#define GPIO_AFR0                   (0x20)                      /*!< GPIO alternate function                */
#define GPIO_AFR1                   (0x24)                      /*!< GPIO alternate function                */

#define GPIO_OUTPUT_PUSHPULL        (0x00000000U)               /*!< Select push-pull as output type        */
#define GPIO_MODE_OUTPUT            (0x00000001U)               /*!< Output Push Pull Mode                  */
#define GPIO_MODE_ALTERNATE         (0x00000002U)               /*!< Select alternate function mode         */
#define GPIO_MODE_INPUT             (0x00000000U)               /*!< Select input function mode             */

#define GPIO_NOPULL                 (0x00000000U)               /*!< No Pull-up or Pull-down activation     */
#define GPIO_PULLUP                 (0x00000001U)               /*!< Pull-up activation                     */
#define GPIO_SPEED_FREQ_VERY_HIGH   (0x00000003U)               /*!< High speed                             */

#define GPIO_AF_7                   (0x00000007U)               /*!<  Select alternate function 7           */

#define GPIO_MODER_MODER0           (0x00000003)   
#define GPIO_OSPEEDER_OSPEEDR0      (0x00000003)
#define GPIO_OTYPER_OT_0            (0x00000001)  
#define GPIO_PUPDR_PUPDR0           (0x00000003)
#define GPIO_AFRH_AFRH0             (0x0000000F)

#define GPIO_NUMBER                 (16)
#define GPIO_MODE                   (0x00000003)
#define GPIO_OUTPUT_TYPE            (0x00000010)


/* External interrupts (EXTI) */
#define EXTI_BASE                   (APB2PERIPH_BASE + 0x3C00UL)
#define EXTI_REG(offset)            _REG32(EXTI_BASE, offset)

#define EXTI_IMR                    (0x00)                      /*!< EXTI Interrupt mask                */
#define EXTI_EMR                    (0x04)                      /*!< EXTI Event mask                    */
#define EXTI_RTSR                   (0x08)                      /*!< EXTI Rising trigger selection      */
#define EXTI_FTSR                   (0x0C)                      /*!< EXTI Falling trigger selection     */
#define EXTI_SWIER                  (0x10)                      /*!< EXTI Software interrupt event      */
#define EXTI_PR                     (0x14)                      /*!< EXTI Pending                       */

#define EXTI_IMR_MR13               (0x00002000)                /*!< Interrupt Mask on line 13          */

#define EXTI_IRQn                   (0x38)


/* Universal Synchronous/Asynchronous Receiver/Transmitter 3 (USART3) */
#define USART3_BASE                 (APB1PERIPH_BASE + 0x4800UL)
#define USART3_REG(offset)          _REG32(USART3_BASE, offset)

#define USART_CR1                   (0x00)                      /*!< USART Control register 1           */
#define USART_CR2                   (0x04)                      /*!< USART Control register 2           */
#define USART_CR3                   (0x08)                      /*!< USART Control register 3           */
#define USART_BRR                   (0x0C)                      /*!< USART Baud rate                    */
#define USART_GTPR                  (0x10)                      /*!< USART Guard time and prescaler     */
#define USART_RTOR                  (0x14)                      /*!< USART Receiver Time Out            */
#define USART_RQR                   (0x18)                      /*!< USART Request                      */
#define USART_ISR                   (0x1C)                      /*!< USART Interrupt and status         */
#define USART_ICR                   (0x20)                      /*!< USART Interrupt flag Clear         */
#define USART_RDR                   (0x24)                      /*!< USART Receive Data                 */
#define USART_TDR                   (0x28)                      /*!< USART Transmit Data                */

#define USART3_PERIPHCLK            (0x00F42400U)

#define USART_DATAWIDTH_8B          (0x00000000U)               /*!< 8 bits word length                 */
#define USART_STOPBITS_1            (0x00000000U)               /*!< 1 stop bit                         */
#define USART_PARITY_NONE           (0x00000000U)               /*!< Parity control disabled            */

#define USART_DIRECTION_TX_RX       (USART_CR1_TE|USART_CR1_RE)  

#define USART_HWCONTROL_NONE        (0x00000000U)               /*!< CTS and RTS hardware disabled      */

#define USART_OVERSAMPLING_16       (0x00000000U)  

#define USART_CR1_M                 (0x10001000)
#define USART_CR1_PCE               (0x00000400)
#define USART_CR1_PS                (0x00000200)
#define USART_CR1_TE                (0x00000008)                /*!< Transmitter Enable                 */
#define USART_CR1_RE                (0x00000004)                /*!< Receiver Enable                    */ 
#define USART_CR1_OVER8             (0x00008000)
#define USART_CR1_RXNEIE            (0x00000020)
#define USART_CR1_UE                (0x00000001)

#define USART_CR2_STOP              (0x00003000)
#define USART_CR2_LINEN             (0x00004000)
#define USART_CR2_CLKEN             (0x00000800)

#define USART_CR3_RTSE              (0x00000100)
#define USART_CR3_CTSE              (0x00000200)
#define USART_CR3_SCEN              (0x00000020)
#define USART_CR3_IREN              (0x00000002)
#define USART_CR3_HDSEL             (0x00000008)

#define USART_ICR_ORECF             (0x00000008)                /*!< OverRun Error Clear Flag           */

#define USART_ISR_ORE               (0x00000008)                /*!< OverRun Error                      */
#define USART_ISR_RXNE              (0x00000020)                /*!< Read Data Register Not Empty       */
#define USART_ISR_TXE               (0x00000080)                /*!< Transmit Data Register Empty       */

#define USART3_IRQn                 (55)



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
