#include"utils.h"


size_t cfger_get_file_size(FILE *fp)
{
    // Store current position of file
    long file_curr_pos = ftell(fp);

    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);

    // Restore the position
    fseek(fp, file_curr_pos, SEEK_SET);

    return file_size;
}

char *cfger_read_config_file(char *file_name)
{
    FILE *cfg_file = fopen(file_name, "r");

    if (cfg_file == NULL)
    {
        printf("[ERROR] Cannot open the file %s\n", file_name);
        return NULL;
    }
    size_t file_size = cfger_get_file_size(cfg_file);

    char *file_content = (char *)malloc(sizeof(char) * file_size);
    if (fread(file_content, sizeof(char), file_size, cfg_file) != file_size)
    {
        fprintf(stderr, "[ERROR] Cannot read the config file %s\n", file_name);
        free(file_content);
        return NULL;
    }
    file_content[file_size] = '\0';
    return file_content;
}
