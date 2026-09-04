# Install Command

The install command can be used to install an AppImage.

## Synopsis
```
ait [GLOBAL OPTIONS] install [COMMAND OPTIONS] <APPIMAGE PATH>...
```

The install command may take any number of operands greater than one.

The operands must be paths to AppImage files.

## Command Options

### --destination <INSTALLATION PATH>
Overrides the install destination. Whatever destination given here is where the AppImage file will be stored after install.

### --system
Installs the AppImage System Wide (instead of for the current user).

## Example Usage
Install an AppImage:
```
ait install app.AppImage
```

Install Multiple AppImages:
```
ait install app1.AppImage app2.AppImage app3.AppImage
```

Install all AppImages in the current directory:
```
ait install *.AppImage
```

Install an AppImage and set the install directory to ~/Documents/
```
ait install app.AppImage --destination ~/Documents/
```
