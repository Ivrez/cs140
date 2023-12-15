toolchain = arm-none-eabi
CC = $(toolchain)-gcc
LD  = $(toolchain)-ld
AS  = $(toolchain)-as
OD  = $(toolchain)-objdump
OCP = $(toolchain)-objcopy
AS  = $(toolchain)-as

CFLAGS = -O -Wall -Wno-unused-variable -Werror \
          -nostdlib -ffreestanding

LINKFILE = linker.ld

MAIN = main2.c
ASMS = start.s 
SRCS = $(MAIN) gpio.c
OBJS = $(ASMS:.s=.o) $(SRCS:.c=.o)

TARGET = kernel7

all: $(TARGET).img

%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(LD) -T $(LINKFILE) $^ -o $@

$(TARGET).img: $(TARGET).elf
	$(OCP) $< -O binary $@

show-dmp: $(TARGET).elf
	$(OD) -D $<

# Need env variable DRIVE 
copy-to-drive: $(TARGET).img
	@if [ -z "$(strip $(DRIVE))" ]; then \
		echo "Error: DRIVE is not set" ;\
	else \
		cp $< $(DRIVE); \
		echo "File copied to $(DRIVE)"; \
	fi

clean:
	rm -f *.o *.bin *.elf *.img