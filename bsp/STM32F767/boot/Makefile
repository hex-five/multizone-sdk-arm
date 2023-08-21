# Copyright(C) 2023 Hex Five Security, Inc. - All Rights Reserved

TARGET		:= boot

MCUFLAGS 	+= -march=$(ARM_ARCH)
MCUFLAGS 	+= -mcpu=$(ARM_CPU)
MCUFLAGS 	+= -mfloat-abi=$(ARM_FLOAT)
MCUFLAGS 	+= -mfpu=$(ARM_FPU)

CFLAGS += $(MCUFLAGS)
CFLAGS += -g -gdwarf-4
CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS += -O0
CFLAGS += -Wall

LDFLAGS	+= -T ../../$(BOARD)/memory.lds -T linker.ld
LDFLAGS	+= -nostartfiles -nodefaultlibs -nostdlib
LDFLAGS += -Xlinker --gc-sections
LDFLAGS += -Wl,-Map,$(TARGET).map


.PHONY: all
all:

	$(CC) $(CFLAGS) -x assembler-with-cpp -c -o $(TARGET).o $(TARGET).S
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).elf ./$(TARGET).o 
	$(OBJCOPY) -O ihex -j.boot $(TARGET).elf $(TARGET).hex
	$(OBJDUMP) --source --all-headers --demangle --disassemble --line-numbers --reloc --wide $(TARGET).elf > $(TARGET).lst

.PHONY: clean
clean:
	rm -f $(TARGET).o $(TARGET).hex $(TARGET).elf $(TARGET).lst $(TARGET).map






