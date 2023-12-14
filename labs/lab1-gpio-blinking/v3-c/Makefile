TOOLCHAIN = arm-none-eabi
CC = $(TOOLCHAIN)-gcc
LD  = $(TOOLCHAIN)-ld
AS  = $(TOOLCHAIN)-as
OD  = $(TOOLCHAIN)-objdump
OCP = $(TOOLCHAIN)-objcopy
AS  = $(TOOLCHAIN)-as

CC-FLAGS = -ffreestanding -O2 -nostdlib -lgcc

all: kernel7.img

%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

kernel.elf: start.o main.o
	$(CC) -T linker.ld -o $@ $^ $(CC-FLAGS)

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


default:
	arm-none-eabi-gcc -T linker.ld -o kernel7.elf start.o main.o -ffreestanding -O2 -nostdlib -lgcc
	arm-none-eabi-objcopy kernel7.elf -O binary kernel7.img