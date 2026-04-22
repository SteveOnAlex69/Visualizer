#ifndef PSEUDOCODE_HPP
#define PSEUDOCODE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <Helper.hpp>
#include <fstream>
#include <iostream>

class Pseudocode{
public:
	Pseudocode();
	Pseudocode(int DS_name, int command_name, int stage = -1);

	std::string get_content();
	std::vector<int> get_highlighted();

	int get_DS_name();
	int get_command_name();

	void get_stage(int step);
private:
	std::string file_path;
	std::string content;
	std::vector<int> highlighted_line;
	int DS_name, command_name;
	int prestage, stage;
};

#endif