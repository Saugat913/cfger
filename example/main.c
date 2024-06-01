#include "cfger/config.h"

int main(int argc, char const *argv[])
{

    struct ArrayOfSection sections = parse_config_file("config.txt");

    for (size_t i = 0; i < sections.count; i++)
    {
        display_section(&sections.sections[i]);
    }

    return 0;
}
