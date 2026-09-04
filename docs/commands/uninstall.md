# Uninstall Command

The uninstall command can be used to uninstall AppImages.

## Synopsis
```
ait [GLOBAL OPTIONS] uninstall [COMMAND OPTIONS] <APPIMAGE NAME>...
```

The uninstall command may take any number of operands greater than one.

The operands are names of installed AppImages which can be obtained using the ```installed``` command.

## Command Options

### --keep-appimage
Only removes the installation record and .desktop entry. the AppImage file will stay in the install directory.

### --assume-yes
Automatically answers yes to any confirmation/warning messages.

## Example Usage
Uninstall an AppImage.
```
ait uninstall app
```

Unisntall an AppImage and skip confirmations.
```
ait uninstall app --assume-yes
```
