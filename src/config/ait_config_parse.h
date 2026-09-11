// ait_config_parse.h
// parses the config file to populate the config struct

#ifndef AIT_CONFIG_PARSE_H
#define AIT_CONFIG_PARSE_H

#include "ait_config.h"
#include "../helpers/ait_dynamic_array.h"
#include <stdlib.h>

// Parses a single line from the config line
// Takes line, the line pulled from the file
// stores the detected key string in key (not validated)
// stores the detected value string in value
void ait_parse_config_line(const char* line, ait_da_char_t* key, ait_da_char_t* value);

ait_config_t ait_parse_config(const char* path);

#endif
