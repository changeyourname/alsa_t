src-m := built-in.a
src-objs =

src-objs += app_debug.o
src-objs += machine.o
src-objs += wav_beep.o
src-objs += ossplayer.o

${src-m}:${src-objs}
	${COMPILES}ar crs ${src-m} $^

${src-objs}:%.o:%.c 
	${COMPILES}gcc -c ${CPPFLAGS} $<

clean:
	-rm ${src-m} ${src-objs}
