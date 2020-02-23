# Copyright(C) 2018 Hex Five Security, Inc. - All Rights Reserved

.PHONY: all
all: $(TARGET)

ASM_SRCS += $(NEWLIB_DIR)/crt0.S
C_SRCS += $(NEWLIB_DIR)/newlib.c

INCLUDES += -I$(PLATFORM_DIR)

MCUFLAGS += -march=$(ARM_ARCH)
MCUFLAGS += -mcpu=$(ARM_CPU)
MCUFLAGS += -mfloat-abi=$(ARM_FLOAT)
MCUFLAGS += -mfpu=$(ARM_FPU)

LDFLAGS	+= -T $(PLATFORM_DIR)/memory.lds
LDFLAGS	+= -T $(LINKER_SCRIPT)
LDFLAGS += -static $(MCUFLAGS)
LDFLAGS	+= -mthumb
LDFLAGS += --specs=nano.specs
LDFLAGS += -nostartfiles
LDFLAGS += -Xlinker --gc-sections

ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)

LINK_OBJS += $(ASM_OBJS) $(C_OBJS)
LINK_DEPS += $(LINKER_SCRIPT)

CLEAN_OBJS += $(TARGET) $(LINK_OBJS)

CFLAGS += -g -gdwarf-4
CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS += $(MCUFLAGS)
CFLAGS += -O0

HEX = $(subst .elf,.hex,$(TARGET))
LST = $(subst .elf,.lst,$(TARGET))
CLEAN_OBJS += $(HEX)
CLEAN_OBJS += $(LST) 

$(TARGET): $(LINK_OBJS) $(LINK_DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) $(LDFLAGS) -o $@ 
	$(OBJCOPY) -O ihex $(TARGET) $(HEX)
	$(OBJDUMP) --all-headers --demangle --disassemble --file-headers --wide -D $(TARGET) > $(LST)

$(ASM_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS) 

