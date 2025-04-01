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

#include <xinput-gtk/gui/EditWindow.hpp>
#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <xinput-gtk/xinput/XInputHelper.hpp>

EditWindow::EditWindow(const XInputDevice& device, const XInputDevice::Prop& prop)
	: m_device(device),
	m_prop(prop) {

	set_title("");
	set_modal(true);
	set_border_width(8);
	set_default_size(300, 0);
	set_resizable(false);

	// Title
	m_label_name.set_label(m_prop.name);

	// Entry Widget with initial prop value
	m_entry_prop.set_text(m_prop.val);

	// Configure Action Box
	m_btn_apply.set_image_from_icon_name("dialog-ok");
	m_btn_apply.set_label("Apply");

	m_btn_cancel.set_image_from_icon_name("dialog-cancel");
	m_btn_cancel.set_label("Cancel");

	m_box_action.pack_end(m_btn_cancel, Gtk::PACK_SHRINK);
	m_box_action.pack_end(m_btn_apply, Gtk::PACK_SHRINK);

	// Organize Layout
	m_box_main.pack_start(m_label_name, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_entry_prop, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_box_action, Gtk::PACK_SHRINK);

	// Connect Signals
	connect_signals();

	add(m_box_main);
	show_all_children();
}

void EditWindow::connect_signals() {
	m_btn_cancel.signal_clicked().connect([this]() {
		close();
	});

	m_btn_apply.signal_clicked().connect([this]() {
		XInputHelper::set_prop(m_device.get_id(), m_prop.id, m_entry_prop.get_text());
		close();
	});
}
