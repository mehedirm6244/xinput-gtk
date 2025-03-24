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

#include <xinput-gtk/Utils.hpp>
#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <xinput-gtk/gui/PropWindow.hpp>
#include <vector>
#include <iostream>

PropWindow::PropWindow(const XInputDevice& device) : m_device(device) {
	set_title("");
	set_default_size(500, 400);
	set_border_width(8);
	set_modal(true);

	// Title
	m_label_name.set_label("Properties of " + m_device.get_name());

	// Configure TreeView
	m_tree_store = Gtk::TreeStore::create(columns);
	m_tree_view.append_column("ID", columns.col_id);
	m_tree_view.append_column("Name", columns.col_name);
	m_tree_view.append_column("Value", columns.col_value);
	m_tree_view.set_model(m_tree_store);
	m_tree_view.get_column(1)->set_expand(true); // Expand `name` column

	populate_tree();

	// Configure ActionBar
	m_btn_reload.set_image_from_icon_name("view-refresh");
	m_btn_reload.set_tooltip_text("Reload XInput list");
	m_actionbar.pack_end(m_btn_reload);

	// Organize layout
	m_scrolledwindow.add(m_tree_view);
	m_frame_scrolledwindow.add(m_box_scrolledwindow);
	m_box_scrolledwindow.pack_start(m_scrolledwindow);
	m_box_scrolledwindow.pack_end(m_actionbar, Gtk::PACK_SHRINK);

	m_box_main.pack_start(m_label_name, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_frame_scrolledwindow);
	
	// Connect signals
	connect_signals();

	add(m_box_main);
	show_all_children();
}

void PropWindow::populate_tree() {
	std::cout << "Loading properties of '" << m_device.get_name() << "'\n";
	m_tree_store->clear();
	std::vector<XInputDevice::Prop> props_list = m_device.get_props();

	for (const auto& prop : props_list) {
		Gtk::TreeModel::Row row = *(m_tree_store->append());
		row[columns.col_id] = prop.id;
		row[columns.col_name] = prop.name;
		row[columns.col_value] = prop.val;
	}

	m_tree_view.expand_all();
}

void PropWindow::connect_signals() {
	m_btn_reload.signal_clicked().connect(
		sigc::mem_fun(*this, &PropWindow::populate_tree));
}
