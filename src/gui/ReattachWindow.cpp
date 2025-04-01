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

#include <xinput-gtk/gui/ReattachWindow.hpp>
#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <xinput-gtk/xinput/XInputHelper.hpp>

ReattachWindow::ReattachWindow(
	const XInputDevice& device,
	const std::vector<int>& master_list
	)
	: m_device(device) {

	set_title("");
	set_modal(true);
	set_default_size(300, 0);
	set_resizable(false);
	set_border_width(8);

	// Set Title
	m_label_name.set_label("Reattach \'" + m_device.get_name() +"\' to master");

	// Populate ComboBox
	for (auto master : master_list) {
		m_combo_masters.append(std::to_string(master));
	}

	// Configure Action Box
	m_btn_apply.set_image_from_icon_name("dialog-ok");
	m_btn_apply.set_label("Apply");

	m_btn_cancel.set_image_from_icon_name("dialog-cancel");
	m_btn_cancel.set_label("Cancel");

	m_box_action.pack_end(m_btn_cancel, Gtk::PACK_SHRINK);
	m_box_action.pack_end(m_btn_apply, Gtk::PACK_SHRINK);

	// Organize Layout
	m_box_main.pack_start(m_label_name, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_combo_masters, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_box_action, Gtk::PACK_SHRINK);

	// Connect Signals
	connect_signals();

	add(m_box_main);
	show_all_children();
}

void ReattachWindow::connect_signals() {
	m_btn_cancel.signal_clicked().connect([this]() {
		close();
	});

	m_btn_apply.signal_clicked().connect([this]() {
		std::string selection = m_combo_masters.get_active_text();
		if (!selection.empty()) {
			XInputHelper::set_master(m_device.get_id(), std::stoi(selection));
			close();
		}
	});
}
