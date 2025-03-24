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
#include <xinput-gtk/Utils.hpp>
#include <regex>

XInputDevice::XInputDevice(const int device_id) : m_id(device_id) {
	// Set device name
	std::string name_cmd = "xinput list --name-only " + std::to_string(device_id);
	m_name = Utils::str_trim_space(Utils::get_cmd_output(name_cmd));

	// Get device type
	// `Device Name    id=X    [master/slave  type (Y)]`
	// We're capturing `[master/slave  type (Y)]`
	std::regex details_pattern(R"(\[(\w+)\s+(\w+)\s+\((\d+)\)\])");
	std::smatch match;

	std::string details_str = "xinput list --short " + std::to_string(m_id);
	std::string device_details = Utils::get_cmd_output(details_str);

	if (std::regex_search(device_details, match, details_pattern)) {
	 	m_is_master = (match[1] == "master");
	 	m_type = match[2];
	} else {
	 	m_type = "floating";
	}
}

std::vector<XInputDevice::Prop> XInputDevice::get_props() {
	std::vector<XInputDevice::Prop> props_vector;

	std::string props_cmd = "xinput list-props " + std::to_string(m_id);
	std::string raw_props = Utils::get_cmd_output(props_cmd);

	std::regex prop_pattern(R"(^(.+) \((\d+)\):(.+)$)");
	std::smatch match;
	std::istringstream stream(raw_props);
	std::string current_line;

	while (std::getline(stream, current_line)) {
		if (std::regex_search(current_line, match, prop_pattern)) {
	 		props_vector.emplace_back(Prop{
	 			.id = std::stoi(match[2]),
	 			.name = Utils::str_trim_space(match[1]),
	 			.val = Utils::str_trim_space(match[3])
	 		});
		}
	}

	return props_vector;
}

std::string XInputDevice::get_info() {
	std::string info_cmd = "xinput list " + std::to_string(m_id);
	std::string info = Utils::get_cmd_output(info_cmd);
	return info;
}

