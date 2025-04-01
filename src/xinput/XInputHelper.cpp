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

#include <xinput-gtk/xinput/XInputHelper.hpp>
#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <xinput-gtk/Utils.hpp>
#include <vector>
#include <iostream>
#include <regex>

std::vector<XInputDevice> XInputHelper::parse_xinput_list() {
	std::vector<XInputDevice> devices;
	std::string device_ids = Utils::get_cmd_output("xinput list --id-only");
	std::smatch match;

	std::istringstream iss(device_ids);
	std::string line;
	while (std::getline(iss, line)) {
		if (std::regex_search(line, match, XInputHelper::ID_PATTERN_REGEX)) {
			try {
				int device_id = std::stoi(match[1]);
				devices.emplace_back(device_id); // Is constructed automatically
			} catch (const std::exception& e) {
				std::cerr << "Invalid device ID: " << line << " - " << e.what() << std::endl;
			}
		}
	}

	return devices;
}

std::vector<XInputDevice::Prop> XInputHelper::get_props(const int device_id) {
	std::vector<XInputDevice::Prop> props;

	std::string props_cmd = "xinput list-props " + std::to_string(device_id);
	std::string raw_props = Utils::get_cmd_output(props_cmd);

	std::smatch match;
	std::istringstream stream(raw_props);
	std::string current_line;

	while (std::getline(stream, current_line)) {
		if (std::regex_search(current_line, match, XInputHelper::PROP_PATTERN_REGEX)) {
	 		props.emplace_back(XInputDevice::Prop{
	 			.id = std::stoi(match[2]),
	 			.name = Utils::str_trim_space(match[1]),
	 			.val = Utils::str_trim_space(match[3])
	 		});
		}
	}

	return props;
}

std::string XInputHelper::get_info(const int device_id) {
	std::string info_cmd = "xinput list " + std::to_string(device_id);
	std::string info = Utils::get_cmd_output(info_cmd);
	return info;
}

void XInputHelper::set_prop(const int device_id, const int prop_id, const std::string &value) {
	std::string device_id_str = std::to_string(device_id);
	std::string prop_id_str = std::to_string(prop_id);
	std::string cmd = "xinput set-prop " + device_id_str + " " + prop_id_str + " " + value;

	std::cout << "Changing property ID " << prop_id
						<< " of device " << device_id << " to " << value << "\n";

	std::string resp = Utils::get_cmd_output(cmd);
	if (!resp.empty()) {
		Utils::show_popup(resp);
	}
}

void XInputHelper::set_float(const int device_id) {
	std::string device_id_str = std::to_string(device_id);
	std::string float_cmd = "xinput float " + device_id_str;

	std::cout << "Floating device " << device_id << "\n";
	
	std::string resp = Utils::get_cmd_output(float_cmd);
	if (!resp.empty()) {
		Utils::show_popup(resp);
	}
}

void XInputHelper::set_master(const int device_id, const int master_id) {
	std::string device_id_str = std::to_string(device_id);
	std::string master_id_str = std::to_string(master_id);
	std::string reattach_cmd = "xinput reattach " + device_id_str + " " + master_id_str;

	std::cout << "Attaching device " << device_id
						<< " to master " << master_id << "\n";

	std::string resp = Utils::get_cmd_output(reattach_cmd);
	if (!resp.empty()) {
		Utils::show_popup(resp);
	}
}
