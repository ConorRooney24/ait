// ait_config_opt.h
// Individual options that can be used in the config file

#ifndef AIT_CONFIG_OPT_H
#define AIT_CONFIG_OPT_H

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

#endif
