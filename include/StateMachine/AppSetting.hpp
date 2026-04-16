#ifndef APPSETTING_HPP
#define APPSETTING_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


const int BACKGROUND_CYCLE = 4;
const int SPEED_CYCLE = 4;

const std::string BACKGROUND_NAMES[] = {
	"Starry Sky",
	"Triangles Tuples",
	"Gravity Grid",
	"Squinty Swirl"
};

const float SPEED_MODIFIER[] = {
	0.75, 1.0, 1.25, 1.5
};

const std::string SPEED_MODIFIER_NAMES[] = {
	"0.75x", "1x", "1.25x", "1.5x"
};

class AppSetting {
public:
	AppSetting();
	void set_background(int bg);
	int get_background();

	void set_speed(int s);
	int get_speed();

	void next_background();
	void next_speed();
private: 
	int background_number;
	int speed_number;
};

#endif