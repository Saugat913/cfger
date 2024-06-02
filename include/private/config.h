#ifndef _CFGER_PRIVATE_CONFIG_H_
#define _CFGER_PRIVATE_CONFIG_H_

#include "../cfger/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    FIELD_STRING,
    FIELD_MAP
} cfger_FieldValueType;

struct cfger_FieldMap
{
    char *key;
    char *value;
};

struct cfger_FieldValue
{
    cfger_FieldValueType type;
    union
    {
        char *str_value;
        struct cfger_FieldMap map_value;
    } value;
};

struct cfger_Field
{
    char *field_name;
    struct cfger_FieldValue value;
};

struct cfger_ArrayOfField
{
    struct cfger_Field *fields;
    size_t count;
    size_t capacity;
};

struct cfger_Section
{
    char *title_name;
    struct cfger_ArrayOfField field;
};

struct cfger_ArrayOfSection
{
    struct cfger_Section *sections;
    size_t count;
    size_t capacity;
};

struct cfger_Config_t
{
    struct cfger_ArrayOfSection sections;
};

typedef struct cfger_Config_t *cfger_Config;
typedef struct cfger_Section *cfger_Section;

bool cfger_init_array_of_field(struct cfger_ArrayOfField *fields, size_t initial_size);

bool cfger_push_to_field_array(struct cfger_ArrayOfField *fields, struct cfger_Field field);

bool cfger_init_array_of_section(struct cfger_ArrayOfSection *section_array, size_t initial_size);

bool cfger_push_to_section_array(struct cfger_ArrayOfSection *section_array, struct cfger_Section section);

void cfger_display_field(struct cfger_Field *field);

#endif