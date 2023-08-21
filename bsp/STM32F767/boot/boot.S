/* Copyright(C) 2023 Hex Five Security, Inc. - All Rights Reserved */

/**
 * Hardware setup / OEM low-level boot code
 * - pass this file to multizone.jar via --boot option
 * - run in privileged mode after policy integrity check
 * - resume execution of MultiZone boot via MZONE_WFI()
 */

# Make sure that the GNU assembler is using a modern syntax for Arm THUMB.
        .syntax	unified
        .arch	armv7e-m

# -------------------------------------------------------------
.align      2
.section    .text.vec
.type       _vec_tbl, %object
# -------------------------------------------------------------
_vec_tbl:
        .word   _stack_end  // MSP definition
        .word   _boot       // Reset_Handler
        .word   _boot       // NMI_Handler

# -------------------------------------------------------------
.align 		2
.section    .text.boot
.global     _boot
.type       _boot, %function
# -------------------------------------------------------------
_boot:
        # Hardware setup code goes here
        nop
        nop

        # Resume MultiZone boot (MZONE_WFI)
        movs    r4, 0x1
        svc     0x1
