#include "lexer.h"



char *token_str[TOKEN_EOF + 1];

void init_lexer(char *src, Lexer *lexer)
{
    lexer->src = src;
    lexer->pos = 0;
    lexer->value = NULL;

    token_str[TOKEN_BRACKET_OPEN] = "]";
    token_str[TOKEN_BRACKET_CLOSE] = "[";
    token_str[TOKEN_CURLY_OPEN] = "}";
    token_str[TOKEN_CURLY_CLOSE] = "}";
    token_str[TOKEN_EQUAL] = "=";
    token_str[TOKEN_COMMA] = ",";
    token_str[TOKEN_END_OF_LINE] = "end of line";
    token_str[TOKEN_EOF] = "end of file";
    token_str[TOKEN_UNKNOWN] = "unknown";

    token_str[TOKEN_IDENTFIER] = "identifier";
    token_str[TOKEN_STRING] = "string";
}

void get_next_token(Lexer *lexer)
{
    while (lexer->src[lexer->pos] == ' ' || lexer->src[lexer->pos] == '\t')
        lexer->pos++;

    if (isalpha(lexer->src[lexer->pos]))
    {
        char *start = lexer->src + lexer->pos;
        while (isalnum(lexer->src[lexer->pos]))
        {
            lexer->pos++;
        }
        lexer->value = strndup(start, (lexer->src + lexer->pos) - start);
        lexer->curr_token = TOKEN_IDENTFIER;
    }
    else if (lexer->src[lexer->pos] == '"')
    {
        lexer->pos++;
        char *start = lexer->src + lexer->pos;
        while (lexer->src[lexer->pos] != '"' && lexer->src[lexer->pos] != '\0')
            lexer->pos++;

        if (lexer->src[lexer->pos] == '\0')
        {
            fprintf(stderr, "[ERROR] Expected end of string \" before end of line\n");
            lexer->curr_token = TOKEN_UNKNOWN;
        }
        else
        {
            lexer->value = strndup(start, (lexer->src + lexer->pos) - start);
            lexer->curr_token = TOKEN_STRING;
            lexer->pos++;
        }
    }
    else
    {
        Token tok;
        switch (lexer->src[lexer->pos])
        {
        case '[':
            tok = TOKEN_BRACKET_OPEN;
            break;
        case ']':
            tok = TOKEN_BRACKET_CLOSE;
            break;
        case '{':
            tok = TOKEN_CURLY_OPEN;
            break;
        case '}':
            tok = TOKEN_CURLY_CLOSE;
            break;
        case '=':
            tok = TOKEN_EQUAL;
            break;
        case ',':
            tok = TOKEN_COMMA;
            break;
        case '\n':
            tok = TOKEN_END_OF_LINE;
            break;
        case '\0':
            tok = TOKEN_EOF;
            break;
        default:
            lexer->curr_token = TOKEN_UNKNOWN;
        }
        lexer->pos++;
        lexer->curr_token = tok;
    }
}

void display_current_token(Lexer *lexer)
{
    switch (lexer->curr_token)
    {

    case TOKEN_BRACKET_OPEN:
        printf("[\n");
        break;
    case TOKEN_BRACKET_CLOSE:
        printf("]\n");
        break;
    case TOKEN_CURLY_OPEN:
        printf("{\n");
        break;
    case TOKEN_CURLY_CLOSE:
        printf("}\n");
        break;
    case TOKEN_IDENTFIER:
        printf("ID:%s\n", lexer->value);
        break;
    case TOKEN_STRING:
        printf("STR:%s\n", lexer->value);
        break;
    case TOKEN_EQUAL:
        printf("=\n");
        break;
    case TOKEN_COMMA:
        printf(",\n");
        break;
    case TOKEN_END_OF_LINE:
        printf("END OF LINE\n");
        break;
    default:
        printf("UNKNOWN TOKEN: %c\n", lexer->src[lexer->pos - 1]);
        break;
    }
}