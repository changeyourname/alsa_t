/******************************************************************
** Copyright (c) 2004- 深圳奥格立电子科技有限公司
** 文件名: deftype.h      CPU Type: S3C44B0   Compiler: arm-elf-tools-20040427
** 创建人: 杨星           版    本: V0.01    日    期: 2005-01-26
** 描  述: 数据类型定义
** 修改人: 
** 描  述: 
*******************************************************************/
#ifndef __DEV_DEFTYPE_H
#define __DEV_DEFTYPE_H

#define _NET_POS

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef WORD
#define WORD unsigned short
#endif

typedef char INT8;

typedef short INT16;
typedef int INT32;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

typedef unsigned char UBOOL;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned char ubool;

typedef int STATUS;
typedef int ARGINT;

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef S8
#define S8 char
#endif

#ifndef S16
#define S16 short
#endif

#ifndef S32
#define S32 int
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef s8
#define s8 char
#endif

#ifndef s16
#define s16 short
#endif

#ifndef s32
#define s32 int
#endif

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef u32
#define u32 unsigned int
#endif

#ifndef bit
#define bit unsigned char
#endif

#ifndef bdata
#define bdata
#endif

#ifndef xdata
#define xdata
#endif


#ifndef idata
#define idata
#endif

#ifndef code
#define code const
#endif

#ifndef SELHIGHRAM6
#define SELHIGHRAM6
#endif

#ifndef SELHIGHRAM
#define SELHIGHRAM
#endif

#ifndef EXTERN
#define EXTERN
#endif

typedef struct tagBITMAPFILEHEADER  //文件头  14B  
{ 
unsigned short int  bfType;   
unsigned long     bfSize;   
unsigned short int  bfReserved1;   
unsigned short int  bfReserved2;   
unsigned long     bfOffBits;   
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER  //头文件信息
{ 
unsigned long    biSize;   
long      biWidth;     
long      biHeight;     
unsigned short int   biPlanes;   
unsigned short int   biBitCount;  
unsigned long     biCompression;   
unsigned long     biSizeImage;   
long      biXPelsPerMeter;   
long      biYPelsPerMeter;   
unsigned long     biClrUsed;  
unsigned long     biClrImportant;  
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{ 
unsigned char    rgbBlue;    
unsigned char    rgbGreen;     
unsigned char    rgbRed;     
unsigned char    rgbReserved;    
} RGBQUAD; 



//Hardware version
#define K370_STARTVER 0x10
#define K370_V11 0x11
#define K370_V12 0x12
#define K370_V13 0x13
#define K370_V14 0x14
#define K370_V15 0x15
#define K370_ENDVER 0x1F

#define K360_STARTVER 0x50
#define K360_V51 0x51
#define K360_V52 0x52
#define K360_V53 0x53
#define K360_V54 0x54
#define K360_V55 0x55
#define K360_ENDVER 0x5F


//yuyt 2008.10.13
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#define NDEBUG
#include <assert.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>

//	#define dprintf printf
#define dprintf(fmt...) 
#endif
