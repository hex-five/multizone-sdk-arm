/* Copyright(C) 2018 Hex Five Security, Inc. - All Rights Reserved */

# Make sure that the GNU assembler is using a modern syntax for Arm THUMB.
	.syntax	unified
	.arch	armv7e-m

/**
 * These are the addresses for the initialized (data) and uninitialized (bss)
 * variables. The initialized variables will be copied from FLASH to RAM. The
 * uninitialized variables will be set to 0. These addresses are set in the
 * linker file.
 */
.word __data_vma_start
.word __data_start
.word __data_end
.word __bss_start
.word __bss_end

# TODO - Consider to move the vector table definition to the bsp
#        since the vector table is specific to the CPU/BOARD
# -------------------------------------------------------------
.section        .text.isr_vector
.align 			2
.globl	__isr_vector
# -------------------------------------------------------------
__isr_vector:
        .word   __end_stack        	// MSP definition
        .word   reset_handler 		// Reset_Handler
        .word   nmi_handler       	// NMI_Handler
        .word   hardfault_handler 	// HardFault_Handler
        .word   memmanage_handler	// MemManage_Handler
        .word   busfault_handler    	// BusFault_Handler
        .word   usagefault_handler	// UsageFault_Handler
        .word   0                  	// Not Defined
        .word   0                  	// Not Defined
        .word   0                  	// Not Defined
        .word   0                  	// Not Defined
        .word   svc_handler       	// SVC_Handler
        .word   debugmon_handler 	// DebugMon_Handler
        .word   0                  	// Not Defined
        .word   pendsv_handler     	// PendSV_Handler
        .word   systick_handler    	// SysTick_Handler
		.rept	37					// Repeat for 
		.word   _def_handler        // IRQ0_Handler to IRQ39_Handler 
		.endr
		.word   uart_handler        // USART Handler (USART0)
		.word   _def_handler
		.word   _def_handler
		.word   btn_handler        	// Button Handler (EXTI10_15_IRQn)
        .rept   27               	// Repeat for 
        .word   _def_handler       	// IRQ41_Handler to IRQ67_Handler 
        .endr
	.size	__isr_vector, . - __isr_vector

# -------------------------------------------------------------
.align 			2
.section        .text.init
.global        	reset_handler
.type           reset_handler, %function
# -------------------------------------------------------------
reset_handler:
	ldr   sp, =__end_stack      /* set stack pointer */

// Copy the initialized global variables to RAM
	mov  r0, #0
	ldr  r1, = __data_start
	ldr  r2, = __data_end
	ldr  r3, = __data_vma_start
	b    loopcopy_data

copy_data:
	ldr  r4, [r3, r0]
	str  r4, [r1, r0]
	adds r0, r0, #4

loopcopy_data:
	add  r4, r1, r0
	cmp  r4, r2
	bcc  copy_data

// Fill uninitialized variables with zeros
	mov  r0, #0
	ldr  r1, = __bss_start
	ldr  r2, = __bss_end
	b    loopfill_zerobss

fill_zerobss:
	str  r0, [r1]
	add  r1, r1, #4

loopfill_zerobss:
	cmp  r1, r2
	bcc  fill_zerobss

// Call the libc init function
	bl   __libc_init_array

// Call the main function
	bl   main


	.global _init
  	.type   _init, %function
_init:
	bx lr
  	.size  _init, .-_init

	.global _fini
  	.type   _fini, %function
_fini:
	bx lr
  	.size  _fini, .-_fini

# -------------------------------------------------------------
.section        .text.nmi_handler
.type           nmi_handler, %function
.weak           nmi_handler               
.thumb_set      nmi_handler,_def_handler

# -------------------------------------------------------------
.section        .text.hardfault_handler
.type           hardfault_handler, %function
.weak           hardfault_handler               
.thumb_set      hardfault_handler,_def_handler

# -------------------------------------------------------------
.section        .text.memmanage_handler
.type           memmanage_handler, %function
.weak           memmanage_handler               
.thumb_set      memmanage_handler,_def_handler

# -------------------------------------------------------------
.section        .text.busfault_handler
.type           busfault_handler, %function
.weak           busfault_handler               
.thumb_set      busfault_handler,_def_handler

# -------------------------------------------------------------
.section        .text.usagefault_handler
.type           usagefault_handler, %function
.weak           usagefault_handler               
.thumb_set      usagefault_handler,_def_handler

# -------------------------------------------------------------
.section        .text.svc_handler
.type           svc_handler, %function
.weak           svc_handler               
.thumb_set      svc_handler,_def_handler

# -------------------------------------------------------------
.section        .text.debugmon_handler
.type           debugmon_handler, %function
.weak           debugmon_handler               
.thumb_set      debugmon_handler,_def_handler

# -------------------------------------------------------------
.section        .text.pendsv_handler
.type           pendsv_handler, %function
.weak           pendsv_handler               
.thumb_set      pendsv_handler,_def_handler

# -------------------------------------------------------------
.section        .text.systick_handler
.type           systick_handler, %function
.weak           systick_handler               
.thumb_set      systick_handler,_def_handler


# -------------------------------------------------------------
.section        .text.btn_handler
.type           btn_handler, %function
.weak           btn_handler               
.thumb_set      btn_handler,_def_handler

# -------------------------------------------------------------
.section        .text.uart_handler
.type           uart_handler, %function
.weak           uart_handler               
.thumb_set      uart_handler,_def_handler

# -------------------------------------------------------------
.section        .text._def_handler
.type           _def_handler, %function
# -------------------------------------------------------------
# -------------------------------------------------------------
_def_handler:     # Default Handler (Exception happen while starting)
# -------------------------------------------------------------
	b    reset_handler             // restart

