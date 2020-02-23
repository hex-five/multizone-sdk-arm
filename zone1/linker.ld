/* Copyright(C) 2018 Hex Five Security, Inc. - All Rights Reserved */

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

ENTRY( reset_handler )

MEMORY {
  flash (rxai!w) : ORIGIN = flash + 0x08000, LENGTH = 32K
  itcm  (rxai!w) : ORIGIN = itcm  + 0x08000, LENGTH = 32K
  dtcm  (wxa!ri) : ORIGIN = dtcm  + 0x00000, LENGTH =  4K
}

__end_stack = _sp; 
SECTIONS {
  	__stack_size = DEFINED(__stack_size) ? __stack_size : 2K;
    /* Put startup code into FLASH, ALWAYS DO THIS FIRST */


    /* Put program code and other data into FLASH */
    .text : {
        . = ALIGN(4);
        __text_start = .;
		
        KEEP(*(.text.isr_vector));
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame)

        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);
        __text_end = .;
    } > itcm AT>flash

    /* Put constant (read-only) data into FLASH */
    .rodata : {
        . = ALIGN(4);
        __rodata_start = .;

        *(.rodata)
        *(.rodata*)

        . = ALIGN(4);
        __rodata_end = .;
    } > itcm AT>flash

    .ARM.extab : {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > itcm AT>flash

    .ARM : {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > itcm AT>flash

    .preinit_array : {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } > itcm AT>flash
    .init_array : {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } > itcm AT>flash
    .fini_array : {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } > itcm AT>flash

    .lalign         :   {
    PROVIDE( __data_vma_start = . );
    } > itcm AT>flash  

    .data : {
        . = ALIGN(4);
        __data_start = .;

        *(.data)
        *(.data*)

        . = ALIGN(4);
        __data_end = .;
    } > dtcm AT>flash

    .bss : {
        . = ALIGN(4);
        __bss_start = .;
        __bss_start__ = __bss_start;

        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        __bss_end = .;
        __bss_end__ = __bss_end;
    } > dtcm AT>dtcm

  	. = ALIGN(4);
  	PROVIDE( _end = . );
  	PROVIDE( end = . );

	. = ALIGN(4);
	PROVIDE( _end = . );
	PROVIDE( end = . );

	.stack ORIGIN(dtcm) + LENGTH(dtcm) - __stack_size :   {
	PROVIDE( _heap_end = . );
	. = __stack_size;
	PROVIDE( _sp = . );
	} >dtcm AT>dtcm 

    /DISCARD/ : {
        libc.a(*)
        libm.a(*)
        libgcc.a(*)
    }

    .ARM.attributes 0 : {
        *(.ARM.attributes)
    }
}
