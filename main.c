#include "ait_invocation_config.h"
#include "ait_splash_screens.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    ait_invocation_config_t cfg;

    cfg = ait_arguments_parse(argc, argv);


    if (cfg.help)
    {
        ait_print_help();
    }

    printf("\n");

    ait_print_invocation_config_details(cfg);

    return 0;
}
