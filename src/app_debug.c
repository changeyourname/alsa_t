#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>

#include "app_debug.h"

/*******************************************************
Note: Please set -rdynamic option to gcc
*******************************************************/
#define MAX_DUMP	1024
void app_dump_strace(void)
{
	void			*array[MAX_DUMP] = {0};
	char 			**strframe = NULL;
	unsigned int	size = 0;
	unsigned int 	i = 0;
	unsigned int	j = 0;
  
	size = backtrace(array, MAX_DUMP);
	strframe = (char **)backtrace_symbols(array, size);
	
	printf("====dump_backtrace=====\r\n");
	printf("========Begin==========\r\n");
	printf("backtrace level = %d\r\n", size);
	for(i = 0; i < size; i++){
		printf("%d:\t%s\r\n", i, strframe[i]);
	}
	printf("=========End===========\r\n");
	
	if(strframe){
		free(strframe);
		strframe = NULL;
	}
}

void app_backtrace()
{
	int i;
	const int 	maxLevel = MAX_DUMP;
	void		*buffer[MAX_DUMP];
	int 		level = backtrace(buffer, maxLevel);
	const int	SIZE = MAX_DUMP;
	char		cmd[MAX_DUMP] = "addr2line -C -f -e";

	// let prog point to the end of "cmd"
	char* prog = cmd + strlen(cmd);
	int r = readlink("/proc/self/exe", prog, sizeof(cmd) - (prog-cmd)-1);

	FILE* fp = popen(cmd, "w");
	if (!fp){
		perror("popen");
		return;
	}
	printf("====dump_backtrace=====\r\n");
	for (i = 0; i < level; i++){
		fprintf(fp, "%d:\r%p\r\n", i, buffer[i]);
	}
	
	fclose(fp);
}
