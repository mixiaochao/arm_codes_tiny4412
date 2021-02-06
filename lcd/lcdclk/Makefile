
TARGET			:= arm
BIN				:= $(TARGET).bin
OBJS			:= main.o
ST_OBJS			:= start.o

CROSS_COMPILE	:= arm-linux-
CC				:= $(CROSS_COMPILE)gcc
AS				:= $(CROSS_COMPILE)as
OBJCOPY			:= $(CROSS_COMPILE)objcopy
LD				:= $(CROSS_COMPILE)ld
NM				:= $(CROSS_COMPILE)nm
OBJDUMP			:= $(CROSS_COMPILE)objdump

CFLAGS			:= -Wall -fno-builtin -Iinclude

all:$(TARGET)
	@$(OBJCOPY) -O binary $< $(BIN)
	@$(NM) $(TARGET) > $(TARGET:=.map)
	@$(OBJDUMP) -d $(TARGET) > $(TARGET:=.s)
	
$(TARGET): $(ST_OBJS) $(OBJS)
	@$(LD) $(ST_OBJS) $(OBJS) -T ld.lds -o $@
	
%.o:%.c
	@$(CC) -c $< -o $@ $(CFLAGS) 
%.o:%.s
	@$(AS) $< -o $@
%.o:%.S
	@$(CC) -c $< -o $@

.PHONY:clean

clean:
	rm -f $(BIN) $(TARGET) $(TARGET:=.s) $(TARGET:=.map) $(OBJS) $(ST_OBJS)

new:
	make clean;
	make
