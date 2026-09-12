// ait_config_parse.c
// Test file for ait_config_parse

#include <stdio.h>
#include "../../src/config/ait_config_parse.h"
#include <string.h>

#define TEST_CASES 11

int main(void)
{
    printf("Testing ait_config_parse_line\n");

    const char* strings[TEST_CASES] = 
    {
        "key = value",
        "key value",
        "# comment",
        "key value value",
        "key = value = value",
        "",
        "key = value # comment",
        "key = \"value\"",
        "\"key\" = value",
        "key = \"value value value\"",
        "\"key\" = value"
    };

    ait_config_line_id_t returns[TEST_CASES] =
    {
        AIT_CONFIG_LINE_KEY_VALUE,
        AIT_CONFIG_LINE_INVALID,
        AIT_CONFIG_LINE_COMMENT,
        AIT_CONFIG_LINE_INVALID,
        AIT_CONFIG_LINE_INVALID,
        AIT_CONFIG_LINE_BLANK,
        AIT_CONFIG_LINE_KEY_VALUE_COMMENT,
        AIT_CONFIG_LINE_KEY_VALUE,
        AIT_CONFIG_LINE_INVALID,
        AIT_CONFIG_LINE_KEY_VALUE,
        AIT_CONFIG_LINE_INVALID
    };

    const char* keys[TEST_CASES] = 
    {
        "key",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "key",
        "key",
        NULL,
        "key",
        NULL
    };

    const char* values[TEST_CASES] = 
    {
        "value",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "value",
        "\"value\"",
        NULL,
        "\"value value value\"",
        NULL
    };

    for (int i = 0; i < TEST_CASES; i++)
    {
        ait_da_char_t k;
        ait_da_char_init(&k);
        ait_da_char_t v;
        ait_da_char_init(&v);
        ait_config_line_id_t ret;

        ret = ait_parse_config_line(strings[i], &k, &v);


        printf("\x1b[34m\x1b[1m[ Case %d ] \x1b[0m\n", i+1);
        printf("Input String: '%s'\n", strings[i]);
        printf("Expected Return: '%d' - Actual: '%d'\n", returns[i], ret);
        printf("Expected Key: '%s' - Actual: '%s'\n", keys[i], k.data);
        printf("Expected Value: '%s' - Actual: '%s'\n", values[i], v.data);
        printf("\n");
        printf("Detailed String View:\n");

        if (keys[i] != NULL)
        {
            printf("      Expected Key |");
            for (int j = 0; j <= strlen(keys[i]); j++)
            {
                printf(" %c |", keys[i][j] == '\0' ? '0' : keys[i][j]);
            }
            printf("\n");
        }
        if (k.data != NULL)
        {
            printf("        Actual Key |");
            for (int j = 0; j <= strlen(k.data); j++)
            {
                printf(" %c |", k.data[j] == '\0' ? '0' : k.data[j]);
            }
            printf("\n");
        }
        if (values[i] != NULL)
        {
            printf("    Expected Value |");
            for (int j = 0; j <= strlen(values[i]); j++)
            {
                printf(" %c |", values[i][j] == '\0' ? '0' : values[i][j]);
            }
            printf("\n");
        }
        if (v.data != NULL)
        {
            printf("     Actual values |");
            for (int j = 0; j <= strlen(v.data); j++)
            {
                printf(" %c |", v.data[j] == '\0' ? '0' : v.data[j]);
            }
            printf("\n");
        }

        int pass = 1;
        if (returns[i] != ret) pass = 0;
        if (keys[i] != k.data) pass = 0;
        if (values[i] != v.data) pass = 0;
        printf("%s\n", (pass == 1) ? "\x1b[32mPass\x1b[0m" : "\x1b[31mFail\x1b[0m");
        printf("\n\n\n");
    }

    return 0;
}
