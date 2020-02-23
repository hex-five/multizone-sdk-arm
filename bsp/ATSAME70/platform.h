/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

#ifndef HEXFIVE_PLATFORM_H
#define HEXFIVE_PLATFORM_H


/************************************************************************************
* 			               ATSAME70-XPLD PLATFORM GERENIC			
************************************************************************************/

#define CPU_FREQ                        (300000000)             /*!< Hz */
#define RTC_FREQ                        (300000000)             /*!< Hz */

#define MPU_REGIONS                     (16)

#define UART_IRQn                       USART1_IRQn 
#define USART1_RX_PIN                   (21)
#define USART1_TX_PIN                   (4)

#define LED                             LED0
#define LED_PIN                         LED0_PIN

#define LED0                            (8)
#define LED0_PIN                        (1 << LED0)

#define BTN                             SW0
#define BTN_PIN                         SW0_PIN
#define BTN_IRQn                        SW0_IRQn

#define SW0                             (11)
#define SW0_PIN                         (11)
#define SW0_IRQn                        PIOA_IRQn

#define PIOA_IRQn                       26

#define SPI_TDI                         (11) 	                /*!< in 	    - D5 (PD11) */
#define SPI_TCK                         (27)	                /*!< out (master)   - D4 (PD27) */
#define SPI_TDO                         (6)	                /*!< out	    - D3 (PA6)  */



/************************************************************************************
* 			            ATSAME70Q21 PERIPHERALS SPECIFIC				
************************************************************************************/


/* Power Management Controller (PMC) */
#define PMC_BASE                        (0x400E0600)            /*!< PMC Base Address                               */
#define PMC_REG(offset)                 _REG32(PMC_BASE, offset)

#define PMC_PCER0                       (0x10)
#define CKGR_MOR                        (0x20)                  /*!< Main Oscillator Register                       */
#define CKGR_PLLAR                      (0x28)
#define PMC_MCKR                        (0x30)                  /*!< Master Clock Register                          */
#define PMC_SR                          (0x68)                  /*!< Status Register                                */

#define CKGR_MOR_MOSCXTEN_Pos           (0)                     /*!< Main Crystal Oscillator Enable Position        */
#define CKGR_MOR_MOSCXTEN_Msk           ((0x1) << CKGR_MOR_MOSCXTEN_Pos)       
#define CKGR_MOR_MOSCXTEN               CKGR_MOR_MOSCXTEN_Msk    
#define CKGR_MOR_MOSCXTBY_Pos           (1)                     /*!< Main Crystal Oscillator Bypass Position        */
#define CKGR_MOR_MOSCXTBY_Msk           ((0x1) << CKGR_MOR_MOSCXTBY_Pos) 
#define CKGR_MOR_MOSCXTBY               CKGR_MOR_MOSCXTBY_Msk   
#define CKGR_MOR_MOSCXTST_Pos           (8)                     /*!< Main Crystal Oscillator Startup Time Position  */
#define CKGR_MOR_MOSCXTST_Msk           ((0xFF) << CKGR_MOR_MOSCXTST_Pos)          
#define CKGR_MOR_MOSCXTST(value)        (CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos))
#define CKGR_MOR_KEY_Pos                (16)                    /*!< Write Access Password Position                 */
#define CKGR_MOR_KEY_Msk                ((0xFF) << CKGR_MOR_KEY_Pos)           
#define CKGR_MOR_KEY(value)             (CKGR_MOR_KEY_Msk & ((value) << CKGR_MOR_KEY_Pos))
#define CKGR_MOR_KEY_PASSWD_Val         (0x37)                                     
#define CKGR_MOR_KEY_PASSWD             (CKGR_MOR_KEY_PASSWD_Val << CKGR_MOR_KEY_Pos)  
#define CKGR_MOR_MOSCSEL_Pos            (24)                    /*!< Main Clock Oscillator Selection Position       */
#define CKGR_MOR_MOSCSEL_Msk            ((0x1) << CKGR_MOR_MOSCSEL_Pos)          
#define CKGR_MOR_MOSCSEL                CKGR_MOR_MOSCSEL_Msk    

