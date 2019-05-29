#include <stdio.h>

FILE *fp_console;
#define cprintf(msg, ...) \
do { \
    fp_console = fopen("/dev/console","w"); \
    if (fp_console) { \
        fprintf(fp_console, "[%s %d]:%c" msg "\n", __func__, __LINE__, !strchr(msg, '\n') ? ' ' : '\n', ##__VA_ARGS__); \
        fclose(fp_console); \
    }; \
} while(0)
