#include "ait_cmd_opt.h"
#include <string.h>

ait_cmd_specific_opt_id_t ait_which_cmd_specific_option(const char* str, ait_cmd_id_t cmd)
{
    if (cmd == AIT_CMD_INSTALL)
    {
        if (strcmp(str, "--destination") == 0) return AIT_CMD_SPECIFIC_OPT_INSTALL_DESTINATION;
        if (strcmp(str, "--system") == 0)      return AIT_CMD_SPECIFIC_OPT_INSTALL_SYSTEM_INSTALL;
    }
    if (cmd == AIT_CMD_INSTALLED)
    {
        if (strcmp(str, "--short") == 0 || strcmp(str, "-s") == 0) return AIT_CMD_SPECIFIC_OPT_INSTALLED_SHORT_FORMAT;
    }
    if (cmd == AIT_CMD_UNINSTALL)
    {
        if (strcmp(str, "--keep-appimage") == 0) return AIT_CMD_SPECIFIC_OPT_UNINSTALL_KEEP_APPIMAGE;
        if (strcmp(str, "--assume-yes") == 0)    return AIT_CMD_SPECIFIC_OPT_UNINSTALL_ASSUME_YES;
    }
    if (cmd == AIT_CMD_UPDATE)
    {
        if (strcmp(str, "--assume-yes") == 0) return AIT_CMD_SPECIFIC_OPT_UPDATE_ASSUME_YES;
    }
    if (cmd == AIT_CMD_UPDATEABLE)
    {
        if (strcmp(str, "--short") == 0 || strcmp(str, "-s") == 0) return AIT_CMD_SPECIFIC_OPT_UPDATEABLE_SHORT_FORMAT;
    }

    return AIT_CMD_SPECIFIC_OPT_NONE;
}


bool ait_does_cmd_specific_opt_expect_value(ait_cmd_specific_opt_id_t opt)
{
    if (opt == AIT_CMD_SPECIFIC_OPT_INSTALL_DESTINATION) return true;

    return false;
}
