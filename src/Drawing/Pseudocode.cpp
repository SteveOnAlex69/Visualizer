#include <Drawing/Pseudocode.hpp>

Pseudocode::Pseudocode() {
	file_path = "";
	content = "";
}

Pseudocode::Pseudocode(int ds_name, int command_name) {
	file_path = PSEUDOCODE_PATH + "DS" + std::string(1, ds_name + '0') + "/command" + 
		std::string(1, '0' + command_name) + ".cpp";

	std::cout << file_path << std::endl;
	std::ifstream input(file_path.c_str());
	std::getline(input, content, '\0');

	std::cout << content << std::endl;
}

std::string Pseudocode::get_content() {
	return content;
}