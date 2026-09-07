#include "ait_invocation_config.h"
#include "../ait_file_io_helpers.h"
#include <string.h>
#include <stdio.h>

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

ait_global_opt_id_t ait_which_global_opt(const char* str)
{
    if(strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0)    return AIT_GLOBAL_OPT_HELP;
    if(strcmp(str, "-v") == 0 || strcmp(str, "--version") == 0) return AIT_GLOBAL_OPT_VERSION;
    return AIT_GLOBAL_OPT_NONE;
}

ait_cmd_id_t ait_which_cmd(const char* str)
{
    if (strcmp(str, "install") == 0)    return AIT_CMD_INSTALL;
    if (strcmp(str, "installed") == 0)  return AIT_CMD_INSTALLED;
    if (strcmp(str, "uninstall") == 0)  return AIT_CMD_UNINSTALL;
    if (strcmp(str, "update") == 0)     return AIT_CMD_UPDATE;
    if (strcmp(str, "updateable") == 0) return AIT_CMD_UPDATEABLE;
    return AIT_CMD_NONE;
}

bool ait_does_cmd_specific_opt_expect_value(ait_cmd_specific_opt_id_t opt)
{
    if (opt == AIT_CMD_SPECIFIC_OPT_INSTALL_DESTINATION) return true;

    return false;
}

bool ait_does_global_opt_expect_value(ait_global_opt_id_t opt)
{
    return false;
}

bool ait_does_cmd_expect_operand(ait_cmd_id_t cmd)
{
    if (cmd == AIT_CMD_INSTALLED) return false;

    return true;
}

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

