cmake_minimum_required(VERSION 3.10)
project(xinput-gtk)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Include directories
include_directories(./include)
include_directories(${GTKMM_INCLUDE_DIRS})

# Define the executable and its source files
add_executable(xinput-gtk
  src/main.cpp
  src/Utils.cpp
  src/gui/Window.cpp
  src/gui/AboutDialog.cpp
  src/gui/InfoWindow.cpp
  src/gui/PropWindow.cpp
  src/gui/EditWindow.cpp
  src/gui/ReattachWindow.cpp
  src/xinput/XInputDevice.cpp
  src/xinput/XInputHelper.cpp
)

# Link libraries
target_link_libraries(xinput-gtk ${GTKMM_LIBRARIES})
