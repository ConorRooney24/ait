#include "ait_dynamic_array.h"
#include <stdlib.h>
#include <stdio.h>

void ait_da_char_init(ait_da_char_t *da)
{
    da->data = malloc(sizeof(char) * AIT_DA_CHAR_DEFAULT_CAP);

    if (da->data == NULL)
    {
        printf("Internal Error: Unable to allocate memory.\n");
        exit(1);
    }

    da->cap = AIT_DA_CHAR_DEFAULT_CAP;
    da->count = 0;
}

void ait_da_char_push(ait_da_char_t *da, const char ch)
{
    if (da == NULL || da->data == NULL)
    {
        printf("Internal Error: Unable to allocate memory.\n");
        exit(1);
    }

    if (da->cap <= 0)
    {
        printf("Internal Error: Unable to push to uninitialized dynamic array.\n");
        exit(1);
    }

    else if (da->count >= da->cap)
    {
        size_t new_cap = da->cap * 2;
        char* tmp = realloc(da->data, new_cap);

        if (tmp == NULL)
        {
            printf("Internal Error: Unable to allocate memory.\n");
            exit(1);
        }

        da->data = tmp;
    }

    da->data[da->count] = ch;
    da->count++;
}

void ait_da_char_free(ait_da_char_t *da)
{
    free(da->data);
    da->data = NULL;
    da->cap = 0;
    da->count = 0;
}