#define CKGR_PLLAR_DIVA_Pos             (0)                     /*!< PLLA Front End Divider Position */
#define CKGR_PLLAR_DIVA_Msk             ((0xFF) << CKGR_PLLAR_DIVA_Pos)             
#define CKGR_PLLAR_DIVA(value)          (CKGR_PLLAR_DIVA_Msk & ((value) << CKGR_PLLAR_DIVA_Pos))
#define CKGR_PLLAR_PLLACOUNT_Pos        (8)                     /*!< PLLA Counter Position */
#define CKGR_PLLAR_PLLACOUNT_Msk        ((0x3F) << CKGR_PLLAR_PLLACOUNT_Pos)     
#define CKGR_PLLAR_PLLACOUNT(value)     (CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos))
#define CKGR_PLLAR_MULA_Pos             (16)                    /*!< PLLA Multiplier Position */
#define CKGR_PLLAR_MULA_Msk             ((0x7FF) << CKGR_PLLAR_MULA_Pos)      
#define CKGR_PLLAR_MULA(value)          (CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos))
#define CKGR_PLLAR_ONE_Pos              (29)                    /*!< Must Be Set to 1 Position */
#define CKGR_PLLAR_ONE_Msk              ((0x1) << CKGR_PLLAR_ONE_Pos)
#define CKGR_PLLAR_ONE                  CKGR_PLLAR_ONE_Msk 

#define PMC_MCKR_CSS_Pos                (0)                     /*!< Master Clock Source Selection Position         */
#define PMC_MCKR_CSS_Msk                ((0x3) << PMC_MCKR_CSS_Pos)             
#define PMC_MCKR_CSS(value)             (PMC_MCKR_CSS_Msk & ((value) << PMC_MCKR_CSS_Pos))
#define PMC_MCKR_PRES_Pos               (4)                     /*!< Processor Clock Prescaler Position             */
#define PMC_MCKR_PRES_Msk               ((0x7) << PMC_MCKR_PRES_Pos)             
#define PMC_MCKR_PRES(value)            (PMC_MCKR_PRES_Msk & ((value) << PMC_MCKR_PRES_Pos))
#define PMC_MCKR_MDIV_Pos               (8)                     /*!< Master Clock Division Position                 */
#define PMC_MCKR_MDIV_Msk               ((0x3) << PMC_MCKR_MDIV_Pos)            
#define PMC_MCKR_MDIV(value)            (PMC_MCKR_MDIV_Msk & ((value) << PMC_MCKR_MDIV_Pos))

#define PMC_SR_MOSCXTS_Pos              (0)                     /*!< Main Crystal Oscillator Status Position        */
#define PMC_SR_MOSCXTS_Msk              ((0x1) << PMC_SR_MOSCXTS_Pos)             
#define PMC_SR_MOSCXTS                  PMC_SR_MOSCXTS_Msk         
#define PMC_SR_LOCKA_Pos                (1)                     /*!< PLLA Lock Status Position                      */
#define PMC_SR_LOCKA_Msk                ((0x1) << PMC_SR_LOCKA_Pos)        
#define PMC_SR_LOCKA                    PMC_SR_LOCKA_Msk                        
#define PMC_SR_MCKRDY_Pos               (3)                     /*!< Master Clock Status Position                   */
#define PMC_SR_MCKRDY_Msk               ((0x1) << PMC_SR_MCKRDY_Pos)                
#define PMC_SR_MCKRDY                   PMC_SR_MCKRDY_Msk     

#define CONF_PLLACK_MUL                 (25)
#define CONF_PLLACK_DIV                 (0x01)
#define PLL_COUNT                       (0x3f)

#define CONF_MCKR_PRESC                 (0)
#define CONF_MCK_DIV                    (1)
#define CONF_CLK_GEN_MCKR_SRC           (2)                


