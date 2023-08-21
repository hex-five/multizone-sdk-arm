/* Copyright(C) 2023 Hex Five Security, Inc. - All Rights Reserved */

ENTRY( _boot )

MEMORY {
  flash (rxai!w) : ORIGIN = flash + 0x2000, LENGTH = 2K
  ram   (wxa!ri) : ORIGIN = dtcm  + 0x1800, LENGTH = 2K
}

SECTIONS {
    .boot : { KEEP(*(.text.vec)); KEEP(*(.text.boot)); . = ALIGN(4); } > flash
}

_stack_end = ORIGIN(ram) + LENGTH(ram);