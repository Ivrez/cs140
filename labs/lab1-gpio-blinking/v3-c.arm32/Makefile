toolchain = arm-none-eabi
CC = $(toolchain)-gcc
LD  = $(toolchain)-ld
AS  = $(toolchain)-as
OD  = $(toolchain)-objdump
OCP = $(toolchain)-objcopy
AS  = $(toolchain)-as

LINKFILE = linker.ld

all: kernel7.img

%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

kernel.elf: start.o main.o
	$(LD) -T $(LINKFILE) $^ -o $@

kernel7.img: kernel.elf
	$(OCP) $< -O binary $@

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