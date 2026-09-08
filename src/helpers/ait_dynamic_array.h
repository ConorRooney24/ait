// ait_dynamic_array.h
// Dynamic array types. Handy for parsing

#ifndef AIT_DYNAMIC_ARRAY_H
#define AIT_DYNAMIC_ARRAY_H

#include <stdlib.h>

#define AIT_DA_CHAR_DEFAULT_CAP 16

typedef struct
{
    char* data;
    size_t count;
    size_t cap;
} ait_da_char_t;

void ait_da_char_init(ait_da_char_t *da);
void ait_da_char_push(ait_da_char_t *da, const char ch);
void ait_da_char_free(ait_da_char_t *da);

#endif
