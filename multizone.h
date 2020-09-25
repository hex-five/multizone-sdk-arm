/* Copyright(C) 2018 Hex Five Security, Inc. - All Rights Reserved */

#ifndef MULTIZONE_H_
#define MULTIZONE_H_

/************************************************************************************
* 			   MultiZone API - Group A (scheduling and communication) 				
************************************************************************************/

#define MZONE_YIELD() 																\
			asm volatile ( 															\
			"mov	r4, 0x00;"														\
			"svc	0x01;"															\
			:::"r4")

#define MZONE_WFI() 																\
			asm volatile ( 															\
			"mov	r4, 0x01;"														\
			"svc	0x01;"															\
			:::"r4")

#define MZONE_SEND(zone, msg) ({ int sent; 											\
			asm volatile ( 															\
			"mov	r5, %1; 		" 												\
			"ldmia	%2, {r6-r9};	" 												\
			"mov	r4, 0x02;		" 												\
			"svc	0x01; 			" 												\
			"mov	%0, r4;  		" 												\
			: "=r"(sent) 															\
			: "r"((const int)zone), "r"(*(const long int (*)[4]) msg) 				\
			: "r4","r5","r6","r7","r8","r9"); 										\
			sent; 																	\
			})

#define MZONE_RECV(zone, msg) ({ int rcvd;											\
			register uint32_t r6 asm("r6");											\
			register uint32_t r7 asm("r7");											\
			register uint32_t r8 asm("r8");											\
			register uint32_t r9 asm("r9");											\
			asm volatile ( 															\
			"mov	r6, #0; 		" 												\
			"mov	r7, #0; 		" 												\
			"mov	r8, #0; 		" 												\
			"mov	r9, #0; 		" 												\
			"mov	r5, %5; 		" 												\
			"mov	r4, 0x03;		" 												\
			"svc	0x01; 			" 												\
            "mov	%0, r4;			" 												\
			"str 	r6, %1;			" 												\
			"str 	r7, %2;			" 												\
			"str 	r8, %3;			" 												\
			"str 	r9, %4;			" 												\
			: "=r"(rcvd), "=m"(msg[0]), "=m"(msg[4]), "=m"(msg[8]), "=m"(msg[12]) 	\
			: "r"((const int)zone) 													\
			: "r4","r5","r6","r7","r8","r9"); 										\
			rcvd;																	\
			})


/************************************************************************************
* 			   		MultiZone API - Group B (soft-timer) 				
************************************************************************************/

#define MZONE_RDTIME() ({ register uint32_t r5 asm ("r5"), r6 asm ("r6");			\
			 asm volatile ( 														\
			 "mov	r4, 0x04;"														\
			 "svc	0x01;"															\
			 : "=r"(r5), "=r"(r6) 													\
			 :: "r4"); 																\
			 (uint64_t)r5<<32|r6;													\
			 })

#define MZONE_WRTIME(cycles) ({                                                     \
            asm volatile (                                                          \
            "mov    r5, %0;"                                                        \
            "mov    r6, %1;"                                                        \
            "mov    r4, 0x14;"                                                      \
            "svc    0x01;"                                                          \
            :: "r"((uint32_t)cycles), "r"((uint32_t)((uint64_t)cycles>>32))         \
            : "r4", "r5", "r6");                                                    \
            })

#define MZONE_RDTIMECMP() ({ register uint32_t r5 asm ("r5"), r6 asm ("r6");		\
			 asm volatile ( 														\
			 "mov	r4, 0x05;"														\
			 "svc	0x01;"															\
			 : "=r"(r5), "=r"(r6) 													\
			 :: "r4"); 																\
			 (uint64_t)r5<<32|r6;													\
			 })

#define MZONE_WRTIMECMP(cycles) ({													\
			asm volatile ( 															\
			"mov	r5, %0;"														\
			"mov	r6, %1;"														\
			"mov	r4, 0x06;"														\
			"svc	0x01;"															\
			:: "r"((uint32_t)cycles), "r"((uint32_t)(cycles>>32))					\
			: "r4", "r5", "r6"); 													\
			})

#define MZONE_ADTIMECMP(cycles) ({													\
			asm volatile ( 															\
			"mov	r5, %0;"														\
			"mov	r6, %1;"														\
			"mov	r4, 0x07;"														\
			"svc	0x01;"															\
			:: "r"((uint32_t)cycles), "r"((uint32_t)(cycles>>32))					\
			: "r4", "r5", "r6"); 													\
			})


/************************************************************************************
* 			   MultiZone API - Group C (architectural-specific) 				
************************************************************************************/

#define LOAD_SCB(scb_reg) ({ register uint32_t r5 asm ("r5"); 						\
			asm volatile ( 															\
			"mov	r5, %1;"														\
			"mov	r4, 0x08;"														\
			"svc	0x01;"															\
			: "=r"(r5)																\
			: "r"((uint32_t)scb_reg)												\
			: "r4"); 																\
			(uint32_t) r5;															\
			})

