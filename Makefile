CC=arm-none-linux-gnueabi-gcc

head_file=asound.h deftype.h soundcard.h wav_beep.h wav.h
c_obj=Talsa.o machine.o

beep: c_dep ${head_file} Makefile
	mv $< $@

c_dep: ${c_obj}
	${CC} -o $@ $^

Makefile:
	echo "rebuilding ..."

clean:
	-rm -rf beep *.o
