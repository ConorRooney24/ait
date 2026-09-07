#include "ait_config.h"
#include <string.h>

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
