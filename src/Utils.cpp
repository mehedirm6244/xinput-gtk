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
#include <iostream>
#include <array>
#include <cstring>
#include <filesystem>
#include <gtkmm/messagedialog.h>

std::string Utils::get_cmd_output(const std::string& cmd) {
	constexpr int CMD_OUTPUT_BUFSIZE = 128;
	char buffer[CMD_OUTPUT_BUFSIZE];
	std::string full_cmd = cmd + " 2>&1";  // Redirect stderr to stdout
	std::ostringstream result;

	FILE* pipe = popen(full_cmd.c_str(), "r");
	if (!pipe) {
		std::cerr << "Failed to open pipe (Utils::get_cmd_output)" << std::endl;
		return "";
	}

	while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
		result << buffer;
	}
	pclose(pipe);
	return result.str();
}

bool Utils::check_installed(const std::string& program_name) {
	const std::array<std::string, 2> bin_dirs = { "/bin/", "/usr/bin/" };
	for (auto dir : bin_dirs) {
		if (std::filesystem::exists(dir + program_name)) {
			return true;
		}
	}
	return false;
}

std::string Utils::str_trim_space(const std::string& source) {
	std::string result_str;
	bool in_spaces = false;

	for (char ch : source) {
		if (std::isspace(ch) and in_spaces) {
			continue;
		}
		result_str += ch;
		in_spaces = std::isspace(ch);	
	}

	// Trim leading spaces
	size_t start = result_str.find_first_not_of(" \t\n\r\f\v");
	result_str = (start == std::string::npos) ? "" : result_str.substr(start);

	// Trim trailing spaces
	size_t end = result_str.find_last_not_of(" \t\n\r\f\v");
	result_str = (end == std::string::npos) ? "" : result_str.substr(0, end + 1);

	return result_str;
}

void Utils::show_popup(const std::string& message) {
	auto dialog = Gtk::MessageDialog("Info");
	dialog.set_secondary_text(message);
	dialog.run();
}
