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

#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <xinput-gtk/xinput/XInputHelper.hpp>
#include <xinput-gtk/Utils.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include <cstdlib>

void set_prop(const int id, const std::string& key, const std::string& value) {
	std::string cmd = "xinput set-prop " + std::to_string(id) + key + " " + value;
	std::system(cmd.c_str());
}

std::vector<XInputDevice> XInputHelper::parse_xinput_list() {
	std::vector<XInputDevice> devices;
	std::string device_ids = Utils::get_cmd_output("xinput list --id-only");

	std::regex float_id_pattern(R"(\D*(\d+)\D*)");
	std::smatch match;

	std::istringstream iss(device_ids);
	std::string current_id;
	while (std::getline(iss, current_id)) {
		// Get the device ID
		std::regex_search(current_id, match, float_id_pattern);
		int device_id = std::stoi(match[1]);

		XInputDevice device(device_id);
		//device.set_float(current_id[0] < '0' or current_id[0] > '9');

		devices.push_back(device);
	}

	return devices;
}
