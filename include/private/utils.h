#ifndef _CFGER_UTILS_H_
#define _CFGER_UTILS_H_

#include <stdio.h>
#include <stdlib.h>

size_t cfger_get_file_size(FILE *fp);
char *cfger_read_config_file(char *file_name);

#endif
