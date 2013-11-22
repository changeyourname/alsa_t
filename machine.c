#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "deftype.h"
#include "machine.h"

xgd_machine_t machine;
int search_file(FILE *fp, const char *keyword)
{
	#define MAX_LINE	32 //256
	char line[2*MAX_LINE+2];
	int count = 0;
	int len;
	char *p;
	struct stat info;
	
	if((fp == NULL) || (keyword == NULL))
		return -1;
	
	//printf("search_file:%s\r\n", keyword);
	line[2*MAX_LINE] = 0;
	line[2*MAX_LINE+1] = 0;
	#if 0
	stat(fp, &info);
	while(info.st_size > count) {
	#else
	// 如果文件为空将产生问题
	if(fseek(fp, count, SEEK_SET) != 0) {
		return -1;
	}
	while(!feof(fp)) {
	#endif
		len = fread(line, sizeof(char), 2*MAX_LINE, fp);
		line[len] = 0;
		if(len > 0) {
			// printf("search_file:%s\r\n",line);
			if ((p = strstr(line, keyword )) != NULL ) {
				// printf("search_file:fgets %d\r\n",count+(p-line));
				return count+(p-line);
			}
		}
		count += MAX_LINE;
		if((len > MAX_LINE) && (fseek(fp, count, SEEK_SET) != 0)) {
			return -1;
		}
	}
	return -1;
}

s32 dev_misc_get_machineversion(void)
{
	#define BUF_SIZE	32 //256
	int ret;
	int i = 0;
	FILE *fp = NULL;
	char buf[BUF_SIZE+1];
	static u8 flag = 0;

	if(flag == 0) {
		flag = 1;
		buf[BUF_SIZE] = 0;
		fp = fopen("/proc/cmdline", "r");
		if (fp != NULL) {
			ret = search_file(fp, "xgd_machine_type=");
			if(ret >= 0) {
				machine.type = fasc2hex(fp, ret);
			} else {
				ret = -1;
			}
			ret = search_file(fp, "xgd_machine_version=");
			if(ret >= 0) {
				machine.version = fasc2hex(fp, ret);
			} else {
				ret = -1;
			}
			#if 0
			// 测试用
			ret = search_file(fp, "xgd_machine_vvvvvvv=");
			if(ret >= 0) {
				machine.version = fasc2hex(fp, ret);
			} else {
				ret = -1;
			}
			#endif
			ret = search_file(fp, "xgd_machine_ad1=");
			if(ret >= 0) {
				machine.machine_ad1 = fasc2hex(fp, ret);
			} else {
				ret = -1;
			}
			ret = search_file(fp, "xgd_machine_ad2=");
			if(ret >= 0) {
				machine.machine_ad2 = fasc2hex(fp, ret);
			} else {
				ret = -1;
			}
			ret = search_file(fp, "xgd_version_ad2=");
			if(ret >= 0) {
				machine.version_ad2 = fasc2hex(fp, ret);
			} else {
				ret = -1;
			}
			fclose(fp);
		} 
		
		if(ret < 0){
			machine.type = K301P;
			machine.version = 0;
			machine.machine_ad1 = 0;
			machine.machine_ad2 = 0;
			machine.version_ad2 = 0;
		}
	}

	return ret;
}

int fasc2hex(FILE *fp, int pos)
{
	#define BUF_SIZE	32 //256
	int ret = -1;
	int i;
	char buf[BUF_SIZE+1];
	
	if(fp == NULL) return -1;
	
	if(fseek(fp, pos, SEEK_SET) == 0) {
		if(fgets(buf, BUF_SIZE, fp) != NULL ){
			i = 0;
			while((buf[i] != '=') && (i < BUF_SIZE)) i++;
			i += 3;
			ret = 0;
			while((buf[i] != ' ') && (i < BUF_SIZE)) {
				ret <<= 4;
				if((buf[i] >= '0') && (buf[i] <= '9')) {
					ret += buf[i]&0x0f;
				} else if((buf[i] >= 'a') && (buf[i] <= 'f')) {
					ret += buf[i]-'a'+10;
				} else if((buf[i] >= 'A') && (buf[i] <= 'F')) {
					ret += buf[i]-'A'+10;
				} else {
					break;
				}
				i++;
			}
		}
	}
	return ret;
}
