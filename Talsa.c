#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "wav.h"
#include "wav_beep.h"
#include "soundcard.h"

#define snd_info(fmt, args...)											\
	printf(fmt"@%s--%d\r\n",##args, __FILE__,__LINE__)
#define snd_err(fmt, args...) snd_info(fmt, ##args)

#define SND_DEBUG		1
#ifdef SND_DEBUG 
	#define snd_debug(fmt, args...) snd_info(fmt,##args)
#else
	#define snd_debug(fmt, args...)
#endif

typedef struct
{
	unsigned int 	pin;
	unsigned int 	value;
}HC595Arg;

static unsigned char request_instruction(void){
	int tmp = 0;
	
	printf("Again 1;Quit 0\r\n");
	printf("Please input your command:");
	scanf("%d", &tmp);
	printf("\r\n");
	
	snd_debug("tmp = %d",tmp);
	return tmp;
}

int main(char argc, char **argv)
{
	int 	dev_dsp;
	
	unsigned int 	count;
	char 			*pdata;
	char 			*psrc;
	long 			remain;
	int 			tmp_cul;
	char 			volum;
	int				status;
	int 			arg;

	struct WAV_INFO *info;
	info = &slotcard_info;
	
	HC595Arg 		hc595_arg;
	snd_debug("dwDataSize = 0x%x", info->data_block.dwDataSize);
	pdata = (char *)malloc(info->data_block.dwDataSize);
	snd_debug("pdata = %p", pdata);

	dev_dsp = open("/dev/dsp", O_WRONLY);
	if(dev_dsp < 0){
		printf("Open /dev/dsp failed!\r\n");
		exit(-1);
	}

	arg = info->fmt_block.wavFormat.dwSamplesPerSec;
	status = ioctl(dev_dsp,SOUND_PCM_WRITE_RATE,&arg);
	
	arg = info->fmt_block.wavFormat.wChannels;
	status = ioctl(dev_dsp, SOUND_PCM_WRITE_CHANNELS, &arg);
	
	arg = info->fmt_block.wavFormat.wBitsPerSample;
	status = ioctl(dev_dsp, SOUND_PCM_WRITE_BITS, &arg);
	
	if(argc == 1){
		arg = 7;
		volum = arg;
		ioctl(dev_dsp,SOUND_PCM_WRITE_VOLUME,&arg);
	}else if(argc == 2){
		arg = *argv[1] - '0';
		volum = arg;
		ioctl(dev_dsp,SOUND_PCM_WRITE_VOLUME,&arg);
	}else{
		snd_debug("Error!\r\n");
		exit(-1);
	}

#define MIN(a,b) (a < b ? a : b)
	count = 0;
	// volum = 0;
	psrc = info->pdata;
	for(; count < info->data_block.dwDataSize; count += 2){
		tmp_cul = (psrc[count + 1] << 8) | psrc[count];
		if(tmp_cul & 0x8000){
			tmp_cul |= 0xffff0000;
			/*
			tmp_cul = ~((~tmp_cul + 1) / (volum * 15)) + 1;
			*/
			tmp_cul = ~((~tmp_cul + 1) * volum ) + 1;
			if(tmp_cul < -32767){
				tmp_cul = -32767;
			}
		}else{
			/*
			tmp_cul = tmp_cul / (volum * 15);
			*/
			tmp_cul = tmp_cul * volum;
			if(tmp_cul > 0x7fff){
				tmp_cul = 0x7fff;
			}
		}

		pdata[count + 1] = (tmp_cul >> 8) & 0xff;
		pdata[count] = tmp_cul & 0xff;
	}
		
	snd_debug();
__Again:
	remain = info->data_block.dwDataSize;
	while(remain > 0){
		status = write(dev_dsp, &pdata[info->data_block.dwDataSize - remain], MIN(1024,remain));
		if (status != MIN(1024,remain)){
			snd_err("status = %x",status);
			exit -1;
		}

		remain -= status;
	}

	if(request_instruction() == 1){
		goto __Again;
	}
	
	close(dev_dsp);
	return 0;
}