/* Parallel Input/Output (PIO) */
#define PIO_BASE                        (0x400E0E00U) 
#define PIOA                            (PIO_BASE+0x000U)       /*!< PIOA Base Address                              */
#define PIOB                            (PIO_BASE+0x200U)       /*!< PIOB Base Address                              */
#define PIOC                            (PIO_BASE+0x400U)       /*!< PIOC Base Address                              */
#define PIOD                            (PIO_BASE+0x600U)       /*!< PIOD Base Address                              */
#define PIOE                            (PIO_BASE+0x800U)       /*!< PIOE Base Address                              */
#define PIOA_REG(offset)                _REG32(PIOA, offset)
#define PIOB_REG(offset)                _REG32(PIOB, offset)
#define PIOC_REG(offset)                _REG32(PIOC, offset)
#define PIOD_REG(offset)                _REG32(PIOD, offset)

#define PIO_PER                         (0x00)
#define PIO_PDR                         (0x04)
#define PIO_OER                         (0x10)
#define PIO_ODR                         (0x14)
#define PIO_IFER                        (0x20)
#define PIO_SODR                        (0x30)
#define PIO_CODR                        (0x34)
#define PIO_ODSR                        (0x38)
#define PIO_PDSR                        (0x3C)
#define PIO_IER                         (0x40)
#define PIO_IDR                         (0x44)
#define PIO_IMR                         (0x48)
#define PIO_ISR                         (0x4C)
#define PIO_PUER                        (0x64)
#define PIO_ABCDSR0                     (0x70)  
#define PIO_ABCDSR1                     (0x74)  
#define PIO_IFSCDR                      (0x80)
#define PIO_IFSCER                      (0x84)
#define PIO_AIMER                       (0xB0)
#define PIO_ESR                         (0xC0)
#define PIO_FELLSR                      (0xD0)

#define ID_PIOA                         (1 << 10)               /*!< Parallel Input/Output Controller (PIOA)        */
#define ID_PIOC                         (1 << 12)               /*!< Parallel Input/Output Controller (PIOC)        */
#define ID_PIOD                         (1 << 16)               /*!< Parallel Input/Output Controller (PIOD)        */


/* Bus Matrix (MATRIX) */
#define MATRIX                          (0x40088000U)
#define MATRIX_REG(offset)              _REG32(MATRIX, offset)

#define CCFG_SYSIO                      (0x114)                 /*!< System I/O and CAN1 Configuration Register     */


/* Universal Synchronous Asynchronous Receiver Transmitter 1 (USART1) */
#define USART1                          (0x40028000U)           /*!< USART1 Base Address                            */
#define USART1_REG(offset)              _REG32(USART1, offset)

#define ID_USART1                       (14)       

#define US_CR                           (0x00)                  /*!< USART Control Register                         */
#define US_MR                           (0x04)                  /*!< USART Mode Register                            */
#define US_IER                          (0x08)                  /*!< USART Interrupt Enable Register                */
#define US_IMR                          (0x10)                  /*!< USART Interrupt Mask Register                  */
#define US_CSR                          (0x14)                  /*!< USART Channel Status Register                  */
#define US_RHR                          (0x18)                  /*!< USART Receive Holding Register                 */
#define US_THR                          (0x1C)                  /*!< USART Transmit Holding Register                */
#define US_BRGR                         (0x20)                  /*!< USART Baud Rate Generator Register             */
#define US_RTOR                         (0x24)                  /*!< USART Receiver Timeout Register                */
#define US_TTGR                         (0x28)                  /*!< USART Transmitter Timeguard Register           */
#define US_WPMR                         (0xE4)                  /*!< USART Write Protection Mode Register           */

