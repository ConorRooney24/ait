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

void ait_print_config_details(ait_config_t config);

#endif
