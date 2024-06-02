#include "parser.h"

enum cfger_State
{
    STATE_GLOBAL,
    STATE_SECTION_NAME,
    STATE_SECTION_NAME_END,

    STATE_END_OF_LINE,

    STATE_KEY,
    STATE_EQUAL,
    STATE_VALUE
};

void cfger_expectation_error(char *message, cfger_Token token)
{
    fprintf(stderr, "[ERROR] Expected %s but found %s\n", message, token_str[token]);
    exit(1);
}

void cfger_error(char *message)
{
    fprintf(stderr, "[ERROR] %s\n", message);
    exit(1);
}

struct cfger_ArrayOfSection cfger_parse(char *file_content)
{
    cfger_Lexer lexer;

    enum cfger_State state = STATE_GLOBAL;
    struct cfger_Section current_section = {0};
    struct cfger_Field current_field;
    struct cfger_ArrayOfSection sections = {0};

    cfger_init_array_of_section(&sections, 5);
    cfger_init_lexer(file_content, &lexer);
    cfger_get_next_token(&lexer);

    while (lexer.curr_token != TOKEN_EOF)
    {
        switch (state)
        {

        case STATE_GLOBAL:
            if (lexer.curr_token == TOKEN_END_OF_LINE)
                break;
            if (lexer.curr_token == TOKEN_BRACKET_OPEN)
                state = STATE_SECTION_NAME;
            else
                cfger_expectation_error("start of section", lexer.curr_token);
            break;

        case STATE_SECTION_NAME:
            if (lexer.curr_token != TOKEN_IDENTFIER)
                cfger_expectation_error("section name", lexer.curr_token);
            current_section.title_name = lexer.value;

            cfger_init_array_of_field(&current_section.field, 5);

            state = STATE_SECTION_NAME_END;
            break;

        case STATE_SECTION_NAME_END:
            if (lexer.curr_token != TOKEN_BRACKET_CLOSE)
                cfger_expectation_error("] to end section title", lexer.curr_token);
            state = STATE_END_OF_LINE;
            break;

        case STATE_END_OF_LINE:
            if (lexer.curr_token != TOKEN_END_OF_LINE)
                cfger_expectation_error(token_str[TOKEN_END_OF_LINE], lexer.curr_token);
            state = STATE_KEY;
            break;

        case STATE_KEY:
            if (lexer.curr_token == TOKEN_END_OF_LINE)
                break;
            if (lexer.curr_token == TOKEN_BRACKET_OPEN)
            {
                cfger_push_to_section_array(&sections, current_section);

                memset(&current_section, 0, sizeof(current_section));

                state = STATE_SECTION_NAME;
            }
            else if (lexer.curr_token == TOKEN_IDENTFIER)
            {
                current_field.field_name = lexer.value;
                state = STATE_EQUAL;
            }
            else
                cfger_expectation_error("key", lexer.curr_token);
            break;

        case STATE_EQUAL:
            if (lexer.curr_token != TOKEN_EQUAL)
                cfger_expectation_error("=", lexer.curr_token);
            state = STATE_VALUE;
            break;

        case STATE_VALUE:
            if (lexer.curr_token != TOKEN_STRING)
                cfger_expectation_error("value", lexer.curr_token);

            // For now we only parse string value
            //[TODO]: Support map and list

            current_field.value.type = FIELD_STRING;
            current_field.value.value.str_value = lexer.value;

            cfger_push_to_field_array(&current_section.field, current_field);

            state = STATE_END_OF_LINE;
            break;
        }

        cfger_get_next_token(&lexer);
    }

    cfger_push_to_section_array(&sections, current_section);

    return sections;
}

cfger_Config cfger_parse_config_file(char *file_name)
{
    char *content = cfger_read_config_file(file_name);

    if (content == NULL)
        return NULL;

    struct cfger_Config_t sections = {.sections = cfger_parse(content)};

    cfger_Config config = (cfger_Config)malloc(sizeof(struct cfger_Config_t));

    //[TODO]: Handle Memory error
    config[0] = sections;

    return config;
}