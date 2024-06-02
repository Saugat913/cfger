#ifndef _CFGER_PARSER_H_
#define _CFGER_PARSER_H_

#include <stdbool.h>

#include "utils.h"
#include "config.h"
#include "lexer.h"

struct cfger_ArrayOfSection parse(char *file_content);

#endif