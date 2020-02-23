/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef HEXFIVE_PLATFORM_H
#define HEXFIVE_PLATFORM_H


/************************************************************************************
* 			               EKRA6M3 PLATFORM GERENIC			
************************************************************************************/

#define CPU_FREQ                        (120000000)             /*!< Hz */
#define RTC_FREQ                        (120000000)             /*!< Hz */

#define MPU_REGIONS                     (8)

#define UART_IRQn                       UART_RX_IRQn
#define USART_BAUDRATE                  (115200)

#define LED                             LED_GREEN
#define LED_PIN                         LED_GREEN_PIN
#define LED_GREEN                       R_PFS_P400PFS
#define LED_BLUE                        R_PFS_P403PFS
#define LED_RED                         R_PFS_P100PFS

#define BTN                             (0)
#define BTN_PIN                         R_PFS_P009PFS
#define BTN_IRQn                        (16)

#define SPI_TDI                         R_PFS_P907PFS 	        /*!< in 		    - D5 (P907) */
#define SPI_TCK                         R_PFS_P908PFS	        /*!< out (master)   - D4 (P908) */
#define SPI_TDO                         R_PFS_P505PFS	        /*!< out		    - D3 (P505) */



/************************************************************************************
* 			            R7FA6M3AH3CFC PERIPHERALS SPECIFIC				
************************************************************************************/

#define PERIPH_BASE                     (0x40000000UL)          /*!< AHB/ABP Peripherals*/


/*  Interrupt Controller Unit (ICU) */
#define R_ICU                           (PERIPH_BASE+0x06000UL) 
#define R_ICU_REG(offset)               _REG32(R_ICU, offset)
#define R_ICU_REG16(offset)             _REG16(R_ICU, offset)
#define R_ICU_REG8(offset)              _REG8(R_ICU, offset)

#define R_ICU_IRQCR                     (0x00000)               /*!< IRQ Control Register [0..15] */
#define R_ICU_NMICR                     (0x00100)               /*!< NMI Pin Interrupt Control Register */
#define R_ICU_NMIER                     (0x00120)               /*!< Non-Maskable Interrupt Enable Register */
#define R_ICU_NMICLR                    (0x00130)               /*!< Non-Maskable Interrupt Status Clear Register */
#define R_ICU_NMISR                     (0x00140)               /*!< Non-Maskable Interrupt Status Clear Register */
#define R_ICU_WUPEN                     (0x001A0)               /*!< Wake Up Interrupt Enable Register */
#define R_ICU_SELSR0                    (0x00200)               /*!< Snooze Event Link Setting Register */
#define R_ICU_DELSR                     (0x00280)               /*!< DMAC Event Link Setting Register */
#define R_ICU_IELSR                     (0x00300)               /*!< ICU Event Link Setting Register [0..95] */

#define R_ICU_IELSR0                    (0x00300)               /*!< ICU Event Link Setting Register 0 */
#define R_ICU_IELSR1                    (0x00304)               /*!< ICU Event Link Setting Register 1 */
#define R_ICU_IELSR2                    (0x00308)               /*!< ICU Event Link Setting Register 2 */
#define R_ICU_IELSR3                    (0x0030C)               /*!< ICU Event Link Setting Register 3 */
#define R_ICU_IELSR4                    (0x00310)               /*!< ICU Event Link Setting Register 4 */
#define R_ICU_IELSR5                    (0x00314)               /*!< ICU Event Link Setting Register 5 */
#define R_ICU_IELSR6                    (0x00318)               /*!< ICU Event Link Setting Register 6 */
#define R_ICU_IELSR7                    (0x0031C)               /*!< ICU Event Link Setting Register 7 */
#define R_ICU_IELSR8                    (0x00320)               /*!< ICU Event Link Setting Register 8 */

#define R_ICU_IELSR_IR                  (1<<16U)

/* Event Table (R01UH0886EJ0100 Rev.1.00 - pag. 275-282) */
#define R_EVENT_PORT_IRQ0               (0x001)
#define R_EVENT_PORT_IRQ1               (0x002)
#define R_EVENT_PORT_IRQ2               (0x003)
#define R_EVENT_PORT_IRQ3               (0x004)
#define R_EVENT_PORT_IRQ4               (0x005)
#define R_EVENT_PORT_IRQ5               (0x006)
#define R_EVENT_PORT_IRQ6               (0x007)
#define R_EVENT_PORT_IRQ7               (0x008)
#define R_EVENT_PORT_IRQ8               (0x009)
#define R_EVENT_PORT_IRQ9               (0x00A)
#define R_EVENT_PORT_IRQ10              (0x00B)
#define R_EVENT_PORT_IRQ11              (0x00C)
#define R_EVENT_PORT_IRQ12              (0x00D)
#define R_EVENT_PORT_IRQ13              (0x00E)
#define R_EVENT_PORT_IRQ14              (0x00F)
#define R_EVENT_PORT_IRQ15              (0x010)
    /* ... */
