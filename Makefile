BUILD_PWD := $(shell /bin/pwd)

ifeq ("PC", "${ARCH}")
CC=gcc
else
CC=arm-none-linux-gnueabi-gcc
endif

CPPFLAGS +=-I${BUILD_PWD}/include/
ifneq ("RELEASE", "${MODE}")
CPPFLAGS +=-DAPP_DEBUG
CPPFLAGS +=-rdynamic
CPPFLAGS +=-g
else
CPPFLAGS +=-O2
endif

head_file =asound.h
head_file +=deftype.h
head_file +=soundcard.h
head_file +=wav_beep.h
head_file +=wav.h
head_file +=app_debug.h
head_file +=machine.h
make_file =Makefile
c_obj =ossplayer.o 
c_obj +=machine.o 
c_obj +=app_debug.o

ossplayer: ${c_obj} 
	${CC} -Wl,-Map=ossplayer.map ${CPPFLAGS} ${LDFLAGS} -o $@ ${c_obj}

${c_obj}: %.o:%.c h.obj m.obj
	${CC} -c ${CPPFLAGS} ${LDFLAGS} $< -o $@

h.obj: ${head_file}
	touch h.obj

m.obj: ${make_file}
	touch m.obj

clean:
	-rm -rf ossplayer *.o *_obj *.obj *.map

