COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: siren.elf

siren.elf: ${COMMON_OBJECTS} buzzer.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: siren.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

buzzer.c: buzzer.h
main.c: buzzer.h

