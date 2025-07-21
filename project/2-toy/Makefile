COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: test.elf

test.elf: main.c led.c switch.c buzzer.c assembly.s statemachines.c p2_interrupt_handler.c ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: test.elf
	msp430loader.sh $^
clean:
	rm -f *.o *.elf 

main.c: switch.h statemachines.h led.h buzzer.h
switch.c: switch.h
p2_interrupt_handler.c: switch.h
led.c: led.h
statemachines.c: statemachines.h led.h buzzer.h
buzzer.c: buzzer.h
