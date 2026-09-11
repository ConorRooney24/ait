#include "ait_config_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Buffer size when reading a line from the config file
#define AIT_CONFIG_LINE_BUFF_SIZE 128

// State for the line parser.
// A good line parse should mean 'walking' up through all of these states
typedef enum
{
    AIT_LINE_PARSER_STATE_START_WHITESPACE,
    AIT_LINE_PARSER_STATE_KEY,
    AIT_LINE_PARSER_STATE_MID_WHITESPACE,
    AIT_LINE_PARSER_STATE_VALUE,
    AIT_LINE_PARSER_STATE_END_WHITESPACE
} ait_line_parser_state_t;

ait_config_line_id_t ait_parse_config_line(const char* line, ait_da_char_t* key, ait_da_char_t* value)
{
    // Note: we dont need to check for quotes at this stage
    // at this point, quotes are considered part of the key
    // in a later validation step, we can check the expected
    // datatype of the option, and then decide if the key
    // expects quotes, and if it does, we can make sure they
    // are valid

    // TODO Add better error messages here


    ait_line_parser_state_t state = AIT_LINE_PARSER_STATE_START_WHITESPACE;
    bool equal_found = false;
    int quotes_found = 0;

    char ch; // current char
    for (int i = 0;; i++)
    {
        ch = line[i];

        if (ch == ' ')
        {
            if (quotes_found == 1 && state == AIT_LINE_PARSER_STATE_VALUE) // If we are inside a quote
            {
                // Treat the space as a part of the value
                ait_da_char_push(value, ch);
            }
            else
            {
                switch (state)
                {
                    case AIT_LINE_PARSER_STATE_START_WHITESPACE:
                        break;
                    case AIT_LINE_PARSER_STATE_KEY:
                        state++;
                        break;
                    case AIT_LINE_PARSER_STATE_MID_WHITESPACE:
                        break;
                    case AIT_LINE_PARSER_STATE_VALUE:
                        state++;
                        break;
                    case AIT_LINE_PARSER_STATE_END_WHITESPACE:
                        break;
                    default:
                        // Error
                        return AIT_CONFIG_LINE_INVALID;
                }
            }
        }
        else if (ch == '\n' || ch == '\0')
        {
            switch (state)
            {
                case AIT_LINE_PARSER_STATE_START_WHITESPACE:
                    return AIT_CONFIG_LINE_BLANK;
                    break;
                case AIT_LINE_PARSER_STATE_END_WHITESPACE:
                    if (equal_found == false) return AIT_CONFIG_LINE_INVALID; // Error
                    ait_da_char_push(key, '\0');
                    ait_da_char_push(value, '\0');
                    return AIT_CONFIG_LINE_KEY_VALUE;
                    break;
                case AIT_LINE_PARSER_STATE_VALUE:
                    if (quotes_found == 1) // If we are inside a quote
                    {
                        return AIT_CONFIG_LINE_INVALID;
                    }
                    else // not inside quotes
                    {
                        if (equal_found == false) return AIT_CONFIG_LINE_INVALID;
                        ait_da_char_push(key, '\0');
                        ait_da_char_push(value, '\0');
                        return AIT_CONFIG_LINE_KEY_VALUE;
                    }
                case AIT_LINE_PARSER_STATE_MID_WHITESPACE:
                case AIT_LINE_PARSER_STATE_KEY:
                default:
                    // Error
                    return AIT_CONFIG_LINE_INVALID;
            }
        }
        else if (ch == '#')
        {
            if (state >= AIT_LINE_PARSER_STATE_VALUE)
            {
                if (equal_found == false) return AIT_CONFIG_LINE_INVALID; // Error
                ait_da_char_push(key, '\0');
                ait_da_char_push(value, '\0');
                return AIT_CONFIG_LINE_KEY_VALUE_COMMENT;
            }
            else if (state == AIT_LINE_PARSER_STATE_START_WHITESPACE)
            {
                return AIT_CONFIG_LINE_COMMENT;
            }
            else
            {
                // Error
                return AIT_CONFIG_LINE_INVALID;
            }
        }
        else if (ch == '=')
        {
            if (equal_found) return AIT_CONFIG_LINE_INVALID; // Error

            if (state == AIT_LINE_PARSER_STATE_VALUE)
            {
                equal_found = true;
                state++;
            }
            else if (state == AIT_LINE_PARSER_STATE_MID_WHITESPACE)
            {
                equal_found = true;
            }
            else
            {
                // Error
                return AIT_CONFIG_LINE_INVALID;
            }
        }
        else if (ch == '"')
        {
            switch (state)
            {
                case AIT_LINE_PARSER_STATE_MID_WHITESPACE:
                case AIT_LINE_PARSER_STATE_VALUE:
                    state++;
                    quotes_found++;
                    ait_da_char_push(value, ch);
                    break;
                case AIT_LINE_PARSER_STATE_END_WHITESPACE:
                case AIT_LINE_PARSER_STATE_START_WHITESPACE:
                case AIT_LINE_PARSER_STATE_KEY:
                default:
                    // Error
                    return AIT_CONFIG_LINE_INVALID;
            }
        }
        else // normal char
        {
            if (state == AIT_LINE_PARSER_STATE_START_WHITESPACE) state++;
            if (state == AIT_LINE_PARSER_STATE_MID_WHITESPACE) state++;
            if (state == AIT_LINE_PARSER_STATE_END_WHITESPACE) return AIT_CONFIG_LINE_INVALID; // Error
            if (state == AIT_LINE_PARSER_STATE_KEY)
            {
                ait_da_char_push(key, ch);
            }
            else if (state == AIT_LINE_PARSER_STATE_VALUE)
            {
                ait_da_char_push(value, ch);
            }
            else
            {
                // Error
                return AIT_CONFIG_LINE_INVALID;
            }
        }
    }

}


ait_config_t ait_parse_config(const char* path)
{
    ait_config_t config = {0};

    FILE* fp = fopen(path, "r");
    if (!fp)
    {
        printf("Error: Unable to open config file\n");
        exit(1);
    }

    // Line Buffer
    char buff[AIT_CONFIG_LINE_BUFF_SIZE];
    while(fgets(buff, AIT_CONFIG_LINE_BUFF_SIZE, fp) != NULL)
    {
        // TODO Implement this
        // - parse each line
        // validate
        // continue
    }

    return config;
}