#define US_CR_RSTRX_Pos                 (2)                                              
#define US_CR_RSTRX_Msk                 ((0x1) << US_CR_RSTRX_Pos)                  
#define US_CR_RSTRX                     US_CR_RSTRX_Msk                    
#define US_CR_RSTTX_Pos                 (3)                                              
#define US_CR_RSTTX_Msk                 ((0x1) << US_CR_RSTTX_Pos)                
#define US_CR_RSTTX                     US_CR_RSTTX_Msk                           
#define US_CR_RXEN_Pos                  (4)                                           
#define US_CR_RXEN_Msk                  ((0x1) << US_CR_RXEN_Pos)                 
#define US_CR_RXEN                      US_CR_RXEN_Msk                                 
#define US_CR_RXDIS_Pos                 (5)                                       
#define US_CR_RXDIS_Msk                 ((0x1) << US_CR_RXDIS_Pos)             
#define US_CR_RXDIS                     US_CR_RXDIS_Msk                                
#define US_CR_TXEN_Pos                  (6)                                      
#define US_CR_TXEN_Msk                  ((0x1) << US_CR_TXEN_Pos)              
#define US_CR_TXEN                      US_CR_TXEN_Msk                             
#define US_CR_TXDIS_Pos                 (7)                          
#define US_CR_TXDIS_Msk                 ((0x1) << US_CR_TXDIS_Pos)                  
#define US_CR_TXDIS                     US_CR_TXDIS_Msk                               
#define US_CR_RSTSTA_Pos                (8)                                              
#define US_CR_RSTSTA_Msk                ((0x1) << US_CR_RSTSTA_Pos)                
#define US_CR_RSTSTA                    US_CR_RSTSTA_Msk
#define US_CR_USART_RTSDIS_Pos          (19)                                        
#define US_CR_USART_RTSDIS              ((0x1) << US_CR_USART_RTSDIS_Pos)  

#define US_MR_Val                       (0x1008c0)

#define US_CSR_RXRDY_Pos                (0)                     /*!< Receiver Ready Position            */
#define US_CSR_RXRDY_Msk                ((0x1) << US_CSR_RXRDY_Pos)                
#define US_CSR_RXRDY                    US_CSR_RXRDY_Msk                             
#define US_CSR_TXRDY_Pos                (1)                     /*!< Transmitter Ready Position         */
#define US_CSR_TXRDY_Msk                ((0x1) << US_CSR_TXRDY_Pos)                 
#define US_CSR_TXRDY                    US_CSR_TXRDY_Msk      

#define US_BRGR_Val                     (196689)

#define US_WPMR_WPKEY_Pos               (8)                     /*!< Write Protection Key Position      */
#define US_WPMR_WPKEY_PASSWD_Val        (0x555341)            
#define US_WPMR_WPKEY_PASSWD            (US_WPMR_WPKEY_PASSWD_Val << US_WPMR_WPKEY_Pos)

#define US_IMR_RXRDY_Pos                (0)                     /*!< RXRDY Interrupt Mask Position      */
#define US_IMR_RXRDY_Msk                ((0x1) << US_IMR_RXRDY_Pos) 
#define US_IMR_RXRDY                    US_IMR_RXRDY_Msk 

#define USART1_IRQn                     (30)


/* EFC FLASH */
#define EFC                             (0x400E0C00)            /*!< EFC Base Address                   */
#define EFC_REG(offset)                 _REG32(EFC, offset)

#define EEFC_FMR                        (0x00)                  /*!< EEFC Flash Mode Register           */

#define EEFC_FMR_FWS_Pos                (8)                     /*!< Flash Wait State Position          */
#define EEFC_FMR_FWS_Msk                ((0xF) << EEFC_FMR_FWS_Pos)         
#define EEFC_FMR_FWS(value)             (EEFC_FMR_FWS_Msk & ((value) << EEFC_FMR_FWS_Pos))

#define CONF_EFC_WAIT_STATE             (5)



/************************************************************************************
* 			                CORTEX-M7 ARCH SPECIFIC				
************************************************************************************/

/* System Control Space */
#define SCS_BASE                        (0xE000E000UL)          /*!< System Control Space (0xE000E000-0xE000EFFF) */
#define MISC_BASE                       (SCS_BASE + 0x0000UL)   /*!< Misc System Control Registers (0xE000E000-0xE000E00F) */ 
#define SYSTICK_BASE                    (SCS_BASE + 0x0010UL)   /*!< SysTick Timer (0xE000E010-0xE000E01F) */
#define NVIC_BASE                       (SCS_BASE + 0x0100UL)   /*!< Nested Vectored Interrupt Controller (0xE000E100-) */
#define SCB_BASE                        (SCS_BASE + 0x0D00UL)   /*!< System Control Block (0xE000E0D0-) */
#define MPU_BASE                        (SCS_BASE + 0x0D90UL)   /*!< Memory Protection Unit (0xE000ED90-) */