#define R_EVENT_SCI0_RXI                (0x174)
#define R_EVENT_SCI0_TXI                (0x175)
#define R_EVENT_SCI0_TEI                (0x176)
#define R_EVENT_SCI0_ERI                (0x177)
    /* ... */
#define R_EVENT_SCI7_RXI                (0x19E)
    /* ... */
#define R_EVENT_JPEG_JEDI               (0x1FE)
#define R_EVENT_JPEG_JDTI               (0x1FF)


/* Port Function Select (PFS) */

#define R_PFS                           (PERIPH_BASE+0x40800UL)
#define R_PFS_REG(offset)               _REG32(R_PFS, offset)
#define R_PFS_REG16(offset)             _REG16(R_PFS, offset)
#define R_PFS_REG8(offset)              _REG8(R_PFS, offset)

#define R_PFS_P000PFS                   (0x0000)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P001PFS                   (0x0004)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P002PFS                   (0x0008)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P003PFS                   (0x000C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P004PFS                   (0x0010)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P005PFS                   (0x0014)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P006PFS                   (0x0018)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P007PFS                   (0x001C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P008PFS                   (0x0020)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P009PFS                   (0x0024)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P010PFS                   (0x0028)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P011PFS                   (0x002C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P012PFS                   (0x0030)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P013PFS                   (0x0034)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P014PFS                   (0x0038)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P015PFS                   (0x003C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P100PFS                   (0x0040)                /*!< Port mn Pin Function Select Register */
    /* ... P101-P114 ... */
#define R_PFS_P115PFS                   (0x007C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P400PFS                   (0x0100)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P401PFS                   (0x0104)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P402PFS                   (0x0108)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P403PFS                   (0x010C)                /*!< Port mn Pin Function Select Register */
    /* ... P404-P409 ... */
#define R_PFS_P410PFS                   (0x0128)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P411PFS                   (0x012C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P412PFS                   (0x0130)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P413PFS                   (0x0134)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P414PFS                   (0x0138)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P415PFS                   (0x013C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P500PFS                   (0x0140)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P501PFS                   (0x0144)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P502PFS                   (0x0148)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P503PFS                   (0x014C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P504PFS                   (0x0150)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P505PFS                   (0x0154)                /*!< Port mn Pin Function Select Register */
    /* ... P506-P512 ... */
#define R_PFS_P513PFS                   (0x0174)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P600PFS                   (0x0180)                /*!< Port mn Pin Function Select Register */
    /* ... P601-P612 ... */
#define R_PFS_P613PFS                   (0x01b4)                /*!< Port mn Pin Function Select Register */              
#define R_PFS_P614PFS                   (0x01b8)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P615PFS                   (0x01bc)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P900PFS                   (0x0240)                /*!< Port mn Pin Function Select Register */
    /* ... P902-P906 ... */
#define R_PFS_P907PFS                   (0x025C)                /*!< Port mn Pin Function Select Register */
#define R_PFS_P908PFS                   (0x0260)                /*!< Port mn Pin Function Select Register */

#define R_PmnPFS_PODR_Pos               (0UL)                   /*!< PODR (Bit 0)                   */
#define R_PmnPFS_PODR_Msk               (0x1UL)                 /*!< PODR (Bitfield-Mask: 0x01)     */
#define R_PmnPFS_PIDR_Pos               (1UL)                   /*!< PIDR (Bit 1)                   */
#define R_PmnPFS_PIDR_Msk               (0x2UL)                 /*!< PIDR (Bitfield-Mask: 0x01)     */
#define R_PmnPFS_PDR_Pos                (2UL)                   /*!< PDR (Bit 2)                    */
#define R_PmnPFS_PDR_Msk                (0x4UL)                 /*!< PDR (Bitfield-Mask: 0x01)      */
#define R_PmnPFS_PCR_Pos                (4UL)                   /*!< PCR (Bit 4)                    */
#define R_PmnPFS_PCR_Msk                (0x10UL)                /*!< PCR (Bitfield-Mask: 0x01)      */
#define R_PmnPFS_DSCR_Pos               (10UL)                  /*!< DSCR (Bit 10)                  */
#define R_PmnPFS_DSCR_Msk               (0xc00UL)               /*!< DSCR (Bitfield-Mask: 0x03)     */
#define R_PmnPFS_EOFR_Pos               (12UL)                  /*!< EOFR (Bit 12)                  */
#define R_PmnPFS_EOFR_Msk               (0x3000UL)              /*!< EOFR (Bitfield-Mask: 0x03)     */
#define R_PmnPFS_ISEL_Pos               (14UL)                  /*!< ISEL (Bit 14)                  */
#define R_PmnPFS_ISEL_Msk               (0x4000UL)              /*!< ISEL (Bitfield-Mask: 0x01)     */
#define R_PmnPFS_ASEL_Pos               (15UL)                  /*!< ASEL (Bit 15)                  */
#define R_PmnPFS_ASEL_Msk               (0x8000UL)              /*!< ASEL (Bitfield-Mask: 0x01)     */
#define R_PmnPFS_PMR_Pos                (16UL)                  /*!< PMR (Bit 16)                   */
#define R_PmnPFS_PMR_Msk                (0x10000UL)             /*!< PMR (Bitfield-Mask: 0x01)      */
#define R_PmnPFS_PSEL_Pos               (24UL)                  /*!< PSEL (Bit 24)                  */
#define R_PmnPFS_PSEL_Msk               (0x1f000000UL)          /*!< PSEL (Bitfield-Mask: 0x1f)     */


