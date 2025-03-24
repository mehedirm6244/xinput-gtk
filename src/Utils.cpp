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
#include <vector>
#include <regex>

std::string Utils::get_cmd_output(const std::string& cmd) {
	std::ostringstream result;
	char buffer[Utils::CMD_OUTPUT_BUFSIZE];

	FILE* pipe = popen(cmd.c_str(), "r");
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

std::vector<XInputDevice> Utils::parse_xinput_list() {
	std::vector<XInputDevice> devices;
	std::string device_ids = Utils::get_cmd_output("xinput list --id-only");
	std::regex id_pattern(R"(\D*(\d+)\D*)");
	std::smatch match;

	std::istringstream iss(device_ids);
	std::string line;
	while (std::getline(iss, line)) {
		if (std::regex_search(line, match, id_pattern)) {
			try {
				int device_id = std::stoi(match[1]);
				XInputDevice device(device_id);
				devices.push_back(device);
			} catch (const std::exception& e) {
				std::cerr << "Invalid device ID: " << line << " - " << e.what() << std::endl;
			}
		}
	}

	return devices;
}
