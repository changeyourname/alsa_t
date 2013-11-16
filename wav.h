#ifndef __DEV_WAV_H
#define __DEV_WAV_H

#include "deftype.h"

struct RIFF_HEADER
{
	S8 szRiffID[4];  // 'R','I','F','F'
	U32 dwRiffSize;
	S8 szRiffFormat[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT
{
	U16 wFormatTag;
	U16 wChannels;
	U32 dwSamplesPerSec;
	U32 dwAvgBytesPerSec;
	U16 wBlockAlign;
	U16 wBitsPerSample;
	//U16 additional;//两字节附加信息
};
struct FMT_BLOCK
{
	S8  szFmtID[4]; // 'f','m','t',' '
	U32  dwFmtSize;
	struct WAVE_FORMAT wavFormat;
};

struct FACT_BLOCK
{
	S8  szFactID[4]; // 'f','a','c','t'
	U32  dwFactSize;
};

struct DATA_BLOCK
{
	S8 szDataID[4]; // 'd','a','t','a'
	U32 dwDataSize;
};
#endif
