// ait_invocation_config.h
// Parses cli arguments and stores results in an invocation config struct

#ifndef AIT_INVOCATION_CONFIG_H
#define AIT_INVOCATION_CONFIG_H

#include <stdbool.h>
#include <stdlib.h>

// Command Type
typedef enum
{
    AIT_CMD_NONE,
    AIT_CMD_INSTALL,
    AIT_CMD_UNINSTALL,
    AIT_CMD_INSTALLED,
    AIT_CMD_UPDATEABLE,
    AIT_CMD_UPDATE
} ait_cmd_t;

// Global Options type
typedef enum
{
    AIT_GLOBAL_OPT_NONE,
    AIT_GLOBAL_OPT_HELP,
    AIT_GLOBAL_OPT_VERSION
} ait_global_opt_t;

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
} ait_cmd_specific_opt_t;

// Operands type
typedef struct
{
    size_t count;
    char** values;
} ait_operands_t;

// Each Commands Options Struct
typedef struct
{
    ait_operands_t operands;

    char* destination; // NULL if destination option not given
    bool system_install;
} ait_install_opts_t;

typedef struct
{
    ait_operands_t operands;

    bool keep_appimage;
    bool assume_yes;
} ait_uninstall_opts_t;


typedef struct
{
    bool short_format;
} ait_installed_opts_t;


typedef struct
{
    ait_operands_t operands;

    bool short_format;
} ait_updateable_opts_t;


typedef struct
{
    ait_operands_t operands;

    bool assume_yes;
} ait_update_opts_t;


// Union to store command options for only a single command
typedef union
{
    ait_install_opts_t    install;
    ait_uninstall_opts_t  uninstall;
    ait_installed_opts_t  installed;
    ait_updateable_opts_t updateable;
    ait_update_opts_t     update;
} ait_cmd_opts_t;


// Main invocation config type
typedef struct
{
    ait_cmd_t cmd;

    // Global Options
    bool help;
    bool version;

    ait_cmd_opts_t cmd_opts;

} ait_invocation_config_t;

ait_global_opt_t ait_which_global_opt(const char* str); // Returns the matching ait_global_opt_t for the string given. returns none if its not a valid global option string.
ait_cmd_specific_opt_t ait_which_cmd_specific_option(const char* str, ait_cmd_t cmd); // Returns the matching cmd_specific_opt_t for the string and command given. returns none if the string does not match any cmd specific opt.
ait_cmd_t ait_which_cmd(const char* str); // returns an ait_cmd_t if the string matches a command. returns AIT_CMD_NONE if str matches no command.


bool ait_does_cmd_specific_opt_expect_value(ait_cmd_specific_opt_t opt);
bool ait_does_global_opt_expect_value(ait_global_opt_t opt);

bool ait_does_cmd_expect_operand(ait_cmd_t cmd);

bool ait_add_operand(ait_operands_t *operands, const char *str);

ait_invocation_config_t ait_arguments_parse(int argc, char** argv);

void ait_print_invocation_config_details(ait_invocation_config_t config);

#endif
