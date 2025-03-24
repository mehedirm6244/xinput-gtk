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

#include <xinput-gtk/gui/Window.hpp>
#include <xinput-gtk/gui/AboutDialog.hpp>
#include <xinput-gtk/gui/InfoWindow.hpp>
#include <xinput-gtk/gui/PropWindow.hpp>
#include <xinput-gtk/Utils.hpp>
#include <xinput-gtk/XInputGtk.hpp>
#include <iostream>

Window::Window() {
	set_title("XInput GTK");
	set_default_size(500, 450);

	// Configure Menubar
	m_help_menuitem.set_label("Help");
	m_help_report.set_label("Report a Bug");
	m_help_about.set_label("About");

	m_help_menuitem.set_submenu(m_help_menu);
	m_help_menu.append(m_help_report);
	m_help_menu.append(m_help_about);

	m_menubar.append(m_help_menuitem);

	// Configure TreeView container
	m_frame_treeview.set_margin_top(8);
	m_frame_treeview.set_margin_bottom(8);
	m_frame_treeview.set_margin_start(8);
	m_frame_treeview.set_margin_end(8);
	m_frame_treeview.add(m_box_scrolledwindow);
	m_box_scrolledwindow.pack_start(m_scrolledwindow);
	m_box_scrolledwindow.pack_end(m_actionbar, Gtk::PACK_SHRINK);
	m_scrolledwindow.add(m_tree_view);
	
	// Configure TreeView
	m_tree_store = Gtk::TreeStore::create(columns);
	m_tree_view.set_model(m_tree_store);
	m_tree_view.append_column("ID", columns.col_id);
	m_tree_view.append_column("Name", columns.col_name);
	m_tree_view.append_column("Type", columns.col_type);
	m_tree_view.get_column(1)->set_expand(true); // Expand name column
	m_tree_view.get_column(2)->set_expand(true); // Expand type column

	populate_tree();

	// Configure ActionBar
	m_btn_reload.set_image_from_icon_name("view-refresh");
	m_btn_reload.set_tooltip_text("Reload XInput list");

	m_btn_info.set_image_from_icon_name("info");
	m_btn_info.set_tooltip_text("Info");

	m_btn_prop.set_image_from_icon_name("settings-configure");
	m_btn_prop.set_tooltip_text("Properties");

	m_actionbar.pack_start(m_btn_info);
	m_actionbar.pack_start(m_btn_prop);
	m_actionbar.pack_end(m_btn_reload);

	// Organize Layout
	m_box_main.pack_start(m_menubar, Gtk::PACK_SHRINK);
	m_box_main.pack_start(m_frame_treeview);

	// Connect Signals
	connect_signals();

	add(m_box_main);
	show_all_children();
}

void Window::populate_tree() {
	std::cout << "Loading device list" << std::endl;
	m_tree_store->clear();
	m_device_list = Utils::parse_xinput_list();

	Gtk::TreeModel::Row parent;

	for (const auto& device : m_device_list) {
		Gtk::TreeModel::Row row;
		if (device.is_master() or device.is_float()) {
			row = *(m_tree_store->append());
			if (device.is_master()) {
				parent = row;
			}
		} else {
			row = *(m_tree_store->append(parent.children()));
		}

		row[columns.col_name] = device.get_name();
		row[columns.col_type] = device.get_type();
		row[columns.col_id] = device.get_id();
		row[columns.col_device] = device;
	}
	m_tree_view.expand_all();
}

void Window::connect_signals() {
	m_btn_reload.signal_clicked().connect(
		sigc::mem_fun(*this, &Window::populate_tree));

	m_btn_info.signal_clicked().connect(
		sigc::mem_fun(*this, &Window::handle_sig_info));

	m_btn_prop.signal_clicked().connect(
		sigc::mem_fun(*this, &Window::handle_sig_prop));

	m_tree_view.signal_row_activated().connect(
		[this](const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
			handle_sig_info();
		}
	);

	m_help_report.signal_activate().connect(
		sigc::mem_fun(*this, &Window::handle_sig_report));

	m_help_about.signal_activate().connect(
		sigc::mem_fun(*this, &Window::handle_sig_about));
}

void Window::handle_sig_info() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_tree_view.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		XInputDevice current_device = row[columns.col_device];
		InfoWindow* infowindow = new InfoWindow(current_device);
		infowindow->set_transient_for(*this);
		infowindow->show();
		infowindow->signal_hide().connect([infowindow]() {
			delete infowindow;
		});
	}
}

void Window::handle_sig_prop() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_tree_view.get_selection();
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		XInputDevice current_device = row[columns.col_device];
		PropWindow* propwindow = new PropWindow(current_device);
		propwindow->set_transient_for(*this);
		propwindow->show();
		propwindow->signal_hide().connect([propwindow]() {
			delete propwindow;
		});
	}
}

void Window::handle_sig_about() {
	AboutDialog aboutdialog;
	aboutdialog.set_transient_for(*this);
	aboutdialog.run();
}

void Window::handle_sig_report() {
	try {
		Gio::AppInfo::launch_default_for_uri(XInput_GTK::WEBSITE_REPORT);
	} catch (const Glib::Error& err) {
		g_warning("Failed to open link: %s", err.what().c_str());
	}
}
