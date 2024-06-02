#ifndef _CFGER_LEXER_H_
#define _CFGER_LEXER_H_

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    TOKEN_BRACKET_OPEN,
    TOKEN_BRACKET_CLOSE,
    TOKEN_CURLY_OPEN,
    TOKEN_CURLY_CLOSE,

    TOKEN_IDENTFIER,
    TOKEN_STRING,

    TOKEN_EQUAL,
    TOKEN_COMMA,
    TOKEN_END_OF_LINE,

    TOKEN_UNKNOWN,
    TOKEN_EOF
} cfger_Token;

extern char *token_str[TOKEN_EOF + 1];
typedef struct
{
    char *src;
    size_t pos;
    cfger_Token curr_token;

    char *value;
} cfger_Lexer;

void cfger_init_lexer(char *src, cfger_Lexer *lexer);
void cfger_get_next_token(cfger_Lexer *lexer);

// ONLY for debug purpose
void cfger_display_current_token(cfger_Lexer *lexer);

#endif