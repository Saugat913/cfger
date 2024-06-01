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
} Token;

extern char *token_str[TOKEN_EOF + 1];
typedef struct
{
    char *src;
    size_t pos;
    Token curr_token;

    char *value;
} Lexer;

void init_lexer(char *src, Lexer *lexer);
void get_next_token(Lexer *lexer);

// ONLY for debug purpose
void display_current_token(Lexer *lexer);

#endif