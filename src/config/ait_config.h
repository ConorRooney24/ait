// ait_config.h
// the persistent config

#ifndef AIT_CONFIG_H
#define AIT_CONFIG_H

typedef struct
{
    char* user_appimage_dest;
    char* user_icon_dest;
    char* user_entry_dest;
    char* system_appimage_dest;
    char* system_icon_dest;
    char* system_entry_dest;
} ait_config_t;

typedef enum
{
    AIT_CONFIG_OPT_NONE,
    AIT_CONFIG_OPT_USER_APPIMAGE_DEST,
    AIT_CONFIG_OPT_USER_ICON_DEST,
    AIT_CONFIG_OPT_USER_ENTRY_DEST,
    AIT_CONFIG_OPT_SYSTEM_APPIMAGE_DEST,
    AIT_CONFIG_OPT_SYSTEM_ICON_DEST,
    AIT_CONFIG_OPT_SYSTEM_ENTRY_DEST
} ait_config_opt_id_t;

ait_config_opt_id_t ait_which_config_opt(const char* str);
void ait_print_config_details(ait_config_t config);

#endif
