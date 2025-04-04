/**
 * This file is from xinput-gtk - A GTK3 frontend for Xorg XInput.
 * Copyright (C) 2025 Mehedi Rahman Mahi
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EDIT_WINDOW_HPP
#define EDIT_WINDOW_HPP

#include <gtkmm.h>
#include <xinput-gtk/xinput/XInputDevice.hpp>

class EditWindow : public Gtk::Window {
public:
	EditWindow(const XInputDevice& device, const XInputDevice::Prop& prop);
	~EditWindow() = default;

private:
	XInputDevice m_device;
	XInputDevice::Prop m_prop;

	Gtk::Box m_box_main{Gtk::ORIENTATION_VERTICAL, 8};

	Gtk::Label m_label_name;
	Gtk::Entry m_entry_prop;

	Gtk::Box m_box_action{Gtk::ORIENTATION_HORIZONTAL, 6};
	Gtk::Button m_btn_apply;
	Gtk::Button m_btn_cancel;

	void connect_signals();
};

#endif // EDIT_WINDOW_HPP
