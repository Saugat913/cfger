#ifndef _CFGER_UTILS_H_
#define _CFGER_UTILS_H_

#include <stdio.h>
#include <stdlib.h>

size_t get_file_size(FILE *fp);
char *read_config_file(char *file_name);

#endif