#define SCS_SCB_CPUID		0
#define SCS_SCB_VTOR		1
	/* ... */

#define STORE_NVICISER(irq) ({														\
			uint32_t mask0 = (irq<47&&irq>15)?(((uint32_t) 0x1) <<(irq-16)):0;		\
			uint32_t mask1 = (irq<79&&irq>47)?(((uint32_t) 0x1) <<(irq-48)):0;		\
			uint32_t mask2 = (irq<111&&irq>79)?(((uint32_t) 0x1) <<(irq-80)):0;		\
			uint32_t mask3 = (irq<128&&irq>111)?(((uint32_t) 0x1)<<(irq-112)):0;	\
			asm volatile ( 															\
			"mov    r5, %0; " 														\
			"mov    r6, %1; " 														\
			"mov    r7, %2; " 														\
			"mov    r8, %3; " 														\
			"mov	r4, 0x09;"														\
			"svc	0x01;"															\
			: : "r"((uint32_t)mask0),"r"((uint32_t)mask1),							\
			"r"((uint32_t)mask2), "r"((uint32_t)mask3)								\
			: "r4","r5","r6","r7","r8");											\
			})

#define STORE_NVICICER(irq) ({														\
			uint32_t mask0 = (irq<47&&irq>15)?(((uint32_t) 0x1) <<(irq-16)):0;		\
			uint32_t mask1 = (irq<79&&irq>47)?(((uint32_t) 0x1) <<(irq-48)):0;		\
			uint32_t mask2 = (irq<111&&irq>79)?(((uint32_t) 0x1) <<(irq-80)):0;		\
			uint32_t mask3 = (irq<128&&irq>111)?(((uint32_t) 0x1)<<(irq-112)):0;	\
			asm volatile ( 															\
			"mov    r5, %0; " 														\
			"mov    r6, %1; " 														\
			"mov    r7, %2; " 														\
			"mov    r8, %3; " 														\
			"mov	r4, 0x0A;"														\
			"svc	0x01;"															\
			: : "r"((uint32_t)mask0),"r"((uint32_t)mask1),							\
			"r"((uint32_t)mask2), "r"((uint32_t)mask3)								\
			: "r4","r5","r6","r7","r8");											\
			})

#define LOAD_MPURBAR(val) ({ register uint32_t r5 asm ("r5"); 						\
			asm volatile ( 															\
			"mov	r5, %1;"														\
			"mov	r4, 0x0B;"														\
			"svc	0x01;"															\
			: "=r"(r5)																\
			: "r"((uint32_t)val)													\
			: "r4"); 																\
			(uint32_t) r5;															\
			})

#define LOAD_MPURASR(val) ({ register uint32_t r5 asm ("r5"); 						\
			asm volatile ( 															\
			"mov	r5, %1;"														\
			"mov	r4, 0x0C;"														\
			"svc	0x01;"															\
			: "=r"(r5)																\
			: "r"((uint32_t)val)													\
			: "r4"); 																\
			(uint32_t) r5;															\
			})


/************************************************************************************
* 			MultiZone API - Group D (zone, kernel, interrupt stats) 				
************************************************************************************/

#define MZONE_RDCYCCNT() ({ register uint32_t r5 asm ("r5"); 						\
			 asm volatile ( 														\
			 "mov	r4, 0x0D;"														\
			 "svc	0x01;"															\
			 : "=r"(r5)																\
			 :: "r4"); 																\
			 (uint32_t) r5;															\
			 })

#define MZONE_WRCYCCNT(val) ({														\
			asm volatile (															\
			"mov	r5, %0;"														\
			"mov	r4, 0x0E;"														\
			"svc	0x01;"															\
			:: "r"((uint32_t)val)													\
			: "r4", "r5"); 															\
			})

#define MZONE_RDINSTR() ({ register uint32_t r5 asm ("r5"); 						\
			 asm volatile ( 														\
			 "mov	r4, 0x0F;"														\
			 "svc	0x01;"															\
			 : "=r"(r5)																\
			 :: "r4"); 																\
			 (uint32_t) r5;})


#define MZONE_RDKCYCCNT()({ register uint32_t r5 asm ("r5"); 						\
			 asm volatile ( 														\
			 "mov	r4, 0x10;"														\
			 "svc	0x01;"															\
			 : "=r"(r5)																\
			 :: "r4"); 																\
			 (uint32_t) r5;})

#define MZONE_RDKINSTR()({ register uint32_t r5 asm ("r5"); 						\
			 asm volatile ( 														\
			 "mov	r4, 0x11;"														\
			 "svc	0x01;"															\
			 : "=r"(r5)																\
			 :: "r4"); 																\
			 (uint32_t) r5;})

