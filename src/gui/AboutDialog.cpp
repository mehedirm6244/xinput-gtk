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

#include <xinput-gtk/gui/AboutDialog.hpp>
#include <xinput-gtk/XInputGtk.hpp>
#include <iostream>

AboutDialog::AboutDialog() {
	set_modal(true);

	set_program_name("XInput GTK");
	set_authors(XInputGTK::AUTHORS);
	set_license(XInputGTK::LICENSE);
	set_comments(XInputGTK::COMMENT);
	set_website(XInputGTK::WEBSITE);
	try {
    set_logo(Gtk::IconTheme::get_default()->load_icon(
      "xorg", 128, Gtk::ICON_LOOKUP_USE_BUILTIN));
  } catch (const Gtk::IconThemeError& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
