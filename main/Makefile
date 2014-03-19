main-m := built-in.a
main-objs =

${main-m}:${main-objs}
	${COMPILES}ar crs ${main-m} $^

${main-objs}:%.o:%.c 
	${COMPILES}gcc -c ${CPPFLAGS} $<

clean:
	-rm ${main-m} ${main-objs}

