/**
 * Some tools for this project
 */

#include "tools.h"

int next_rnd_int(int upper)
{
    int rnd = (int)(upper * (rand() / (RAND_MAX + 1.0)));
    return rnd + 1;
}

clock_t get_current_clock()
{
    return clock();
}

double clock_to_ms(const clock_t stop, const clock_t start)
{
    return (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
}

char* read_file_content(char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL) return "";

    fseek(fp, 0L, SEEK_END);
    long file_length = ftell(fp);
    if (file_length <= 0) return NULL;
    rewind(fp);

    char* str_buf = malloc(sizeof(char)*(file_length + 1));
    size_t new_len = fread(str_buf, sizeof(char), file_length, fp);
    str_buf[new_len] = '\0'; // Terminator

    fclose(fp);
    return str_buf;
}
