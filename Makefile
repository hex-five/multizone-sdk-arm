# Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved

#############################################################
# Platform definitions
#############################################################

BOARD ?= STM32F767
ifeq ($(BOARD),STM32F767)
   ARM_ARCH := armv7e-m
   ARM_CPU := cortex-m7
   ARM_FLOAT := soft
   ARM_FPU := fpv5-sp-d16
else ifeq ($(BOARD),ATSAME70)
   ARM_ARCH := armv7e-m
   ARM_CPU := cortex-m7
   ARM_FLOAT := softfp
   ARM_FPU := fpv4-sp-d16	
else ifeq ($(BOARD),IMXRT1020)
   ARM_ARCH := armv7e-m
   ARM_CPU := cortex-m7
   ARM_FLOAT := soft
   ARM_FPU := fpv5-d16	
else ifeq ($(BOARD),EKRA6M3)
   ARM_ARCH := armv7e-m
   ARM_CPU := cortex-m4
   ARM_FLOAT := soft
   ARM_FPU := fpv5-sp-d16
else ifeq ($(BOARD),GD32307)
   ARM_ARCH := armv7e-m
   ARM_CPU := cortex-m4
   ARM_FLOAT := soft
   ARM_FPU := fpv5-sp-d16
else 
   $(error Unsupported board $(BOARD))
endif

#############################################################
# Arguments/variables available to all submakes
#############################################################

export BOARD
export ARM_ARCH
export ARM_CPU
export ARM_FLOAT
export ARM_FPU

#############################################################
# Toolchain definitions
#############################################################

ifndef GNU_ARM
   $(error GNU_ARM (GNU Arm Embedded Toolchain) not set)
endif

export CROSS_COMPILE := $(abspath $(GNU_ARM))/arm-none-eabi-
export CC      := $(CROSS_COMPILE)gcc
export OBJDUMP := $(CROSS_COMPILE)objdump
export OBJCOPY := $(CROSS_COMPILE)objcopy
export GDB     := $(CROSS_COMPILE)gdb
export AR      := $(CROSS_COMPILE)ar
export LD      := $(CROSS_COMPILE)gcc

#############################################################
# Rules for building multizone
#############################################################

.PHONY: all 
all: clean
	$(MAKE) -C bsp/$(BOARD)/boot
	$(MAKE) -C zone1
	$(MAKE) -C zone2
	$(MAKE) -C zone3
	java -jar multizone.jar \
	--arch $(BOARD) \
	--config bsp/$(BOARD)/multizone.cfg \
	--boot bsp/$(BOARD)/boot/boot.hex \
	zone1/zone1.elf \
	zone2/zone2.elf \
	zone3/zone3.elf 

.PHONY: clean
clean: 
	$(MAKE) -C bsp/$(BOARD)/boot clean
	$(MAKE) -C zone1 clean
	$(MAKE) -C zone2 clean
	$(MAKE) -C zone3 clean
	rm -f multizone.hex

#############################################################
# Load and debug variables and rules
#############################################################

ifndef OPENOCD
$(error OPENOCD not set)
endif

OPENOCD := $(abspath $(OPENOCD))/bin/openocd

ifeq ($(BOARD),STM32F767)
   OPENOCDCFG1 ?= bsp/$(BOARD)/stlink.cfg
   OPENOCDCFG2 ?= bsp/$(BOARD)/openocd.cfg
   OPENOCDARGS += -f $(OPENOCDCFG1) -f $(OPENOCDCFG2)
else ifeq ($(BOARD),ATSAME70)
   OPENOCDARGS += -f bsp/$(BOARD)/atsame70.cfg
else ifeq ($(BOARD),IMXRT1020)
   OPENOCDCFG1 ?= bsp/$(BOARD)/cmsis-dap.cfg
   OPENOCDCFG2 ?= bsp/$(BOARD)/imxrt1020.cfg
   OPENOCDARGS += -f $(OPENOCDCFG1) -f $(OPENOCDCFG2)
else ifeq ($(BOARD),EKRA6M3)
   OPENOCDCFG1 ?= bsp/$(BOARD)/jlink.cfg
   OPENOCDCFG2 ?= bsp/$(BOARD)/ra6m3.cfg
   OPENOCDARGS += -f $(OPENOCDCFG1) -f $(OPENOCDCFG2)
else ifeq ($(BOARD),GD32307)
   OPENOCDCFG1 ?= bsp/$(BOARD)/gdlink.cfg
   OPENOCDARGS += -f $(OPENOCDCFG1)
endif

GDB_PORT ?= 3333
GDB_LOAD_ARGS ?= --batch
GDB_LOAD_CMDS += -ex "set mem inaccessible-by-default off"
GDB_LOAD_CMDS += -ex "set remotetimeout 240"
GDB_LOAD_CMDS += -ex "set arch $(BOARD):$(ARCH)"
GDB_LOAD_CMDS += -ex "target extended-remote localhost:$(GDB_PORT)"
GDB_LOAD_CMDS += -ex "monitor reset halt"
GDB_LOAD_CMDS += -ex "monitor flash protect 0 64 last off"
GDB_LOAD_CMDS += -ex "load"
GDB_LOAD_CMDS += -ex "monitor resume"
GDB_LOAD_CMDS += -ex "monitor shutdown"
GDB_LOAD_CMDS += -ex "quit"

.PHONY: load

load:
	$(OPENOCD) $(OPENOCDARGS) & \
	$(GDB) multizone.hex $(GDB_LOAD_ARGS) $(GDB_LOAD_CMDS)
	
