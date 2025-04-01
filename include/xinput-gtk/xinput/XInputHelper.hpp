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

#ifndef XINPUT_HELPER_HPP
#define XINPUT_HELPER_HPP

#include <xinput-gtk/xinput/XInputDevice.hpp>
#include <regex>

namespace XInputHelper {
	const std::regex ID_PATTERN_REGEX(R"(\D*(\d+)\D*)");
	const std::regex PROP_PATTERN_REGEX(R"(^(.+) \((\d+)\):(.+)$)");

	std::vector<XInputDevice> parse_xinput_list();

	std::vector<XInputDevice::Prop> get_props(const int device_id);

	std::string get_info(const int device_id);

	void set_prop(const int device_id, const int prop_id, const std::string &value);

	void set_float(const int device_id);

	void set_master(const int device_id, const int master_id);
} // namespace XInputHelper

#endif // XINPUT_HELPER_HPP
