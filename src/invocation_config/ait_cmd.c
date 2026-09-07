#include "ait_cmd.h"
#include <string.h>

ait_cmd_id_t ait_which_cmd(const char* str)
{
    if (strcmp(str, "install") == 0)    return AIT_CMD_INSTALL;
    if (strcmp(str, "installed") == 0)  return AIT_CMD_INSTALLED;
    if (strcmp(str, "uninstall") == 0)  return AIT_CMD_UNINSTALL;
    if (strcmp(str, "update") == 0)     return AIT_CMD_UPDATE;
    if (strcmp(str, "updateable") == 0) return AIT_CMD_UPDATEABLE;
    return AIT_CMD_NONE;
}

bool ait_does_cmd_expect_operand(ait_cmd_id_t cmd)
{
    if (cmd == AIT_CMD_INSTALLED) return false;

    return true;
}