#define MZONE_RDKCYCCNT_IRQ()({ register uint32_t r5 asm ("r5");					\
			 asm volatile ( 														\
			 "mov	r4, 0x12;"														\
			 "svc	0x01;"															\
			 : "=r"(r5)																\
			 :: "r4"); 																\
			 (uint32_t) r5;})

#define MZONE_RDKINSTR_IRQ()({ register uint32_t r5 asm ("r5");						\
			 asm volatile ( 														\
			 "mov	r4, 0x13;"														\
			 "svc	0x01;"															\
			 : "=r"(r5)																\
			 :: "r4"); 																\
			 (uint32_t) r5;})


/************************************************************************************
* 			   				Privileged Pseudoinstructions 				
************************************************************************************/


/* Global Interrupt enable (using the instruction CPSIE i) */
__attribute__((always_inline))
static inline void __enable_irq(void){
	__asm volatile ("cpsie i" : : : "memory");
}

/* Global Interrupt disable (using the instruction CPSID i) */
__attribute__((always_inline))
static inline void __disable_irq(void){
	__asm volatile ("cpsid i" : : : "memory");
}

/* Global Fault exception and Interrupt enable (using the instruction CPSIE f) */
__attribute__((always_inline))
static inline void __enable_fault_irq(void){
	__asm volatile ("cpsie f" : : : "memory");
}

/* 	Global Fault exception and Interrupt disable (using the instruction CPSID f) */
__attribute__((always_inline))
static inline void __disable_fault_irq(void){
	__asm volatile ("cpsid f" : : : "memory");
}

/* Assign value to Priority Mask Register (using the instruction MSR) */
__attribute__((always_inline))
static inline void __set_PRIMASK(int primask){
	__asm volatile ("msr primask, %0" : : "r" (primask) : "memory");
}

/* Return Priority Mask Register (using the instruction MRS) */
__attribute__((always_inline))
static inline int __get_PRIMASK(void){
	int primask;
	__asm volatile ("mrs %0, primask" : "=r" (primask) :: "memory");
	return(primask);
}

/* Assign value to Fault Mask Register (using the instruction MSR) */
__attribute__((always_inline))
static inline void __set_FAULTMASK(int faultmask){
	__asm volatile ("msr faultmask, %0" : : "r" (faultmask) : "memory");
}

/* Return Fault Mask Register (using the instruction MRS) */
__attribute__((always_inline))
static inline int __get_FAULTMASK(void){
	int faultmask;
	__asm volatile ("mrs %0, faultmask" : "=r" (faultmask) );
	return(faultmask);
}

/* Set Base Priority (using the instruction MSR) */
__attribute__((always_inline))
static inline void __set_BASEPRI(int basepri){
	__asm volatile ("msr basepri, %0" : : "r" (basepri) : "memory");
}

/* Return Base Priority (using the instruction MRS) */
__attribute__((always_inline))
static inline int __get_BASEPRI(void){
	int basepri;
	__asm volatile ("mrs %0, basepri" : "=r" (basepri) );
	return(basepri);
}

/* Set CONTROL register value (using the instruction MSR) */
__attribute__((always_inline))
static inline void __set_CONTROL(int control){
	__asm volatile ("msr control, %0" : : "r" (control) : "memory");
}

/* Return CONTROL Register Value (using the instruction MRS) */
__attribute__((always_inline))
static inline int __get_CONTROL(void){
	int control;
	__asm volatile ("mrs %0, control" : "=r" (control) );
	return(control);
}

/* Set Process Stack Pointer value (using the instruction MSR) */
__attribute__((always_inline))
static inline void __set_PSP(int psp){
  __asm volatile ("msr psp, %0" : : "r" (psp) : );
}

/* Return Process Stack Pointer (using the instruction MRS) */
__attribute__((always_inline))
static inline int __get_PSP(void){
  int psp;
  __asm volatile ("mrs %0, psp"  : "=r" (psp) );
  return(psp);
}

/* Set Main Stack Pointer (using the instruction MSR) */
__attribute__((always_inline))
static inline void __set_MSP(int msp){
  __asm volatile ("msr msp, %0" : : "r" (msp) : );
}

/* Return Main Stack Pointer (using the instruction MRS) */
__attribute__((always_inline))
static inline int __get_MSP(void)
{
  int msp;
  __asm volatile ("mrs %0, msp" : "=r" (msp) );
  return(msp);
}

/* Data Synchronization Memory Barrier */
__attribute__((always_inline))
static inline void __DSB(){
	__asm volatile ("dsb 0xF");
}

/* Instruction Synchronization Barrier */
__attribute__((always_inline))
static inline void __ISB(){
	__asm volatile ("isb 0xF");
}

/* Wait for Interrupt */
__attribute__((always_inline))
static inline void __WFI(){
	__asm volatile ("wfi");
}


#endif /* MULTIZONE_H */
