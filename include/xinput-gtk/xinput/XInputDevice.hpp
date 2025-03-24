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

#ifndef XINPUT_DEVICE_HPP
#define XINPUT_DEVICE_HPP

#include <string>
#include <vector>

class XInputDevice {
public:
	XInputDevice() {};
	XInputDevice(const int device_id);
	~XInputDevice() = default;

	struct Prop {
		int id;
		std::string name;
		std::string val;
	};

	// Getter functions
	std::string get_name() const { return m_name; }
	int get_id() const { return m_id; }
	std::string get_type() const { return m_type; }
	bool is_master() const { return m_is_master; }
	bool is_float() const { return m_type == "floating"; }

	// Helper functions
	std::vector<Prop> get_props();
	std::string get_info();

private:
	std::string m_name;
	std::string m_type;
	int m_id{-1};
	bool m_is_master{false}; // True if the device is a master device
};

#endif // XINPUT_DEVICE_HPP
