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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <string>
#include <vector>

namespace Utils {
	const int CMD_OUTPUT_BUFSIZE = 128;

	std::string get_cmd_output(const std::string& cmd);

	bool check_installed(const std::string& program_name);

	std::string str_trim_space(const std::string& source);
	
	std::vector<XInputDevice> parse_xinput_list();
};

#endif // UTILS_HPP
