// ait_cmd_opt_h
// anything to do with command specific options

#ifndef AIT_CMD_OPT_H
#define AIT_CMD_OPT_H

#include "ait_cmd.h"

// Command Specific Options type
typedef enum
{
    // The naming here is AIT_CMD_SPECIFIC_OPT_<command>_<option_name>

    AIT_CMD_SPECIFIC_OPT_NONE,

    AIT_CMD_SPECIFIC_OPT_INSTALL_SYSTEM_INSTALL,
    AIT_CMD_SPECIFIC_OPT_INSTALL_DESTINATION,

    AIT_CMD_SPECIFIC_OPT_INSTALLED_SHORT_FORMAT,

    AIT_CMD_SPECIFIC_OPT_UNINSTALL_KEEP_APPIMAGE,
    AIT_CMD_SPECIFIC_OPT_UNINSTALL_ASSUME_YES,

    AIT_CMD_SPECIFIC_OPT_UPDATE_ASSUME_YES,

    AIT_CMD_SPECIFIC_OPT_UPDATEABLE_SHORT_FORMAT,
} ait_cmd_specific_opt_id_t;


ait_cmd_specific_opt_id_t ait_which_cmd_specific_option(const char* str, ait_cmd_id_t cmd); // Returns the matching cmd_specific_opt_t for the string and command given. returns none if the string does not match any cmd specific opt.
bool ait_does_cmd_specific_opt_expect_value(ait_cmd_specific_opt_id_t opt);

#endif
