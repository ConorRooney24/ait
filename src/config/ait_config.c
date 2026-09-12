#include "ait_config.h"
#include <stdio.h>

void ait_print_config_details(ait_config_t config)
{
    printf("User AppImage Dest: %s\n", config.user_appimage_dest);
    printf("User Icon Dest: %s\n", config.user_icon_dest);
    printf("User Entry Dest: %s\n", config.user_entry_dest);
    printf("System AppImage Dest: %s\n", config.system_appimage_dest);
    printf("System Icon Dest: %s\n", config.system_icon_dest);
    printf("System Entry Dest: %s\n", config.system_entry_dest);
}
