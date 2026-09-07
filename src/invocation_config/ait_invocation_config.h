// ait_invocation_config.h
// Parses cli arguments and stores results in an invocation config struct

#ifndef AIT_INVOCATION_CONFIG_H
#define AIT_INVOCATION_CONFIG_H

#include <stdbool.h>
#include <stdlib.h>
#include "ait_cmd.h"
#include "ait_global_opt.h"
#include "ait_cmd_opt.h"

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
    ait_cmd_id_t cmd;

    // Global Options
    bool help;
    bool version;

    ait_cmd_opts_t cmd_opts;

} ait_invocation_config_t;

bool ait_add_operand(ait_operands_t *operands, const char *str);
void ait_print_invocation_config_details(ait_invocation_config_t config);

#endif
