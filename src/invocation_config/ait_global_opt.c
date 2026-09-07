#include "ait_global_opt.h"
#include <string.h>

ait_global_opt_id_t ait_which_global_opt(const char* str)
{
    if(strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0)    return AIT_GLOBAL_OPT_HELP;
    if(strcmp(str, "-v") == 0 || strcmp(str, "--version") == 0) return AIT_GLOBAL_OPT_VERSION;
    return AIT_GLOBAL_OPT_NONE;
}

bool ait_does_global_opt_expect_value(ait_global_opt_id_t opt)
{
    return false;
}
