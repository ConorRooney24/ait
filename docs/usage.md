# ait Usage
## Synopsis
The general syntax of a AIT invocation is as follows:
```
ait [GLOBAL OPTIONS] <COMMAND> [COMMAND OPTIONS] ...
```

Global options are options whose meaning is independent from the command (if any) chosen.

Command options are options that are dependent on a specific command. You can find a commands command options in its usage file (docs/commands/command_name.md).

The ellipses here represent the fact that the syntax is different depending on the chosen command. Some commands may require additional operands of different types; some may not.

Global options may come before or after the command and command options.

Command options **must** come after the command.

So an overview of syntax:
- An invocation of AIT must start with the word "ait"
- you may ommit the command. For example, you may just run ```ait --help```
- any command specific options must come after the command name
- The commands operand can go anywhere after the command name (so long as it is not directly after an option that expects an operand)
- If a global or command specific option requires an operand, the operand must come directly after the option
- global options may go anywhere after the word "ait"

## Global Options
### '-h', '--help'
Displays a help screen.

If a command has been specified, the help screen will contain information on that command.

If no command has been specified, the help screen will give general usage information.

### '-v', '--version'
Displays the currently installed version of AIT.


## Commands
| Command                                        | Description                      |
|------------------------------------------------|----------------------------------|
| [install](commands/install.md)                 | Installs an AppImage             |
| [uninstall](commands/uninstall.md)             | Uninstalls an Installed AppImage |
| [installed](commands/installed.md)             | Lists all installed AppImage     |
| [updateable](commands/updateable.md)           | Lists all updateable AppImage    |
| [update](commands/update.md)                   | Updates an AppImage/AppImages    |
