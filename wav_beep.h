#include "wav.h"

struct WAV_INFO
{
	struct RIFF_HEADER  riff_header;
	struct FMT_BLOCK    fmt_block;
	struct FACT_BLOCK   fact_block;
	struct DATA_BLOCK   data_block;
	char 				*pdata;
};

extern char wav_beepok[];
extern char wav_beeperr[];
extern char wav_slotcard[];

struct WAV_INFO beepok_info = {
	.riff_header = {
		.szRiffID 		= {'R','I','F','F'},
		.dwRiffSize 	= 0x2298,
		.szRiffFormat 	= {'W','A','V','E'}
	},

	.fmt_block = {
		.szFmtID 		= {'f','m','t',' '},
		.dwFmtSize 		= 0x10,
		.wavFormat 		= {
			.wFormatTag 		= 0x1,
			.wChannels 			= 0x2,
			.dwSamplesPerSec 	= 0xac44,
			.dwAvgBytesPerSec 	= 0x2b110,
			.wBlockAlign 		= 0x4,
			.wBitsPerSample 	= 0x10
		}
	},

	.data_block = {
		.szDataID 		= {'d','a','t','a'},
		.dwDataSize 	= 0x2274
	},

	.pdata 				= wav_beepok
};

struct WAV_INFO beeperr_info = {
	.riff_header = {
		.szRiffID 		= {'R','I','F','F'},
		.dwRiffSize 	= 0xf18e,
		.szRiffFormat 	= {'W','A','V','E'}
	},

	.fmt_block = {
		.szFmtID 		= {'f','m','t',' '},
		.dwFmtSize 		= 0x10,
		.wavFormat 		= {
			.wFormatTag 		= 0x1,
			.wChannels 			= 0x2,
			.dwSamplesPerSec 	= 0xac44,
			.dwAvgBytesPerSec 	= 0x2b110,
			.wBlockAlign 		= 0x4,
			.wBitsPerSample 	= 0x10
		}
	},

	.data_block = {
		.szDataID 		= {'d','a','t','a'},
		.dwDataSize 	= 0xf12c
	},

	.pdata 				= wav_beeperr
};

struct WAV_INFO slotcard_info = {
	.riff_header = {
		.szRiffID 		= {'R','I','F','F'},
		.dwRiffSize 	= 0x224a0,
		.szRiffFormat 	= {'W','A','V','E'}
	},

	.fmt_block = {
		.szFmtID 		= {'f','m','t',' '},
		.dwFmtSize 		= 0x10,
		.wavFormat 		= {
			.wFormatTag 		= 0x1,
			.wChannels 			= 0x2,
			.dwSamplesPerSec 	= 0xac44,
			.dwAvgBytesPerSec 	= 0x2b110,
			.wBlockAlign 		= 0x4,
			.wBitsPerSample 	= 0x10
		}
	},

	.data_block = {
		.szDataID 		= {'d','a','t','a'},
		.dwDataSize 	= 0x2247a,
	},

	.pdata 				= wav_slotcard
};
