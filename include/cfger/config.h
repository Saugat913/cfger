#ifndef _CFGER_CONFIG_H_
#define _CFGER_CONFIG_H_

#include <stdbool.h>
#include <stddef.h>

enum cfger_VAL_STATUS
{
    VALUE_DOESNOT_EXIST,
    VALUE_INVALID_DATA_TYPE,
    VALUE_EXIST
};

struct cfger_Config_t;
struct cfger_Section;

typedef struct cfger_Config_t *cfger_Config;
typedef struct cfger_Section *cfger_Section;

typedef char *cfger_Value;

// Parse the file_name file and return config
// if error occured return NULL
cfger_Config cfger_parse_config_file(char *file_name);

void cfger_write_config_to_file(char *file_name, cfger_Config config);
void cfger_display_config(cfger_Config config);

// Return section by name section_name else NULL
cfger_Section cfger_get_section(char *section_name, cfger_Config config);

// Return VALUE_EXIST if value exist otherwise return VALUE_DOESNOT_EXIST
//  return VALUE_INVALID_DATA_TYPE if it is not of type string
int cfger_get_str_value_of_key(char *key, cfger_Value *value_ptr, cfger_Section section);

// void* data represent the area or structure where you store the result of operation
typedef void (*cfger_section_loop)(const cfger_Section section, void *data);

//[WARNING]: Handle with care
void cfger_for_each_section(cfger_section_loop callback, void *data, cfger_Config config);

cfger_Config cfger_create_new_config();
cfger_Section cfger_create_section(char *section_name, cfger_Config config);

int cfger_set_str_value(char *key, char *value, cfger_Section section);

void cfger_destroy_config(cfger_Config config);
#endif