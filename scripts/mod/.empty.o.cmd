cmd_scripts/mod/empty.o := /opt/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc -Wp,-MD,scripts/mod/.empty.o.d  -nostdinc -isystem /opt/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/lib/gcc/arm-none-linux-gnueabi/4.1.2/include -Iinclude  -I/home1/zhouyixing/Uniform/pkernel/arch/arm/include -include include/linux/autoconf.h -D__KERNEL__ -DXGD_COMPILE_DATE=\"131105\" -DXGD_KERNEL_SUB_VERSION=\"247\" -DCONFIG_IMX258_DEBUG=1 -DCONFIG_XGD_SYS_SECURE=1 -DXGD_PROGRAM_CC_FLAG=1 -DXGD_GIT_COMMIT_INFO=\"SHASUM:469408a2da0afa4581eefe1cd348a1b28d2883ce\\\r\\\nBRANCH:next\\\r\\\nDATE:2013115_09:33:51\\\r\\\nAUTHOR:zhouyixing\" -mlittle-endian -Iarch/arm/mach-mx25/include -Iarch/arm/plat-mxc/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -DXGD_COMPILE_DATE=\"131105\" -DXGD_KERNEL_SUB_VERSION=\"247\" -DCONFIG_IMX258_DEBUG=1 -DCONFIG_XGD_SYS_SECURE=1 -DXGD_PROGRAM_CC_FLAG=1 -DXGD_GIT_COMMIT_INFO=\"SHASUM:469408a2da0afa4581eefe1cd348a1b28d2883ce\\\r\\\nBRANCH:next\\\r\\\nDATE:2013115_09:33:51\\\r\\\nAUTHOR:zhouyixing\" -Os -marm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -msoft-float -Uarm -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign   -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(empty)"  -D"KBUILD_MODNAME=KBUILD_STR(empty)"  -c -o scripts/mod/.tmp_empty.o scripts/mod/empty.c

deps_scripts/mod/empty.o := \
  scripts/mod/empty.c \

scripts/mod/empty.o: $(deps_scripts/mod/empty.o)

$(deps_scripts/mod/empty.o):
