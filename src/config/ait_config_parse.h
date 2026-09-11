// ait_config_parse.h
// parses the config file to populate the config struct

#ifndef AIT_CONFIG_PARSE_H
#define AIT_CONFIG_PARSE_H

#include "ait_config.h"
#include "../helpers/ait_dynamic_array.h"
#include <stdlib.h>

typedef enum
{
    AIT_CONFIG_LINE_INVALID,          // Invalid syntax on line
    AIT_CONFIG_LINE_BLANK,            // A line with nothing on it but whitespace
    AIT_CONFIG_LINE_COMMENT,          // A line with only a comment
    AIT_CONFIG_LINE_KEY_VALUE,        // A line with a key and value but no winged comment
    AIT_CONFIG_LINE_KEY_VALUE_COMMENT // a line with a key, value, and a winged comment
} ait_config_line_id_t;

// Parses a single line from the config line
// Takes line, the line pulled from the file
// stores the detected key string in key (not validated)
// stores the detected value string in value
// returns the line type
ait_config_line_id_t ait_parse_config_line(const char* line, ait_da_char_t* key, ait_da_char_t* value);

ait_config_t ait_parse_config(const char* path);

#endif
