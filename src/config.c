#include "config.h"

bool init_array_of_field(struct ArrayOfField *fields, size_t initial_size)
{
    if (fields->fields != NULL)
        free(fields->fields);

    fields->fields = (struct Field *)malloc(sizeof(struct Field) * initial_size);

    if (fields->fields == NULL)
        return false;

    fields->count = 0;
    fields->capacity = initial_size;

    return true;
}

bool push_to_field_array(struct ArrayOfField *fields, struct Field field)
{
    if (fields->capacity <= fields->count)
    {
        fields->fields = (struct Field *)realloc(fields->fields, sizeof(struct Field) * (fields->capacity + 5));
        //[TODO]: Handle the unsufficeient memory

        fields->capacity = fields->capacity + 5;
    }

    fields->fields[fields->count++] = field;

    return true;
}

bool init_array_of_section(struct ArrayOfSection *section_array, size_t initial_size)
{
    if (section_array->sections != NULL)
        free(section_array->sections);

    section_array->sections = (struct Section *)malloc(sizeof(struct Section) * initial_size);

    if (section_array->sections == NULL)
        return false;

    section_array->count = 0;
    section_array->capacity = initial_size;

    return true;
}

bool push_to_section_array(struct ArrayOfSection *section_array, struct Section section)
{
    if (section_array->capacity <= section_array->count)
    {
        section_array->sections = (struct Section *)realloc(section_array->sections, sizeof(struct Field) * (section_array->capacity + 5));
        //[TODO]: Handle the unsufficeient memory

        section_array->capacity = section_array->capacity + 5;
    }

    section_array->sections[section_array->count++] = section;

    return true;
}

void display_field(struct Field *field)
{
    printf("    %s:", field->field_name);

    switch (field->value.type)
    {
    case FIELD_STRING:
        printf(" %s\n", field->value.value.str_value);
        break;
    default:
        printf("Unsupported type!");
        break;
    }
}

void display_section(struct Section *section)
{
    printf("Section Name:[%s]\n", section->title_name);

    for (size_t i = 0; i < section->field.count; i++)
    {
        display_field(&section->field.fields[i]);
    }
}