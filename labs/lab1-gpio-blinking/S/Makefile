TOOLCHAIN = arm-none-eabi
CC = $(TOOLCHAIN)-gcc
LD  = $(TOOLCHAIN)-ld
AS  = $(TOOLCHAIN)-as
OD  = $(TOOLCHAIN)-objdump
OCP = $(TOOLCHAIN)-objcopy
AS  = $(TOOLCHAIN)-as

all: kernel7.img

%.o: %.S
	$(AS) $< -o $@

kernel.elf: start.o
	$(LD) $< -o $@

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