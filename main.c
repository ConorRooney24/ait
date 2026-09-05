#include "ait_invocation_config.h"
#include "ait_splash_screens.h"

int main(int argc, char** argv)
{
    ait_invocation_config_t cfg;

    cfg = ait_arguments_parse(argc, argv);

    ait_print_help(cfg.cmd);

    //ait_print_invocation_config_details(cfg);

    return 0;
}
