PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

INCLUDEDIR 	:= $(shell pwd)/include  $(shell pwd) irda
CFLAGS 		:= -Wall
CPPFLAGS   	:= -nostdinc -fno-builtin -I$(INCLUDEDIR)

GCCDIR=$(shell which arm-linux-gnueabihf-gcc)
LIBDIR=$(subst arm-linux-gnueabihf-gcc,../,$(GCCDIR))

LDFLAGS         :=-lgcc -L$(LIBDIR)lib/gcc/arm-linux-gnueabihf/6.2.1
objs :=  start.o main.o uart.o eabi_compat.o my_printf.o gic.o gpio.o timer.o irda/circle_buffer.o irda/irda_raw.o  irda/irda_nec.o

TARGET := irda

$(TARGET).img : $(objs)
	$(LD) -T imx6ull.lds -o $(TARGET).elf $^ $(LDFLAGS)
	$(OBJCOPY) -O binary -S $(TARGET).elf  $(TARGET).bin
	$(OBJDUMP) -D -m arm  $(TARGET).elf  > $(TARGET).dis	
	./tools/mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d $(TARGET).bin $(TARGET).imx
	dd if=/dev/zero of=1k.bin bs=1024 count=1
	cat 1k.bin $(TARGET).imx > $(TARGET).img

%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET).dis  $(TARGET).bin $(TARGET).elf $(TARGET).imx $(TARGET).img *.o


	
