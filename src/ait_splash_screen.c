#include "ait_splash_screens.h"
#include <stdio.h>

void ait_print_help(ait_cmd_t cmd)
{
    switch (cmd)
    {
        case AIT_CMD_NONE:
            ait_print_help_main();
            break;

        case AIT_CMD_INSTALL:
            ait_print_help_install();
            break;

        case AIT_CMD_UNINSTALL:
            ait_print_help_uninstall();
            break;

        case AIT_CMD_INSTALLED:
            ait_print_help_installed();
            break;

        case AIT_CMD_UPDATEABLE:
            ait_print_help_updateable();
            break;

        case AIT_CMD_UPDATE:
            ait_print_help_update();
            break;

        default:
            printf("Internal Error: Unrecognised command - unable to print help screen.\n");
            exit(1);
    }
}

void ait_print_help_main()
{
    const char* help_screen = 
    AIT_ANSI_BOLD "Usage:" AIT_ANSI_RESET "\n"
    "    ait [GLOBAL OPTIONS] <COMMAND> [COMMAND OPTIONS] ...\n"
    "    ait <GLOBAL OPTIONS>\n"
    "\n"
    AIT_ANSI_BOLD "Description:" AIT_ANSI_RESET "\n"
    "    AIT - AppImage Integration Tool\n"
    "\n"
    AIT_ANSI_BOLD "Commands:" AIT_ANSI_RESET "\n"
    "    install      Install an AppImage\n"
    "    installed    List Installed AppImages\n"
    "    uninstall    Uninstall an AppImage\n"
    "    update       Update AppImages\n"
    "    updateable   List Updateable AppImages\n"
    "\n"
    AIT_ANSI_BOLD "Global Options:" AIT_ANSI_RESET "\n"
    "    -h, --help      Display a Help Menu\n"
    "    -v, --version   Display installed AIT Version\n"
    "\n\n\n"
    AIT_ANSI_ITALIC AIT_ANSI_FAINT "Try 'ait <COMMAND> --help' for command specific usage information" AIT_ANSI_RESET "\n";

    printf("%s", help_screen);
}

void ait_print_help_install()
{
    const char* help_screen =
    AIT_ANSI_BOLD "Usage:" AIT_ANSI_RESET "\n"
    "    ait [GLOBAL OPTIONS] install [COMMAND OPTIONS] <APPIMAGE PATH>...\n"
    "\n"
    AIT_ANSI_BOLD "Description:" AIT_ANSI_RESET "\n"
    "    Install one or more AppImages.\n"
    "\n"
    AIT_ANSI_BOLD "Arguments:" AIT_ANSI_RESET "\n"
    "    <APPIMAGE PATH>    Path to one or more AppImage files.\n"
    "\n"
    AIT_ANSI_BOLD "Options:" AIT_ANSI_RESET "\n"
    "    --destination <INSTALLATION PATH>   Override the install destination.\n"
    "    --system                            Install the AppImage system wide.\n"
    "\n"
    AIT_ANSI_BOLD "Examples:" AIT_ANSI_RESET "\n"
    "    ait install app.AppImage\n"
    "    ait install app1.AppImage app2.AppImage app3.AppImage\n"
    "    ait install *.AppImage\n"
    "    ait install app.AppImage --destination ~/Documents/\n"
    "\n";

    printf("%s", help_screen);
}

void ait_print_help_installed()
{
    const char* help_screen =
    AIT_ANSI_BOLD "Usage:" AIT_ANSI_RESET "\n"
    "    ait [GLOBAL OPTIONS] installed [COMMAND OPTIONS]\n"
    "\n"
    AIT_ANSI_BOLD "Description:" AIT_ANSI_RESET "\n"
    "    List currently installed AppImages.\n"
    "\n"
    AIT_ANSI_BOLD "Options:" AIT_ANSI_RESET "\n"
    "    -s, --short   List less information per record.\n"
    "\n"
    AIT_ANSI_BOLD "Examples:" AIT_ANSI_RESET "\n"
    "    ait installed\n"
    "    ait installed -s\n"
    "\n";

    printf("%s", help_screen);
}

