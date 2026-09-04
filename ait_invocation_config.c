#include "ait_invocation_config.h"
#include <string.h>

#include <stdio.h>

ait_cmd_specific_opt_t ait_which_cmd_specific_option(const char* str, ait_cmd_t cmd)
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

ait_global_opt_t ait_which_global_opt(const char* str)
{
    if(strcmp(str, "-h") == 0 || strcmp(str, "--help") == 0)    return AIT_GLOBAL_OPT_HELP;
    if(strcmp(str, "-v") == 0 || strcmp(str, "--version") == 0) return AIT_GLOBAL_OPT_VERSION;
    return AIT_GLOBAL_OPT_NONE;
}

ait_cmd_t ait_which_cmd(const char* str)
{
    if (strcmp(str, "install") == 0)    return AIT_CMD_INSTALL;
    if (strcmp(str, "installed") == 0)  return AIT_CMD_INSTALLED;
    if (strcmp(str, "uninstall") == 0)  return AIT_CMD_UNINSTALL;
    if (strcmp(str, "update") == 0)     return AIT_CMD_UPDATE;
    if (strcmp(str, "updateable") == 0) return AIT_CMD_UPDATEABLE;
    return AIT_CMD_NONE;
}

bool ait_does_cmd_specific_opt_expect_value(ait_cmd_specific_opt_t opt)
{
    if (opt == AIT_CMD_SPECIFIC_OPT_INSTALL_DESTINATION) return true;

    return false;
}

bool ait_does_global_opt_expect_value(ait_global_opt_t opt)
{
    return false;
}

bool ait_does_cmd_expect_operand(ait_cmd_t cmd)
{
    if (cmd == AIT_CMD_INSTALLED) return false;

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
                            invocation_config.cmd_opts.install.operands.values[invocation_config.cmd_opts.install.operands.count] = strdup(argv[i]);
                            invocation_config.cmd_opts.install.operands.count++;
                            break;

                        case AIT_CMD_UNINSTALL:
                            invocation_config.cmd_opts.uninstall.operands.values[invocation_config.cmd_opts.uninstall.operands.count] = strdup(argv[i]);
                            invocation_config.cmd_opts.uninstall.operands.count++;
                            break;

                        case AIT_CMD_UPDATEABLE:
                            invocation_config.cmd_opts.updateable.operands.values[invocation_config.cmd_opts.updateable.operands.count] = strdup(argv[i]);
                            invocation_config.cmd_opts.updateable.operands.count++;
                            break;

                        case AIT_CMD_UPDATE:
                            invocation_config.cmd_opts.update.operands.values[invocation_config.cmd_opts.update.operands.count] = strdup(argv[i]);
                            invocation_config.cmd_opts.update.operands.count++;
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

    return invocation_config;
}
