#include <stdio.h>

FILE *fp_console;
#define cprintf(msg, ...) \
do { \
    fp_console = fopen("/dev/console","w"); \
    if (fp_console) { \
        fprintf(fp_console, "[%s %d]: " msg "\n", __func__, __LINE__, ##__VA_ARGS__); \
        fclose(fp_console); \
    }; \
} while(0)
