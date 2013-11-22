#ifndef __MACHINE__
#define __MACHINE__

#include "deftype.h"

#define K301          0x04
#define K350          0x05
#define K360          0x06
#define K360_IMX258   0x16
#define K370          0x07
#define K370_IMX258   0x17
#define K380          0x08
#define K390          0x09
#define K390_WINCE    0x0A
#define K320A         0x11
#define K320_IMX258   0x1A
#define K320          0x20
#define K501          0x21
#define K501A         0x21
#define K3306R        0x22
#define K501AD        0x23
#define K301P         0x24
#define K320P         0x1A
#define K350P         0x15
#define K360P         0x16
#define K370P         0x17
#define K3306P        0x3A
#define G891		  0x49
#define G810          0x42
#define G850          0x45
#define G860          0x46
#define G870          0x47
#define G360M         0x4A
#define G870D         0x4B
#define G8601D        0x4C
#define K3305         0x80
#define K3306         0x81
#define G101          0x85
#define K3306H        0x88
#define V30PINPAD_MAXQ 0x87
#define V30PINPAD_STC  0x3B
#define V30PINPAD_STM  0x89
#define K3601D        0x93
#define K3102          0x90
#define K3108          0x91
#define K502           0x92 
#define K820P		   0x1C

typedef struct _XGD_MACHINE_ {
	unsigned int type;
	unsigned int version;
	unsigned int machine_ad1;
	unsigned int machine_ad2;
	unsigned int version_ad2;
} xgd_machine_t;

extern xgd_machine_t machine;
extern s32 dev_misc_get_machineversion(void);
#endif
