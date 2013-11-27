#include <stdio.h>

#define app_info(fmt, args...)  										\
	printf("INFO: "fmt"@%s--%d\r\n", ##args, __FILE__,__LINE__)

#define app_warn(fmt, args...)  										\
	printf("WARN: "fmt"@%s--%d\r\n", ##args, __FILE__,__LINE__)
#define app_err(fmt, args...) 											\
	fprintf(stderr, "ERROR: "fmt"@%s--%d\r\n", ##args, __FILE__, __LINE__)

#ifdef APP_DEBUG
#define app_debug(fmt, args...) 										\
	printf("DEBUG: "fmt"@%s--%d\r\n", ##args, __FILE__,__LINE__)
#else
#define app_debug(fmt, args...)
#endif
	
extern void app_dump_strace(void);
extern void app_backtrace(void);








