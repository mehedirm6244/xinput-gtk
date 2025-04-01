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

#ifndef XINPUT_GTK_HPP
#define XINPUT_GTK_HPP

#include <vector>
#include <glibmm/ustring.h>

namespace XInputGTK {
	const std::vector<Glib::ustring> AUTHORS = {
		"Mehedi Rahman Mahi"
	};
	constexpr const char* COMMENT = "A GTK3 frontend for Xorg XInput";
	constexpr const char* WEBSITE = "https://github.com/mehedirm6244/xinput-gtk";
	constexpr const char* WEBSITE_REPORT = "https://github.com/mehedirm6244/xinput-gtk/issues";
	constexpr const char* LICENSE = R"(This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.)";
} // namespace XInputGTK

#endif // XINPUT_GTK_HPP
