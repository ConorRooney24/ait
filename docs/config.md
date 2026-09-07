# AIT Configuration
*This relates to the persistant config, not the invocation config (cli arguments)*

The config file can be found at ```~/.config/ait/config```.

It uses [TOML](https://toml.io/en/).

Any options edited here will decide the default behaviour of any invocation of AIT.

Invocation Configuration will overwrite the persistent configuration options.

To change an option, just type its name as in the table below, an equal sign, and then its new value.

Placeholders like <RESOLUTION> and <APP_NAME> may be used.

## Options
| Name/Key                         | Type   | Default Value                                         | Description                                                                     |
|----------------------------------|--------|-------------------------------------------------------|---------------------------------------------------------------------------------|
| user_appimage_destination        | string | ~/.local/share/appimages/                             | The default location for AppImages to be relocated after user installs.         |
| user_icon_destination            | string | ~/.local/share/icons/hicolor/<RESOLUTION>/<APP_NAME>/ | The default location for icons to be relocated after user installs.             |
| user_desktop_entry_destination   | string | ~/.local/share/applications/                          | The default location for desktop entries to be relocated after user installs.   |
| system_appimage_destination      | string | /opt/<APP_NAME>/                                      | The default location for AppImages to be relocated after system installs.       |
| system_icon_destination          | string | /usr/share/icons/hicolor/<RESOLUTION>/<APP_NAME>/     | The default location for icons to be relocated after system installs.           |
| system_desktop_entry_destination | string | /usr/share/applications/                              | The default location for desktop entries to be relocated after system installs. |
