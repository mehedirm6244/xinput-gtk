# xinput-gtk
xinput-gtk is a GTK3 frontend for Xorg XInput

![Screenshot](https://i.ibb.co.com/nMJbvsrQ/Mn5KK9g.png)

## Features
- List available input devices
- View detailed information of a device
- Float or reattach devices
- View and modify device properties

## Dependencies
- `xorg-xinput`
- `gtkmm-3`

## Installation
```
git clone https://github.com/mehedirm6244/xinput-gtk
cd xinput-gtk
mkdir build; cd build
cmake ..
cmake --build . -j 4
```
