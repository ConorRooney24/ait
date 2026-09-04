# Update Command

The update command can be used to update one or more installed AppImages, given the target AppImages support updates.

## Synopsis
```
ait [GLOBAL OPTIONS] update [COMMAND OPTIONS] [APPIMAGE NAME]...
```

The update command may take any number of operands, including 0.

If no operands are given, ait will default to updating all installed AppImages.

The operands are names of installed AppImages which can be obtained using the ```installed``` command.

Some AppImages may not support updates. AppImages must contain update information for this command to work on them.

## Command Options

### --assume-yes
Automatically answers yes to any confirmation/warning messages.

## Example Usage
Update an installed AppImage
```
ait update app
```

Update all installed AppImages
```
ait update
```

Update an AppImage and ignore confirmation and warning messages
```
ait update --assume-yes app
```
