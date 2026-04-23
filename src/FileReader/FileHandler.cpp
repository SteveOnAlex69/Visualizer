#include <FileReader/FileHandler.hpp>


std::string loadTextFile() {
	auto selection = pfd::open_file("Select a text file", ".",
		{ "Text Files (*.txt)", "*.txt" }).result();
	if (!selection.empty()) {
		std::string filePath = selection[0];
		std::ifstream file(filePath);
		std::cout << "Opening file: " << filePath << std::endl;
		if (file.is_open()) {
			std::string line;
			std::getline(file, line, '\0');
			file.close();
			return line;
		}
	}
	return "";
}