#include "invocation_config/ait_invocation_config.h"
#include "invocation_config/ait_arg_parse.h"
#include "ait_splash_screens.h"
#include "config/ait_config_parse.h"
#include "helpers/ait_dynamic_array.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    ait_invocation_config_t cfg;

    cfg = ait_arguments_parse(argc, argv);

    ait_print_help(cfg.cmd);

    const char* str = "key = value";
    ait_da_char_t a;
    ait_da_char_init(&a);
    ait_da_char_t b;
    ait_da_char_init(&b);
    printf("parsing test on '%s':\n", str);

    ait_parse_config_line(str, &a, &b);
    //ait_print_invocation_config_details(cfg);

    printf("a: '%s'\n", a.data);
    printf("b: '%s'\n", b.data);
    return 0;
}
