// ait_splash_screens.h
// Functions for printing splash screens such as usage menus

#ifndef AIT_SPLASH_SCREENS_H
#define AIT_SPLASH_SCREENS_H

#include "ait_invocation_config.h"

#define AIT_ANSI_BOLD      "\x1b[1m"
#define AIT_ANSI_FAINT     "\x1b[2m"
#define AIT_ANSI_ITALIC    "\x1b[3m"
#define AIT_ANSI_UNDERLINE "\x1b[4m"
#define AIT_ANSI_RESET     "\x1b[0m"

void ait_print_help(ait_cmd_t cmd);

void ait_print_help_main();
void ait_print_help_install();
void ait_print_help_installed();
void ait_print_help_uninstall();
void ait_print_help_update();
void ait_print_help_updateable();

#endif
