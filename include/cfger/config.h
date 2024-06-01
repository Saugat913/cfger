#ifndef _CFGER_CONFIG_H_
#define _CFGER_CONFIG_H_

#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    FIELD_STRING,
    FIELD_MAP
} FieldValueType;

struct FieldMap
{
    char *key;
    char *value;
};

struct FieldValue
{
    FieldValueType type;
    union
    {
        char *str_value;
        struct FieldMap map_value;
    } value;
};

struct Field
{
    char *field_name;
    struct FieldValue value;
};

struct ArrayOfField
{
    struct Field *fields;
    size_t count;
    size_t capacity;
};

struct Section
{
    char *title_name;
    struct ArrayOfField field;
};

struct ArrayOfSection
{
    struct Section *sections;
    size_t count;
    size_t capacity;
};
struct ArrayOfSection parse_config_file(char *file_name);
void display_section(struct Section *section);
#endif