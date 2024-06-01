#ifndef _CFGER_PRIVATE_CONFIG_H_
#define _CFGER_PRIVATE_CONFIG_H_

#include "../cfger/config.h"
#include <stdio.h>
#include <stdlib.h>
bool init_array_of_field(struct ArrayOfField *fields, size_t initial_size);

bool push_to_field_array(struct ArrayOfField *fields, struct Field field);

bool init_array_of_section(struct ArrayOfSection *section_array, size_t initial_size);

bool push_to_section_array(struct ArrayOfSection *section_array, struct Section section);

void display_field(struct Field *field);
void display_section(struct Section *section);

#endif