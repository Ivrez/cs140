toolchain = arm-none-eabi
CC = $(toolchain)-gcc
LD  = $(toolchain)-ld
AS  = $(toolchain)-as
OD  = $(toolchain)-objdump
OCP = $(toolchain)-objcopy
AS  = $(toolchain)-as

LINKFILE = linker.ld

ASMS = start.s 
SRCS = main.c gpio.c
OBJS = $(ASMS:.s=.o) $(SRCS:.c=.o)

TARGET = kernel

all: $(TARGET)7.img

%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(LD) -T $(LINKFILE) $^ -o $@

$(TARGET)7.img: $(TARGET).elf
	$(OCP) $< -O binary $@

show-dmp: $(TARGET).elf
	$(OD) -D $<

# Need env variable DRIVE 
copy-to-drive: kernel7.img
	@if [ -z "$(strip $(DRIVE))" ]; then \
		echo "Error: DRIVE is not set" ;\
	else \
		cp $< $(DRIVE); \
		echo "File copied to $(DRIVE)"; \
	fi

clean:
	rm -f *.o *.bin *.elf *.img