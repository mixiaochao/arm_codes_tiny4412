
.PHONY:clean

TARGET				:= stage2
BIN				:= $(TARGET).bin
OBJS				:= app.o
ASM_OBJ				:= start.o mem_init_r1.o clock_init.o
CFLAGS				:= -Wall -fno-builtin -Iinclude

CROSS_COMPILER		:= arm-linux-

CC					:= $(CROSS_COMPILER)gcc
LD					:= $(CROSS_COMPILER)ld
OBJDUMP				:= $(CROSS_COMPILER)objdump
OBJCOPY				:= $(CROSS_COMPILER)objcopy

##############################

$(BIN):$(TARGET)
	$(OBJCOPY) -O binary $< $@

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
