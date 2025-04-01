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

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <gtkmm.h>
#include <vector>
#include <xinput-gtk/xinput/XInputDevice.hpp>

class Window : public Gtk::Window {
public:
	Window();
	~Window() = default;

protected:
	Gtk::TreeView m_tree_view;
	Glib::RefPtr<Gtk::TreeStore> m_tree_store;

	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(col_id);
			add(col_name);
			add(col_type);
			add(col_device);
    }

		Gtk::TreeModelColumn<int> col_id;
		Gtk::TreeModelColumn<std::string> col_name;
		Gtk::TreeModelColumn<std::string> col_type;
		Gtk::TreeModelColumn<XInputDevice> col_device;
	};

	ModelColumns columns;

private:
	std::vector<XInputDevice> m_device_list;
	std::vector<int> m_masters_list;

	Gtk::Box m_box_main{Gtk::ORIENTATION_VERTICAL};

	// Menubar
	Gtk::MenuBar m_menubar;
	Gtk::Menu m_help_menu;
	Gtk::MenuItem m_help_menuitem;
	Gtk::MenuItem m_help_about;
	Gtk::MenuItem m_help_report;

	// Scrolledwindow (contains TreeView)
	Gtk::Frame m_frame_treeview;
	Gtk::ScrolledWindow m_scrolledwindow;
	Gtk::Box m_box_scrolledwindow{Gtk::ORIENTATION_VERTICAL};

	// ActionBar
	Gtk::ActionBar m_actionbar;
	Gtk::Button m_btn_reload;
	Gtk::Button m_btn_info;
	Gtk::Button m_btn_prop;
	Gtk::Button m_btn_float;
	Gtk::Button m_btn_attach;
	
	void populate_tree();

	// Signal Handlers
	void handle_sig_info();
	void handle_sig_prop();
	void handle_sig_float();
	void handle_sig_attach();
	void handle_sig_about();
	void handle_sig_report();
	void handle_sig_selchange();
	void connect_signals();
};

#endif // WINDOW_HPP