void ait_print_help_uninstall()
{
    const char* help_screen =
    AIT_ANSI_BOLD "Usage:" AIT_ANSI_RESET "\n"
    "    ait [GLOBAL OPTIONS] uninstall [COMMAND OPTIONS] <APPIMAGE NAME>...\n"
    "\n"
    AIT_ANSI_BOLD "Description:" AIT_ANSI_RESET "\n"
    "    Uninstall one or more installed AppImages.\n"
    "\n"
    AIT_ANSI_BOLD "Arguments:" AIT_ANSI_RESET "\n"
    "    <APPIMAGE NAME>   Name of an installed AppImage.\n"
    "\n"
    AIT_ANSI_BOLD "Options:" AIT_ANSI_RESET "\n"
    "    --keep-appimage   Keep the AppImage file after uninstalling.\n"
    "    --assume-yes       Automatically answer yes to confirmations\n"
    "                      and warning messages.\n"
    "\n"
    AIT_ANSI_BOLD "Examples:" AIT_ANSI_RESET "\n"
    "    ait uninstall app\n"
    "    ait uninstall app --assume-yes\n"
    "\n";

    printf("%s", help_screen);
}

void ait_print_help_update()
{
    const char* help_screen =
    AIT_ANSI_BOLD "Usage:" AIT_ANSI_RESET "\n"
    "    ait [GLOBAL OPTIONS] update [COMMAND OPTIONS] [APPIMAGE NAME]...\n"
    "\n"
    AIT_ANSI_BOLD "Description:" AIT_ANSI_RESET "\n"
    "    Update one or more installed AppImages.\n"
    "\n"
    "    If no AppImage names are given, AIT will attempt to update all\n"
    "    installed AppImages.\n"
    "\n"
    AIT_ANSI_ITALIC AIT_ANSI_FAINT "    Note: AppImages must contain update information to support updating." AIT_ANSI_RESET "\n"
    "\n"
    AIT_ANSI_BOLD "Arguments:" AIT_ANSI_RESET "\n"
    "    [APPIMAGE NAME]   Name of an installed AppImage.\n"
    "\n"
    AIT_ANSI_BOLD "Options:" AIT_ANSI_RESET "\n"
    "    --assume-yes    Automatically answer yes to confirmations\n"
    "                   and warning messages.\n"
    "\n"
    AIT_ANSI_BOLD "Examples:" AIT_ANSI_RESET "\n"
    "    ait update app\n"
    "    ait update\n"
    "    ait update --assume-yes app\n"
    "\n";

    printf("%s", help_screen);
}

void ait_print_help_updateable()
{
    const char* help_screen =
    AIT_ANSI_BOLD "Usage:" AIT_ANSI_RESET "\n"
    "    ait [GLOBAL OPTIONS] updateable [COMMAND OPTIONS] [APPIMAGE NAME]...\n"
    "\n"
    AIT_ANSI_BOLD "Description:" AIT_ANSI_RESET "\n"
    "    List installed AppImages which can be updated.\n"
    "\n"
    "    If no AppImage names are given, AIT will check all installed\n"
    "    AppImages.\n"
    "\n"
    AIT_ANSI_ITALIC AIT_ANSI_FAINT "    Note: AppImages must contain update information to be checked." AIT_ANSI_RESET "\n"
    "\n"
    AIT_ANSI_BOLD "Arguments:" AIT_ANSI_RESET "\n"
    "    [APPIMAGE NAME]   Name of an installed AppImage.\n"
    "\n"
    AIT_ANSI_BOLD "Options:" AIT_ANSI_RESET "\n"
    "    -s, --short   List less information per record.\n"
    "\n"
    AIT_ANSI_BOLD "Examples:" AIT_ANSI_RESET "\n"
    "    ait updateable\n"
    "    ait updateable app\n"
    "    ait updateable -s\n"
    "\n";

    printf("%s", help_screen);
}
