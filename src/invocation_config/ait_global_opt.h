// ait_global_opt.h
// anything to do with global options

#ifndef AIT_GLOBAL_OPT_H
#define AIT_GLOBAL_OPT_H

#include <stdbool.h>

typedef enum
{
    AIT_GLOBAL_OPT_NONE,
    AIT_GLOBAL_OPT_HELP,
    AIT_GLOBAL_OPT_VERSION
} ait_global_opt_id_t;

ait_global_opt_id_t ait_which_global_opt(const char* str); // Returns the matching ait_global_opt_t for the string given. returns none if its not a valid global option string.
bool ait_does_global_opt_expect_value(ait_global_opt_id_t opt);

#endif