/* System Control Block (SCB) */
#define SCB_CPUID                       (SCB_BASE + 0x00UL)     /*!< CPUID Base Register */
#define SCB_ICSR                        (SCB_BASE + 0x04UL)     /*!< Interrupt Control and State Register */
#define SCB_VTOR                        (SCB_BASE + 0x08UL)     /*!< Vector Table Offset Register */
#define SCB_AIRCR                       (SCB_BASE + 0x0CUL)     /*!< Application Interrupt and Reset Control Register */
#define SCB_SCR                         (SCB_BASE + 0x10UL)     /*!< System Control Register */
#define SCB_CCR                         (SCB_BASE + 0x14UL)     /*!< Configuration and Control Register */
#define SCB_SHPR1                       (SCB_BASE + 0x18UL)     /*!< System Handler Priority Register 1 */
#define SCB_SHPR2                       (SCB_BASE + 0x1CUL)     /*!< System Handler Priority Register 2 */
#define SCB_SHPR3                       (SCB_BASE + 0x20UL)     /*!< System Handler Priority Register 3 */
#define SCB_SHCSR                       (SCB_BASE + 0x24UL)     /*!< System Handler Control and State Register */
#define SCB_CFSR                        (SCB_BASE + 0x28UL)     /*!< Configurable Fault Status Register */
#define SCB_HFSR                        (SCB_BASE + 0x2CUL)     /*!< HardFault Status Register */
#define SCB_DFSR                        (SCB_BASE + 0x30UL)     /*!< Debug Fault Status Register */
#define SCB_MMFAR                       (SCB_BASE + 0x34UL)     /*!< MemManage Fault Address Register */
#define SCB_BFAR                        (SCB_BASE + 0x38UL)     /*!< BusFault Address Register */
#define SCB_AFSR                        (SCB_BASE + 0x3CUL)     /*!< Auxiliary Fault Status Register */
#define SCB_CPACR                       (SCB_BASE + 0x88UL)     /*!< Coprocessor Access Control Register */

/* Memory Protection Unit (MPU) */
#define MPU_TYPE                        (MPU_BASE + 0x00UL)     /*!< MPU Type Register */
#define MPU_CTRL                        (MPU_BASE + 0x04UL)     /*!< MPU Control Register */
#define MPU_RNR                         (MPU_BASE + 0x08UL)     /*!< MPU Region Number Register */
#define MPU_RBAR                        (MPU_BASE + 0x0CUL)     /*!< MPU Region Base Address Register */
#define MPU_RASR                        (MPU_BASE + 0x10UL)     /*!< MPU Region Attribute and Size Register */
#define MPU_RBAR1                       (MPU_BASE + 0x14UL)     /*!< MPU Region Base Address Alias1 Register */
#define MPU_RASR1                       (MPU_BASE + 0x18UL)     /*!< MPU Region Attribute and Size Alias1 Register */
#define MPU_RBAR2                       (MPU_BASE + 0x1CUL)     /*!< MPU Region Base Address Alias2 Register */
#define MPU_RASR2                       (MPU_BASE + 0x20UL)     /*!< MPU Region Attribute and Size Alias2 Register */
#define MPU_RBAR3                       (MPU_BASE + 0x24UL)     /*!< MPU Region Base Address Alias3 Register */
#define MPU_RASR3                       (MPU_BASE + 0x28UL)     /*!< MPU Region Attribute and Size Alias3 Register */



/************************************************************************************
* 			                    HELPERS				
************************************************************************************/

#define _REG64(base, offset)            (*(volatile uint64_t *)((base) + (offset)))
#define _REG32(base, offset)            (*(volatile uint32_t *)((base) + (offset)))
#define _REG16(base, offset)            (*(volatile uint16_t *)((base) + (offset)))
#define _REG8(base, offset)             (*(volatile uint8_t *)((base) + (offset)))


#endif /* HEXFIVE_PLATFORM_H */
