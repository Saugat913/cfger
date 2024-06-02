#include "config.h"

bool cfger_init_array_of_field(struct cfger_ArrayOfField *fields, size_t initial_size)
{
    if (fields->fields != NULL)
        free(fields->fields);

    fields->fields = (struct cfger_Field *)malloc(sizeof(struct cfger_Field) * initial_size);

    if (fields->fields == NULL)
        return false;

    fields->count = 0;
    fields->capacity = initial_size;

    return true;
}

bool cfger_push_to_field_array(struct cfger_ArrayOfField *fields, struct cfger_Field field)
{
    if (fields->capacity <= fields->count)
    {
        fields->fields = (struct cfger_Field *)realloc(fields->fields, sizeof(struct cfger_Field) * (fields->capacity + 5));
        //[TODO]: Handle the unsufficeient memory

        fields->capacity = fields->capacity + 5;
    }

    fields->fields[fields->count++] = field;

    return true;
}

bool cfger_init_array_of_section(struct cfger_ArrayOfSection *section_array, size_t initial_size)
{
    if (section_array->sections != NULL)
        free(section_array->sections);

    section_array->sections = (struct cfger_Section *)malloc(sizeof(struct cfger_Section) * initial_size);

    if (section_array->sections == NULL)
        return false;

    section_array->count = 0;
    section_array->capacity = initial_size;

    return true;
}

bool cfger_push_to_section_array(struct cfger_ArrayOfSection *section_array, struct cfger_Section section)
{
    if (section_array->capacity <= section_array->count)
    {
        section_array->sections = (struct cfger_Section *)realloc(section_array->sections, sizeof(struct cfger_Section) * (section_array->capacity + 5));
        //[TODO]: Handle the unsufficeient memory
        section_array->capacity = section_array->capacity + 5;
    }

    section_array->sections[section_array->count] = section;
    section_array->count++;
    return true;
}

void cfger_write_field(struct cfger_Field *field, FILE *fp)
{
    fprintf(fp, "   %s = ", field->field_name);

    switch (field->value.type)
    {
    case FIELD_STRING:
        fprintf(fp, "\"%s\"\n", field->value.value.str_value);
        break;
    default:
        fprintf(fp, "null");
        break;
    }
}

void cfger_write_section(cfger_Section section, FILE *fp)
{
    fprintf(fp, "[%s]\n", section->title_name);

    for (size_t i = 0; i < section->field.count; i++)
    {
        cfger_write_field(&section->field.fields[i], fp);
    }
}

void cfger_write_config_to_file(char *file_name, cfger_Config config)
{
    FILE *fp = fopen(file_name, "w");

    for (size_t i = 0; i < config->sections.count; i++)
    {
        cfger_write_section(&config->sections.sections[i], fp);
        fprintf(fp, "\n\n");
    }
    fclose(fp);
}

cfger_Section cfger_get_section(char *section_name, cfger_Config config)
{
    for (size_t i = 0; i < config->sections.count; i++)
    {
        if (strcmp(section_name, config->sections.sections[i].title_name) == 0)
        {
            return &config->sections.sections[i];
        }
    }

    return NULL;
}

int cfger_get_str_value_of_key(char *key, cfger_Value *value_ptr, cfger_Section section)
{
    for (size_t i = 0; i < section->field.count; i++)
    {
        if (strcmp(key, section->field.fields[i].field_name) == 0)
        {
            if (section->field.fields[i].value.type != FIELD_STRING)
                return VALUE_INVALID_DATA_TYPE;

            *value_ptr = section->field.fields[i].value.value.str_value;
            return VALUE_EXIST;
        }
    }

    return VALUE_DOESNOT_EXIST;
}

// void cfger_display_config(cfger_Section )

//[WARNING]: Handle with care
void cfger_for_each_section(cfger_section_loop callback, void *data, cfger_Config config)
{
    for (size_t i = 0; i < config->sections.count; i++)
    {
        callback(&config->sections.sections[i], data);
    }
}

cfger_Config cfger_create_new_config()
{
    cfger_Config config = (cfger_Config)malloc(sizeof(struct cfger_Config_t));
    //[TODO]: Handle memory error
    cfger_init_array_of_section(&config->sections, 5);
    return config;
}
cfger_Section cfger_create_section(char *section_name, cfger_Config config)
{
    cfger_Section section = cfger_get_section(section_name, config);

    if (section != NULL)
        return section;

    struct cfger_Section section_static = {0};
    section_static.title_name = strdup(section_name);

    cfger_init_array_of_field(&section_static.field, 5);

    cfger_push_to_section_array(&config->sections, section_static);

    return config->sections.sections + (config->sections.count - 1);
}

int cfger_set_str_value(char *key, char *value, cfger_Section section)
{
    for (size_t i = 0; i < section->field.count; i++)
    {
        if (strcmp(key, section->field.fields[i].field_name) == 0)
        {
            if (section->field.fields[i].value.type != FIELD_STRING)
                return VALUE_INVALID_DATA_TYPE;

            char *tmp = section->field.fields[i].value.value.str_value;
            free(tmp);

            section->field.fields[i].value.value.str_value = strdup(value);

            return VALUE_EXIST;
        }
    }

    struct cfger_Field current_field;
    current_field.field_name = strdup(key);
    current_field.value.type = FIELD_STRING;
    current_field.value.value.str_value = strdup(value);

    cfger_push_to_field_array(&section->field, current_field);
    return VALUE_DOESNOT_EXIST;
}

void cfger_display_config(cfger_Config config)
{
    for (size_t i = 0; i < config->sections.count; i++)
    {
        cfger_write_section(&config->sections.sections[i], stdout);
        fprintf(stdout, "\n");
    }
}

void cfger_destroy_section(cfger_Section section)
{
    for (size_t i = 0; i < section->field.count; i++)
    {
        if (section->field.fields[i].value.type == FIELD_STRING)
        {
            free(section->field.fields[i].value.value.str_value);
        }
        free(section->field.fields[i].field_name);
    }

    free(section->title_name);
    free(section->field.fields);
}

void cfger_destroy_config(cfger_Config config)
{
    for (size_t i = 0; i < config->sections.count; i++)
    {
        cfger_destroy_section(&config->sections.sections[i]);
    }

    free(config->sections.sections);
    free(config);
}
