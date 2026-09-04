# Updateable Command

The updateable command can be used to list which installed AppImages can be updated.

## Synopsis
```
ait [GLOBAL OPTIONS] updateable [COMMAND OPTIONS] [APPIMAGE NAME]...
```

The updateable command may take any number of operands, including 0.

If no operands are given, ait will default to checking all installed AppImages.

The operands are names of installed AppImages which can be obtained using the ```installed``` command.

Some AppImages may not support updates. AppImages must contain update information for this command to work on them.

## Command Options

### -s, --short
Lists less information per record.

## Example Usage
Check all installed AppImages to see which can be updated
```
ait updateable
```

Check a specific installed AppImages to see if it can be updated
```
ait updateable app
```

Check all installed AppImages to see which can be updated and list in a short format
```
ait updateable -s
```
