// ait_config_parse.c
// Test file for ait_config_parse

#include <stdio.h>
#include "../../src/config/ait_config_parse.h"

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

        int pass = 1;

        printf("[ Case %d ] ", i+1);
        printf("   Input String: '%s'\n", strings[i]);
        printf("   Expected Return: '%d' - Actual: '%d'\n", returns[i], ret);
        printf("   Expected Key: '%s' - Actual: '%s'\n", keys[i], k.data);
        printf("   Expected Value: '%s' - Actual: '%s'\n", values[i], v.data);
        if (returns[i] != ret) pass = 0;
        if (keys[i] != k.data) pass = 0;
        if (values[i] != v.data) pass = 0;
        printf("   %s\n", (pass == 1) ? "Pass" : "Fail");
        printf("\n");
    }

    return 0;
}
