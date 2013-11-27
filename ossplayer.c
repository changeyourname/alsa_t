#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/mman.h>

#include "wav.h"
#include "wav_beep.h"
#include "soundcard.h"
#include "machine.h"
#include "app_debug.h"

static char *command;

inline int volum_to_freq(char volum);
static void usage(char *command);
int main(char argc, char **argv)
{
	int 			dev_dsp;
	int 			src_wav;
	
	unsigned int 	count;
	long 			remain;
	int 			tmp_cul;
	char 			volum = 4;
	int				status;
	int 			arg;
	unsigned char 	*pdata;
	unsigned char 	*f_wav = NULL;

	struct WAV_INFO *info;
	
	static struct option long_options[] = {
		{"help", 0, 0, 'h'},
		{"volume", 1, 0, 'v'},
		{0, 0, 0, 0}
	};
	char *short_options = "hv:";

	int option_index;
	command = argv[0];
	while ((arg = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (arg) {
		case 'h':
			usage(command);
			return 0;
		case 'v':
			volum = atoi(optarg);
			app_debug("volume = %d", volum);
			break;
		}
	}
	status = dev_misc_get_machineversion();
	if(status < 0){
		app_warn("machine would be set to K301P");
	}else{
		app_debug("machine = %d", machine.type);
	}
	
	f_wav = argv[optind];
	app_debug("wav is %s", f_wav);
	src_wav = open (f_wav, O_RDWR);
	if (src_wav < 0){
		app_err("open %s failed!", f_wav);
		usage(command);
		exit(-1);
	}

	info = (struct WAV_INFO *)malloc(sizeof(struct WAV_INFO));
	if(info == 0){
		app_debug("malloc info failed!\r\n");
		exit -1;
	}

	pdata = (char *)malloc(16384);
	if(pdata == 0){
		app_debug("malloc pdata failed!\r\n");
		exit -1;
	}
	
	status = read(src_wav, pdata, 128);
	if(status != 128){
		info->riff_header.dwRiffSize 	= *(u32 *)&pdata[4];
		app_debug("dwRiffSize = %x", info->riff_header.dwRiffSize);
	}

	info->fmt_block.dwFmtSize 	= *(u32 *)&pdata[16];
	app_debug("dwFmtSize = %d", info->fmt_block.dwFmtSize);
	info->fmt_block.wavFormat.wChannels 		= *(u16 *)&pdata[22]; 
	app_debug("wChannels = %d", info->fmt_block.wavFormat.wChannels);
	info->fmt_block.wavFormat.dwSamplesPerSec 	= *(u32 *)&pdata[24];
	app_debug("dwSamplesPerSec = %d", info->fmt_block.wavFormat.dwSamplesPerSec);
	info->fmt_block.wavFormat.wBitsPerSample 	= *(u16 *)&pdata[34];
	app_debug("wBitsPerSample = %d", info->fmt_block.wavFormat.wBitsPerSample);

	int fact_offset;
	int data_offset;
	fact_offset = 20 + info->fmt_block.dwFmtSize;
	if (memcmp((char *)(&pdata[fact_offset]), "fact", 4) == 0){
		info->fact_block.dwFactSize = *(u32 *)&pdata[fact_offset + 4];
		data_offset = fact_offset + 8 + info->fact_block.dwFactSize;
	}else{
		info->fact_block.dwFactSize = 0;
		data_offset = fact_offset;
	}
	app_debug("data_offset = %d", data_offset);
	app_debug("fact_offset = %d", fact_offset);

	info->data_block.dwDataSize = 
	(pdata[data_offset + 4] & 0xff) 		|
	(pdata[data_offset + 5] & 0xff) << 8 	|
	(pdata[data_offset + 6] & 0xff) << 16 	|
	(pdata[data_offset + 7] & 0xff)	<< 24;

	app_debug("dwDataSize = %x", info->data_block.dwDataSize);

	dev_dsp = open("/dev/dsp", O_WRONLY);
	if(dev_dsp < 0){
		printf("Open /dev/dsp failed!\r\n");
		exit(-1);
	}

#define SNDCTL_DSP_LIBDEV_VERSION   _SIOR ('P', 25, int)
#define SOUND_PCM_LIBDEV_VERSION    SNDCTL_DSP_LIBDEV_VERSION
	arg = 179;
	status = ioctl(dev_dsp, SOUND_PCM_LIBDEV_VERSION, &arg);

	if(machine.type == G810){
		arg = volum_to_freq(volum);
		volum = 7;
	}else{
		arg = info->fmt_block.wavFormat.dwSamplesPerSec;
	}

	status = ioctl(dev_dsp,SOUND_PCM_WRITE_RATE,&arg);
	
	arg = info->fmt_block.wavFormat.wChannels;
	status = ioctl(dev_dsp, SOUND_PCM_WRITE_CHANNELS, &arg);
	
	arg = info->fmt_block.wavFormat.wBitsPerSample;
	status = ioctl(dev_dsp, SOUND_PCM_WRITE_BITS, &arg);
	
#define FRAME_LEN 	1024
#define likely(x) 	__builtin_expect((x),1)
#define unlikely(x) __builtin_expect((x),0)
#define MIN(a,b) 	(likely(a < b) ? a : b)
	if(lseek(src_wav, data_offset + 8, SEEK_SET) != data_offset + 8){
		app_debug("Error!\r\n");
		exit(-1);
	}

	info->pdata = pdata;
	remain = info->data_block.dwDataSize & (~(1UL));
	while(remain){
		status = read(src_wav, pdata, MIN(FRAME_LEN, remain));
		if(unlikely(status != MIN(FRAME_LEN, remain))){
			app_debug("Error!\r\n");
			exit(-1);
		}
	
		char tmp_vol;
		switch(volum){
		case 0:
			memset(pdata, 0, MIN(FRAME_LEN, remain));
			break;
		case 1:
		case 2:
		case 3:
			tmp_vol = 4 - volum;
			for(count = 0; count < MIN(FRAME_LEN, remain); count += 2){
				tmp_cul = (pdata[count + 1] << 8) | pdata[count];
				if(tmp_cul & 0x8000){
					tmp_cul |= 0xffff0000;
					tmp_cul = ~((~tmp_cul + 1) >> tmp_vol) + 1;
					if(unlikely(tmp_cul < -32767)){
						tmp_cul = -32767;
					}
				}else{
					tmp_cul = tmp_cul >> tmp_vol;
					if(unlikely(tmp_cul > 0x7fff)){
						tmp_cul = 0x7fff;
					}
				}

				pdata[count + 1] = (tmp_cul >> 8) & 0xff;
				pdata[count] = tmp_cul & 0xff;
			}
			break;
		case 4:
			break;
		case 5:
			tmp_vol = 1;
			for(count = 0; count < MIN(FRAME_LEN, remain); count += 2){
				tmp_cul = (pdata[count + 1] << 8) | pdata[count];
				if(tmp_cul & 0x8000){
					tmp_cul |= 0xffff0000;
					tmp_cul = ~((~tmp_cul + 1) + (~tmp_cul + 1) >> 1) + 1;
					if(unlikely(tmp_cul < -32767)){
						tmp_cul = -32767;
					}
				}else{
					tmp_cul = tmp_cul + (tmp_cul >> 3);
					if(unlikely(tmp_cul > 0x7fff)){
						tmp_cul = 0x7fff;
					}
				}

				pdata[count + 1] = (tmp_cul >> 8) & 0xff;
				pdata[count] = tmp_cul & 0xff;
			}
			break;
		case 6:
			tmp_vol = 1;
			for(count = 0; count < MIN(FRAME_LEN, remain); count += 2){
				tmp_cul = (pdata[count + 1] << 8) | pdata[count];
				if(tmp_cul & 0x8000){
					tmp_cul |= 0xffff0000;
					tmp_cul = ~((~tmp_cul + 1) + (~tmp_cul + 1) >> 0) + 1;
					if(unlikely(tmp_cul < -32767)){
						tmp_cul = -32767;
					}
				}else{
					tmp_cul = tmp_cul + (tmp_cul >> 2);
					if(unlikely(tmp_cul > 0x7fff)){
						tmp_cul = 0x7fff;
					}
				}

				pdata[count + 1] = (tmp_cul >> 8) & 0xff;
				pdata[count] = tmp_cul & 0xff;
			}
			break;
		case 7:
			for(count = 0; count < MIN(FRAME_LEN, remain); count += 2){
				tmp_cul = (pdata[count + 1] << 8) | pdata[count];
				if(tmp_cul & 0x8000){
					tmp_cul |= 0xffff0000;
					tmp_cul = ~((~tmp_cul + 1) << 1) + 1;
					if(unlikely(tmp_cul < -32767)){
						tmp_cul = -32767;
					}
				}else{
					tmp_cul = (tmp_cul << tmp_vol) + (tmp_cul >> 1);
					if(unlikely(tmp_cul > 0x7fff)){
						tmp_cul = 0x7fff;
					}
				}

				pdata[count + 1] = (tmp_cul >> 8) & 0xff;
				pdata[count] = tmp_cul & 0xff;
			}
			break;
		default:
			break;
		}


		status = write(dev_dsp, pdata, MIN(FRAME_LEN, remain));
		if(unlikely(status != MIN(FRAME_LEN, remain))){
			app_debug("write pdata failed! status = %d", status);
			exit -1;
		}else{
			remain -= MIN(FRAME_LEN, remain);
		}
	}
	
	free(pdata);
	free(info);
	close(dev_dsp);

	return 0;
}

inline int volum_to_freq(char volum)                                                                               
{                                                                                                                  
    int freq;                                                                                                      
                                                                                                                                             
    switch(volum){                                                                                                 
    case 0:                                                                                                        
        freq = 32000;                                                                                              
        break;                                                                                                     
    case 1:                                                                                                        
    case 2:                                                                                                        
    case 3:                                                                                                        
    case 4:                                                                                                        
    case 5:                                                                                                        
    case 6:                                                                                                        
    case 7:                                                                                                        
        freq = volum * 2000 + 32000;                                                                               
        break;                                                                                                     
    default:                                                                                                       
        freq = 44100;                                                                                              
    }                                                                                                              
                                                                                                                   
    return freq;                                                                                                   
}

static void usage(char *command)
{
	fprintf(stderr,
"\n"
"Usage: %s [OPTION]... [FILE]...\n"
"-h, --help              help\n"
"\n"
		, command);
}
