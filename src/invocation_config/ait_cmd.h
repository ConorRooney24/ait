// ait_cmd.h
// Anything to do with commands

#ifndef AIT_CMD_H
#define AIT_CMD_H

#include <stdbool.h>

typedef enum
{
    AIT_CMD_NONE,
    AIT_CMD_INSTALL,
    AIT_CMD_UNINSTALL,
    AIT_CMD_INSTALLED,
    AIT_CMD_UPDATEABLE,
    AIT_CMD_UPDATE
} ait_cmd_id_t;


ait_cmd_id_t ait_which_cmd(const char* str); // returns an ait_cmd_t if the string matches a command. returns AIT_CMD_NONE if str matches no command.
bool ait_does_cmd_expect_operand(ait_cmd_id_t cmd);

#endif
