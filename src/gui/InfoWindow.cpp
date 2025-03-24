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

#include <xinput-gtk/gui/InfoWindow.hpp>
#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <iostream>

InfoWindow::InfoWindow(const XInputDevice& device) : m_device(device) {
	set_title("");
	set_default_size(500, 400);
	set_border_width(8);
	set_modal(true);

	std::cout << "Loading information of '" << m_device.get_name() << "'\n";

	// Title
	m_label_name.set_label("Information of " + m_device.get_name());

	// Configure TextView
	m_txtview_info.set_editable(false);
	m_txtview_info.set_cursor_visible(false);
	m_txtview_info.set_top_margin(8);
	m_txtview_info.set_left_margin(8);

	// Set TextView content
	m_txtview_info.get_buffer()->set_text(m_device.get_info());

	// Organize layout
	m_frame_txtview.add(m_scrolledwindow_txtview);
	m_scrolledwindow_txtview.add(m_txtview_info);

	m_box_main.pack_start(m_label_name, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_frame_txtview);

	add(m_box_main);
	show_all_children();
}
