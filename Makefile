CC=arm-none-linux-gnueabi-gcc

all:Makefile beep

beep: Talsa.o wav_beep.o
	${CC} -o $@ $^

Makefile:
	echo Makefile

clean:
	-rm -rf beep *.o
