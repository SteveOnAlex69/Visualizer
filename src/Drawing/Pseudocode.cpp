#include <Drawing/Pseudocode.hpp>
#include <Data/pseudocode_time.hpp>

Pseudocode::Pseudocode() {
	file_path = "";
	content = "";
}

Pseudocode::Pseudocode(int d, int c, int s) {
	DS_name = d;
	command_name = c;
	file_path = ""; content = "";
	file_path = PSEUDOCODE_PATH + "DS" + std::string(1, DS_name + '0') + "/command" +
		std::string(1, '0' + command_name) + ".cpp";

	std::ifstream input(file_path.c_str());
	if (input.is_open())
		std::getline(input, content, '\0');

	prestage = s;
}

std::string Pseudocode::get_content() {return content;}

std::vector<int> Pseudocode::get_highlighted() {return get_highlighted_line(DS_name,
	command_name, stage);}

int Pseudocode::get_DS_name() { return DS_name; }
int Pseudocode::get_command_name() { return command_name; }

void Pseudocode::get_stage(int step) {
	stage = f(prestage, step);
}