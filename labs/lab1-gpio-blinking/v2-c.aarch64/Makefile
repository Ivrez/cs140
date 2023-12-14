CROSS = aarch64-linux-gnu
CC = $(CROSS)-gcc
LINKER = $(CROSS)-ld
OBJCOPY = $(CROSS)-objcopy

PROJECT_OBJS = crt0.o blinky.o

all: kernel8.img

%.o: %.S
	$(CC) -c $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

blinky.bin: blinky.elf
	$(OBJCOPY) -O binary $< $@

blinky.elf: $(PROJECT_OBJS) layout.ld
	$(LINKER) -T layout.ld $(PROJECT_OBJS) -o $@

kernel8.img: blinky.bin
	cp blinky.bin kernel8.img

clean:
	rm -f $(PROJECT_OBJS) *.bin *.elf *.img