/* Module Stop Control (MSTP) */
#define R_MSTP_BASE                     (0x40047000UL)
#define MSTP_REG(offset)                _REG32(R_MSTP_BASE, offset)

#define R_MSTP_MSTPCRB_MSTPB31_Msk      (0x80000000)            /*!< SCI0:MSTPB31                   */
#define R_MSTP_MSTPCRB_MSTPB24_Msk      (0x01000000)            /*!< SCI0:MSTPB24                   */


/* Serial Communication Interface 7 (SCI7) */
#define R_SCI7_BASE                     (0x400700E0UL)

#define R_SCI7_REG8(offset)             _REG8(R_SCI7_BASE, offset)
#define R_SCI7_REG16(offset)            _REG16(R_SCI7_BASE, offset)
#define R_SCI7_REG16(offset)            _REG16(R_SCI7_BASE, offset)

#define R_SCI_SMR                       (0x00000000)
#define R_SCI_BRR                       (0x00000001)
#define R_SCI_SCR                       (0x00000002)
#define R_SCI_TDR                       (0x00000003)
#define R_SCI_SSR                       (0x00000004)
#define R_SCI_RDR                       (0x00000005)
#define R_SCI_SCMR                      (0x00000006)
#define R_SCI_SEMR                      (0x00000007)
#define R_SCI_SNFR                      (0x00000008)
#define R_SCI_SIMR1                     (0x00000009)
#define R_SCI_SIMR2                     (0x0000000A)
#define R_SCI_SIMR3                     (0x0000000B)
#define R_SCI_SPMR                      (0x0000000D)
#define R_SCI_MDDR                      (0x00000012)
#define R_SCI_DCCR                      (0x00000013)
#define R_SCI_CDR                       (0x0000001A)  
#define R_SCI_SPTR                      (0x0000001C)

#define SCI_UART_DCCR_DEFAULT_VALUE     (0x40U)
#define SCI_UART_SCMR_DEFAULT_VALUE     (0xF2U)
#define SPTR_SPB2D_BIT                  (1U)
#define SPTR_OUTPUT_ENABLE_MASK         (0x04U)
#define SCI_SCR_RE_MASK                 (0x10U)
#define SCI_SCR_TE_MASK                 (0x20U)                 /*!< Transmit Enable                */
#define SCI_SCR_RIE_MASK                (0x40U)                 /*!< Receive Interrupt Enable       */
#define R_SCI_SSR_RDRF_Msk              (0x40UL)                /*!< RDRF (Bitfield-Mask: 0x01)     */ 
#define R_SCI_SSR_TDRE_Msk              (0x80UL)                /*!< TDRE (Bitfield-Mask: 0x01)     */

#define SCI_UART_SEMR_BAUD_SETTING_MASK ((1U << 2U) | (1U << 3U) | (1U << 4U) | (1U << 6U))
#define SCI_UART_START_BIT_FALLING_EDGE (0x1) 

#define UART_PARITY_OFF                 (0U)                    /*!< No parity                      */
#define UART_STOP_BITS_1                (0U)                    /*!< Stop bit 1-bit                 */

#define UART_RX_IRQn                    (24U)



/************************************************************************************
* 			                CORTEX-M4 ARCH SPECIFIC				
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
* 			                C HELPER FUNCTIONS				
************************************************************************************/

#define _REG64(base, offset)        (*(volatile uint64_t *)((base) + (offset)))
#define _REG32(base, offset)        (*(volatile uint32_t *)((base) + (offset)))
#define _REG16(base, offset)        (*(volatile uint16_t *)((base) + (offset)))
#define _REG8(base, offset)         (*(volatile uint8_t *)((base) + (offset)))


#endif /* HEXFIVE_PLATFORM_H */
