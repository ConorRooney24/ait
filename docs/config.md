# AIT Configuration
*This relates to the persistant config, not the invocation config (cli arguments)*

The config file can be found at ```~/.config/ait/config```.

Any options edited here will decide the default behaviour of any invocation of AIT.

Invocation Configuration will overwrite the persistent configuration options.

## Syntax
The AIT config file uses a syntax that is somewhat similar to [TOML](https://toml.io/en/), But far simpler. It does not support things like multi-line strings.

The syntax is made up of very simple key value pairs seperated by an equal sign.

A key value pair must be on one line. Each line must either be blank, a comment, or have a key value pair (that may be followed by a winged comment).

Each key is an **option**, and each value is the value for the given option.

Placeholders like <ICON_RES> and <APP_ID> may be used in value strings.

Below is an example of the syntax:
```
# This is a comment
key = "value"
key2 = 123 # also a comment
key3 = "~/apps/<APP_ID>/"
```

## Options
| Name/Key                         | Type   | Default Value                                     | Description                                                                     |
|----------------------------------|--------|---------------------------------------------------|---------------------------------------------------------------------------------|
| user_appimage_destination        | string | ~/.local/share/appimages/                         | The default location for AppImages to be relocated after user installs.         |
| user_icon_destination            | string | ~/.local/share/icons/hicolor/<ICON_RES>/<APP_ID>/ | The default location for icons to be relocated after user installs.             |
| user_desktop_entry_destination   | string | ~/.local/share/applications/                      | The default location for desktop entries to be relocated after user installs.   |
| system_appimage_destination      | string | /opt/<APP_ID>/                                    | The default location for AppImages to be relocated after system installs.       |
| system_icon_destination          | string | /usr/share/icons/hicolor/<ICON_RES>/<APP_ID>/     | The default location for icons to be relocated after system installs.           |
| system_desktop_entry_destination | string | /usr/share/applications/                          | The default location for desktop entries to be relocated after system installs. |
