
.PHONY:clean

TARGET		:= arm
BIN		:= $(TARGET).bin
OBJS		:= mmu.o app.o 
OBJS		+= irq.o isr.o i2c.o tp.o rtc.o 
OBJS		+= vector.o display.o uart.o timer.o gobang.o string.o 
OBJS		+= lib.o lcd.o pwm.o backlight.o boot.o menu.o key.o
OBJS		+= led.o calendar.o time.o adc.o buzzer.o shell.o
OBJS		+= gallery.o wdt.o
ASM_OBJ		:= start.o

CFLAGS		:= -Wall -fno-builtin -Iinclude

CROSS_COMPILER	:= arm-linux-

CC		:= $(CROSS_COMPILER)gcc
LD		:= $(CROSS_COMPILER)ld
OBJDUMP		:= $(CROSS_COMPILER)objdump
OBJCOPY		:= $(CROSS_COMPILER)objcopy

##############################

$(BIN):$(TARGET)
	$(OBJCOPY) -O binary $< $@;mv $(BIN) ../

$(TARGET):$(ASM_OBJ) $(OBJS)
	$(LD) $(ASM_OBJ) $(OBJS) -o $@ -Tld.lds

%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f *.o $(TARGET) $(BIN)
new:
	make clean;make
