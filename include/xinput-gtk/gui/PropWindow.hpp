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

#ifndef PROP_WINDOW_HPP
#define PROP_WINDOW_HPP

#include <gtkmm.h>
#include <xinput-gtk/xinput/XInputDevice.hpp>

class PropWindow : public Gtk::Window {
public:
	PropWindow(const XInputDevice& device);
	~PropWindow() = default;

protected:
	Gtk::TreeView m_tree_view;
	Glib::RefPtr<Gtk::TreeStore> m_tree_store;

	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() {
			add(col_id);
			add(col_name);
			add(col_value);
    }

    Gtk::TreeModelColumn<int> col_id;
		Gtk::TreeModelColumn<std::string> col_name;
		Gtk::TreeModelColumn<std::string> col_value;
	};

	ModelColumns columns;

private:
	XInputDevice m_device;

	Gtk::Box m_box_main{Gtk::ORIENTATION_VERTICAL, 10};

	Gtk::Label m_label_name;

	Gtk::Box m_box_scrolledwindow{Gtk::ORIENTATION_VERTICAL};
	Gtk::Frame m_frame_scrolledwindow;
	Gtk::ScrolledWindow m_scrolledwindow;

	Gtk::ActionBar m_actionbar;
	Gtk::Button m_btn_reload;

	void populate_tree();
	void connect_signals();
};

#endif // PROP_WINDOW_HPP
