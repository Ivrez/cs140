ARM = arm-none-eabi
CC = $(ARM)-gcc
LD  = $(ARM)-ld
AS  = $(ARM)-as
OD  = $(ARM)-objdump
OCP = $(ARM)-objcopy
AS  = $(ARM)-as

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