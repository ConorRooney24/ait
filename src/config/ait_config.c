#include "ait_config.h"
#include <string.h>
#include <stdio.h>

ait_config_opt_id_t ait_which_config_opt(const char* str)
{
    if (strcmp(str, "user_appimage_destination") == 0)        return AIT_CONFIG_OPT_USER_APPIMAGE_DEST;
    if (strcmp(str, "user_icon_destination") == 0)            return AIT_CONFIG_OPT_USER_ICON_DEST;
    if (strcmp(str, "user_desktop_entry_destination") == 0)   return AIT_CONFIG_OPT_USER_ENTRY_DEST;
    if (strcmp(str, "system_appimage_destination") == 0)      return AIT_CONFIG_OPT_SYSTEM_APPIMAGE_DEST;
    if (strcmp(str, "system_icon_destination") == 0)          return AIT_CONFIG_OPT_SYSTEM_ICON_DEST;
    if (strcmp(str, "system_desktop_entry_destination") == 0) return AIT_CONFIG_OPT_SYSTEM_ENTRY_DEST;
    return AIT_CONFIG_OPT_NONE;
}

void ait_print_config_details(ait_config_t config)
{
    printf("User AppImage Dest: %s\n", config.user_appimage_dest);
    printf("User Icon Dest: %s\n", config.user_icon_dest);
    printf("User Entry Dest: %s\n", config.user_entry_dest);
    printf("System AppImage Dest: %s\n", config.system_appimage_dest);
    printf("System Icon Dest: %s\n", config.system_icon_dest);
    printf("System Entry Dest: %s\n", config.system_entry_dest);
}
