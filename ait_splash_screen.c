#include "ait_splash_screens.h"
#include <stdio.h>

void ait_print_help()
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
