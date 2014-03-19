ifeq ("PC", "${ARCH}")
COMPILES ?=
else
COMPILES ?= arm-none-linux-gnueabi-
endif

CC :=gcc
LD :=ld
MAKE ?= /usr/bin/make

BUILD_PWD := $(shell /bin/pwd)
include ${BUILD_PWD}/scripts/Kbuild.include

CPPFLAGS +=-I${BUILD_PWD}/include
ifneq ("RELEASE", "${MODE}")
CPPFLAGS +=-DAPP_DEBUG
CPPFLAGS +=-rdynamic
CPPFLAGS +=-g
else
CPPFLAGS +=-O2
endif

tools-path := ${BUILD_PWD}/Tools/
src-path 	:= ${BUILD_PWD}/src/
main-path 	:= ${BUILD_PWD}/main/

ossplayer-dirs := $(patsubst %/,%,$(filter %/, $(tools-y) $(src-y) $(main-y)))

tools-y	:= $(patsubst %/, %/built-in.a, ${tools-path})
src-y	:= $(patsubst %/, %/built-in.a, ${src-path})
main-y	:= $(patsubst %/, %/built-in.a, ${main-path})

## ossplayer : ${tools-y} ${src-y} ${src-y}
ossplayer : ${tools-y} ${src-y} ${main-y} ${ossplayer-dirs} 
	@${COMPILES}${CC} ${tools-y} ${src-y} ${main-y} -o $@

${main-y} : $(patsubst %/built-in.a, %/Makefile, $(main-y))
	@make -C ${main-path} COMPILES=${COMPILES} CPPFLAGS="${CPPFLAGS}" -f $<

${tools-y} : $(patsubst %/built-in.a, %/Makefile, $(tools-y))
	@make -C ${tools-path} COMPILES=${COMPILES} CPPFLAGS="${CPPFLAGS}" -f $<

${src-y} : $(patsubst %/built-in.a, %/Makefile, $(src-y))
	@make -C ${src-path} COMPILES=${COMPILES} CPPFLAGS="${CPPFLAGS}" -f $<


clean:
	@make -C ${tools-path} clean
	@make -C ${src-path} clean
	@make -C ${main-path} clean
	@-rm ossplayer

$(ossplayer-dirs): scripts FORCE
	$(MAKE) $(build)=$@

FORCE:
