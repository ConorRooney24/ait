# ait Usage
## Synopsis
The general syntax of a ait invocation is as follows:
```
ait [GLOBAL OPTIONS] <COMMAND> [COMMAND OPTIONS] ...
```

Global options are options whose meaning is independent from the command (if any) chosen.

Command options are options that are dependent on a specific command.

The ellipses here represent the fact that the syntax is different depending on the chosen command. Some commands may require additional operands of different types; some may not.

Global options may come before or after the command and command options.

Command options **must** come after the command.

## Global Options
### '-h', '--help'
Displays a help screen.

If a command has been specified, the help screen will contain information on that command.

If no command has been specified, the help screen will give general usage information.

### '-v', '--version'
Displays the currently installed version of ait.


## Commands
| Command                                        | Description                      |
|------------------------------------------------|----------------------------------|
| [install](commands/install.md)                 | Installs an AppImage             |
| [uninstall](commands/uninstall.md)             | Uninstalls an Installed AppImage |
| [installed](commands/installed.md)             | Lists all installed AppImage     |
| [updateable](commands/updateable.md)           | Lists all updateable AppImage    |
| [update](commands/update.md)                   | Updates an AppImage/AppImages    |
