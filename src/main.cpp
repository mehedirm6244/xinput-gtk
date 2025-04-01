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

#include <xinput-gtk/gui/Window.hpp>
#include <xinput-gtk/Utils.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "xinput-gtk - A GTK3 frontend for Xorg XInput\n";

	// Abort program if `xinput` is not installed
	if (!Utils::check_installed("xinput")) {
		std::cerr << "Error: 'xinput' is not installed! Aborting..." << std::endl;
		return EXIT_FAILURE;
	}
	
	// Print 'xinput' version upon starting
	std::cout << Utils::get_cmd_output("xinput --version");

	const std::string APP_ID = "org.xinput-gtk.app";
	auto app = Gtk::Application::create(argc, argv, APP_ID);
	auto window = std::make_unique<Window>();

	int status = app->run(*window);
	if (status) {
		std::cerr << "Application exited with error code " << status << std::endl;
	}
	return status;
}