ait_invocation_config_t ait_arguments_parse(int argc, char** argv)
{
    ait_invocation_config_t invocation_config = {0}; // Init the config struct. now, this is delicate. if one of the enums changes order or something else changes about the struct, initing everything to 0 might not make sense then.


    // Parser state vars
    char** open_option = NULL; // Pointer to the option expecting a value. NULL means we are not waiting on a value.

    for (int i = 1; i < argc; i++)
    {
        // Are we waiting on an options value?
        if (open_option != NULL)
        {
            *open_option = argv[i];
            open_option = NULL;
        }
        // Does this value start with a dash?
        else if (argv[i][0] == '-')
        {
            // Is it a valid global option?
            if (ait_which_global_opt(argv[i]) != AIT_GLOBAL_OPT_NONE)
            {
                // Does this option expect a value?
                if (ait_does_global_opt_expect_value( ait_which_global_opt(argv[i]) ))
                {
                    // TODO
                    // right now, no globals expect values
                    // When we have globals that expect values we will need to add code here
                    // maybe just a switch that says "if its this global, then the pointer points here"
                }
                else
                {
                    // Set this global options value to true
                    if (ait_which_global_opt(argv[i]) == AIT_GLOBAL_OPT_VERSION) invocation_config.version = true;
                    if (ait_which_global_opt(argv[i]) == AIT_GLOBAL_OPT_HELP) invocation_config.help = true;
                }
            }
            else // not a global option
            {
                // If we have found a command
                if (invocation_config.cmd != AIT_CMD_NONE)
                {
                    // Is this a valid command specific option for our command?
                    if(ait_which_cmd_specific_option(argv[i], invocation_config.cmd) != AIT_CMD_SPECIFIC_OPT_NONE)
                    {
                        // Does this option expect a value?
                        if(ait_does_cmd_specific_opt_expect_value( ait_which_cmd_specific_option(argv[i], invocation_config.cmd) ))
                        {
                            // Switch for all options that expect a value
                            switch (ait_which_cmd_specific_option(argv[i], invocation_config.cmd))
                            {
                                case AIT_CMD_SPECIFIC_OPT_INSTALL_DESTINATION:
                                    // Ensure there is room for a destination argument
                                    if (i == argc-1)
                                    {
                                        printf("Error: No path given for install destination\n");
                                        exit(1);
                                    }

                                    open_option = &invocation_config.cmd_opts.install.destination;
                                    break;

                                default:
                                    printf("Internal Error: ait_invocation_config.c\n");
                                    exit(1);
                                    break;
                            }
                        }
                        else // Command does not expect a value
                        {
                            // Switch with all options that do not expect values
                            switch (ait_which_cmd_specific_option(argv[i], invocation_config.cmd))
                            {
                                case AIT_CMD_SPECIFIC_OPT_INSTALL_SYSTEM_INSTALL:
                                    invocation_config.cmd_opts.install.system_install = true;
                                    break;

                                case AIT_CMD_SPECIFIC_OPT_INSTALLED_SHORT_FORMAT:
                                    invocation_config.cmd_opts.installed.short_format = true;
                                    break;

                                case AIT_CMD_SPECIFIC_OPT_UNINSTALL_KEEP_APPIMAGE:
                                    invocation_config.cmd_opts.uninstall.keep_appimage = true;
                                    break;

                                case AIT_CMD_SPECIFIC_OPT_UNINSTALL_ASSUME_YES:
                                    invocation_config.cmd_opts.uninstall.assume_yes = true;
                                    break;

                                case AIT_CMD_SPECIFIC_OPT_UPDATE_ASSUME_YES:
                                    invocation_config.cmd_opts.update.assume_yes = true;
                                    break;

                                case AIT_CMD_SPECIFIC_OPT_UPDATEABLE_SHORT_FORMAT:
                                    invocation_config.cmd_opts.updateable.short_format = true;
                                    break;

                                default:
                                    printf("Internal Error: ait_invocation_config.c\n");
                                    exit(1);
                                    break;
                            }
                        }
                    }
                    else // This is not a valid cmd specific option for the command
                    {
                        printf("Error: Invalid option '%s' for command\n", argv[i]);
                        exit(1);
                    }
                }
                else // if we have not found our command
                {
                    printf("Error: Unidentified option '%s'.\n", argv[i]);
                    exit(1);
                }
            }
        }
        else // Value does not start with a dash
        {
            // Do we have a command?
            if (invocation_config.cmd != AIT_CMD_NONE)
            {
                // does this command expect an operand?
                if (ait_does_cmd_expect_operand(invocation_config.cmd))
                {
                    // switch of all commands that take an operand
                    switch (invocation_config.cmd)
                    {
                        case AIT_CMD_INSTALL:
                            if (!ait_add_operand(&invocation_config.cmd_opts.install.operands, argv[i]))
                            {
                                printf("Internal Error: Unable to allocate memory for operands\n");
                                exit(1);
                            }
                            break;

                        case AIT_CMD_UNINSTALL:
                            if (!ait_add_operand(&invocation_config.cmd_opts.uninstall.operands, argv[i]))
                            {
                                printf("Internal Error: Unable to allocate memory for operands\n");
                                exit(1);
                            }
                            break;

                        case AIT_CMD_UPDATEABLE:
                            if (!ait_add_operand(&invocation_config.cmd_opts.updateable.operands, argv[i]))
                            {
                                printf("Internal Error: Unable to allocate memory for operands\n");
                                exit(1);
                            }
                            break;

                        case AIT_CMD_UPDATE:
                            if (!ait_add_operand(&invocation_config.cmd_opts.update.operands, argv[i]))
                            {
                                printf("Internal Error: Unable to allocate memory for operands\n");
                                exit(1);
                            }
                            break;

                        default:
                            printf("Internal Error: Unexpected command accepting operand in ait_invocation_config.c\n");
                            exit(1);
                            break;
                    }
                }
                else // command does not expect an operand
                {
                    printf("Error: Unexpected Operand '%s' for command.\n", argv[i]);
                    exit(1);
                }
            }
            else // we do not have a command
            {
                // does this argument represent a valid command?
                if (ait_which_cmd(argv[i]) != AIT_CMD_NONE)
                {
                    invocation_config.cmd = ait_which_cmd(argv[i]);
                }
                else // not a valid command
                {
                    printf("Error: Invalid Command '%s'\n", argv[i]);
                    exit(1);
                }
            }
        }
    }

    // TODO run validation here. at this stage, we have parsed all of argv. we just need to ensure its valid. 
    // Validation
    switch (invocation_config.cmd)
    {
        case AIT_CMD_INSTALL:
            // If no operands given
            if (invocation_config.cmd_opts.install.operands.count <= 0)
            {
                // Only cause error if both help and version are false
                if (!invocation_config.help && !invocation_config.version)
                {
                    printf("Error: no operands given for install command (Operands should be paths to AppImages. Try ait --help for usage information)\n");
                    exit(1);
                }
            }
            // Check all operands to ensure they are files that exist
            for (size_t i = 0; i < invocation_config.cmd_opts.install.operands.count; i++)
            {
                if (!ait_does_file_exist(invocation_config.cmd_opts.install.operands.values[i]))
                {
                    printf("Error: File '%s' does not exist\n", invocation_config.cmd_opts.install.operands.values[i]);
                    exit(1);
                }
            }
            // Ensure install destination is valid
            if (invocation_config.cmd_opts.install.destination != NULL)
            {
                if (!ait_does_directory_exist(invocation_config.cmd_opts.install.destination))
                {
                    printf("Error: directory '%s' does not exist\n", invocation_config.cmd_opts.install.destination);
                    exit(1);
                }
            }
            break;

        case AIT_CMD_UNINSTALL:
            // We need to ensure that the operands passed here actually exist in our record of installed apps.
            // Check this during the actual operation though. TODO
            // Before uninstalling anything, ensure that all of the names are recognised installed apps
            // Need to implement the catalogue before that can be done though
            if (invocation_config.cmd_opts.uninstall.operands.count <= 0)
            {
                if (!invocation_config.help && !invocation_config.version)
                {
                    printf("Error: no operands given for uninstall command (Operands should be names of installed AppImages. Try ait --help for usage information)\n");
                    exit(1);
                }
            }
            break;

        case AIT_CMD_INSTALLED:
            // No validation needed at the moment
            break;

        case AIT_CMD_UPDATEABLE:
            // No validation needed
            // Operands here are not required so it doesnt matter if count is 0
            // Although, same with uninstall, we need to eventually make sure any operands given are installed appimages.
            // TODO
            break;

        case AIT_CMD_UPDATE:
            // Same as above. nothing needed at the moment. we will need stuff eventaully though
            // TODO
            break;

        default:
            // Case if there was no command. no validation needed at the moment.
            // If we add global options that take operands then we need to do something here TODO
            break;
    }

    return invocation_config;
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
