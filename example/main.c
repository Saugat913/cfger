#include "cfger/config.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{

    cfger_Config config = cfger_parse_config_file("config.txt");

    if (config == NULL)
    {
        printf("ERROR while opening file\n");
        return 1;
    }

    cfger_Section new_test_section = cfger_create_section("test", config);

    cfger_set_str_value("key1", "value1", new_test_section);

    cfger_display_config(config);

    cfger_destroy_config(config);

    return 0;
}
