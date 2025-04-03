# xinput-gtk
A GTK3 frontend for Xorg XInput

![image](https://github.com/user-attachments/assets/e635b774-daab-4906-a059-fcbf1e87be84)

## Features
- List available input devices
- View detailed device information
- Float or reattach devices
- View and modify device properties
- Receive a popup warning if an `xinput` operation fails

## Dependencies
- `xorg-xinput`
- `gtkmm3` (Arch) or `libgtkmm-3.0-dev` (Debian/Ubuntu)

# Installation

## From AUR (Arch/Arch based distros)
The [xinput-gtk-git](https://aur.archlinux.org/packages/xinput-gtk-git) package is maintained by [softexpert](https://github.com/softexpert). Install it using any AUR helper:
```
yay -S xinput-gtk-git
```

## Manual Installation
```
git clone https://github.com/mehedirm6244/xinput-gtk
cd xinput-gtk
mkdir build && cd build
cmake ..
cmake --build .
```
To run the binary, either use it from the `/build` directory or move it to `/usr/bin` for system-wide access:
```
sudo mv xinput-gtk /usr/bin/
```
