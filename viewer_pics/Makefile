
TARGET		:= arm
BIN		:= $(TARGET).bin
OBJS		:= lib.o main.o pwm.o lcd.o backlight.o
ASMOBJS		:= head.o
CFLAGS		:= -Wall -fno-builtin -Iinclude -c
CROSS_COMPILE	:= arm-linux-

CC		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
OBJCOPY		:= $(CROSS_COMPILE)objcopy
NM		:= $(CROSS_COMPILE)nm
objdump		:= $(CROSS_COMPILE)objdump

LDADD		:= 0x50000000

#############################################

$(BIN):$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf:$(ASMOBJS) $(OBJS)
	$(LD) $(ASMOBJS) $(OBJS) -Tld.lds -o $@	
	$(NM) $@ > $(TARGET).map 
	

%.o:%.S
	$(CC) $(CFLAGS) $< -o $@
%.o:%.c
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f $(BIN) $(TARGET).elf $(OBJS) $(ASMOBJS)

