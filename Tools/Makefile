tools-m := built-in.a
tools-objs =

${tools-m}:${tools-objs}
	${COMPILES}ar crs ${tools-m} $^

${tools-objs}:%.o:%.c 
	${COMPILES}gcc -c ${CPPFLAGS} $<

clean:
	-rm ${tools-m} ${tools-objs}


