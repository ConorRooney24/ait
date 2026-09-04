// ait_invocation_config.h
// Parses cli arguments and stores results in an invocation config struct

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


// Each Commands Options Struct
typedef struct
{
    size_t operands_count;
    char** operands;

    char* destination; // NULL if destination option not given
    bool system_install;
} ait_install_opts_t;

typedef struct
{
    size_t operands_count;
    char** operands;

    bool keep_appimage;
    bool assume_yes;
} ait_uninstall_opts_t;


typedef struct
{
    bool short_format;
} ait_installed_opts_t;


typedef struct
{
    size_t operands_count;
    char** operands;

    bool short_format;
} ait_updateable_opts_t;


typedef struct
{
    size_t operands_count;
    char** operands;

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
