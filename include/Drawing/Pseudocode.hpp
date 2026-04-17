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
	Pseudocode(int DS_name, int command_name);

	std::string get_content();
private:
	std::string file_path;
	std::string content;
};

#endif