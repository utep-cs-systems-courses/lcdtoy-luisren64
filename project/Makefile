#configuration
COMMON_OBJECTS	=	
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: install

install:
	(cd ../timerLib; make install)
	(cd ../lcdLib; make install)


toy.elf: ${COMMON_OBJECTS}  stateMachines.o led.o switches.o buzzer.o wdInterruptHandler.o p2_interrupt_handler.o toyMain.o ../lib/libTimer.a ../lib/libLcd.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

clean: 
	(cd ..; rm -rf lib h)
	(cd ../timerLib; make clean)
	(cd ..; rm -rf Doxygen_docs)
	rm -f *.o *.elf

led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

wdInterruptHandler.o: stateMachines.h

p2_interrupt_handler.o: switches.h

stateMachines.o: stateMachines.h stateMachines.c

switches.o: switches.h switches.c
