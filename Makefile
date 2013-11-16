CC=arm-none-linux-gnueabi-gcc

beep: wav_beep.c Talsa.c
	${CC} -o $@ $^

clean:
	-rm -rf beep *.o
