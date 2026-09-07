#include "ait_invocation_config.h"
#include <string.h>
#include <stdio.h>

bool ait_add_operand(ait_operands_t *operands, const char *str)
{
    char **new_values = realloc(operands->values, (operands->count + 1) * sizeof(*operands->values));

    if (new_values == NULL) return false;

    operands->values = new_values;

    operands->values[operands->count] = strdup(str);

    if (operands->values[operands->count] == NULL) return false;

    operands->count++;

    return true;
}
void ait_print_invocation_config_details(ait_invocation_config_t config)
{
    printf("Global Options:\n");
    printf("\tVersion: %s\n", config.version ? "true" : "false");
    printf("\tHelp: %s\n", config.help ? "true" : "false");
    printf("\n");

    printf("Command:\n");
    switch (config.cmd)
    {
        case AIT_CMD_NONE:
            printf("\tnone\n");
            break;

        case AIT_CMD_INSTALL:
            printf("\tinstall\n");
            break;

        case AIT_CMD_UNINSTALL:
            printf("\tuninstall\n");
            break;

        case AIT_CMD_INSTALLED:
            printf("\tinstalled\n");
            break;

        case AIT_CMD_UPDATEABLE:
            printf("\tupdateable\n");
            break;

        case AIT_CMD_UPDATE:
            printf("\tupdate\n");
            break;

        default:
            printf("\tERROR: NULL\n");
            break;
    }
    printf("\n");

    printf("Command Options:\n");
    switch (config.cmd)
    {
        case AIT_CMD_NONE:
            printf("\tnone\n");
            break;

        case AIT_CMD_INSTALL:
            printf("\tSystem Install: %s\n", config.cmd_opts.install.system_install ? "true" : "false");
            printf("\tDestination: %s\n", config.cmd_opts.install.destination != NULL ? config.cmd_opts.install.destination : "null");
            printf("\tOperands:\n");
            if (config.cmd_opts.install.operands.count == 0) printf("\t\tnone\n");
            for (size_t i = 0; i < config.cmd_opts.install.operands.count; i++)
            {
                printf("\t\t%s\n", config.cmd_opts.install.operands.values[i]);
            }
            break;

        case AIT_CMD_UNINSTALL:
            printf("\tKeep AppImage: %s\n", config.cmd_opts.uninstall.keep_appimage ? "true" : "false");
            printf("\tAssume Yes: %s\n", config.cmd_opts.uninstall.assume_yes ? "true" : "false");
            printf("\tOperands:\n");
            if (config.cmd_opts.uninstall.operands.count == 0) printf("\t\tnone\n");
            for (size_t i = 0; i < config.cmd_opts.uninstall.operands.count; i++)
            {
                printf("\t\t%s\n", config.cmd_opts.uninstall.operands.values[i]);
            }
            break;

        case AIT_CMD_INSTALLED:
            printf("\tShort Format: %s\n", config.cmd_opts.installed.short_format ? "true" : "false");
            break;

        case AIT_CMD_UPDATEABLE:
            printf("\tShort Format: %s\n", config.cmd_opts.updateable.short_format ? "true" : "false");
            printf("\tOperands:\n");
            if (config.cmd_opts.updateable.operands.count == 0) printf("\t\tnone\n");
            for (size_t i = 0; i < config.cmd_opts.updateable.operands.count; i++)
            {
                printf("\t\t%s\n", config.cmd_opts.updateable.operands.values[i]);
            }
            break;

        case AIT_CMD_UPDATE:
            printf("\tAssume Yes: %s\n", config.cmd_opts.update.assume_yes ? "true" : "false");
            printf("\tOperands:\n");
            if (config.cmd_opts.update.operands.count == 0) printf("\t\tnone\n");
            for (size_t i = 0; i < config.cmd_opts.update.operands.count; i++)
            {
                printf("\t\t%s\n", config.cmd_opts.update.operands.values[i]);
            }
            break;

        default:
            printf("\tERROR: NULL\n");
            break;
    }
}
