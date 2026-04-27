#ifndef APPSETTING_HPP
#define APPSETTING_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


const int BACKGROUND_CYCLE = 5;
const int SPEED_CYCLE = 4;
const int BACKGROUND_SPEED_CYCLE = 5;
const int INFO_DISPLAY_CYCLE = 2;
const int PSEUDOCODE_DISPLAY_CYCLE = 2;

const std::string BACKGROUND_NAMES[] = {
	"Starry Sky",
	"Triangles Tuples",
	"Gravity Grid",
	"Squinty Swirl",
	"Empty"
};

const float SPEED_MODIFIER[] = {
	0.75, 1.0, 1.25, 1.5
};
const float BACKGROUND_SPEED[] = {
	0, 0.5, 1, 1.5, 2
};


const std::string SPEED_MODIFIER_NAMES[] = {
	"0.75x", "1x", "1.25x", "1.5x"
};
const std::string BACKGROUND_SPEED_NAMES[] = {
	"0x", "0.5x", "1x", "1.5x", "2x"
};
const std::string INFO_DISPLAY_NAMES[] = {
	"No", "Yes"
};
const std::string PSEUDOCODE_DISPLAY_NAMES[] = {
	"No", "Yes"
};

class AppSetting {
public:
	AppSetting();
	void set_background(int bg);
	int get_background();
	void set_speed(int s);
	int get_speed();
	void set_bg_speed(int s);
	int get_bg_speed();
	void set_info_display(int s);
	int get_info_display();
	void set_pseudocode_display(int s);
	int get_pseudocode_display();

	void next_background();
	void next_speed();
	void next_bg_speed();
	void next_info_display();
	void next_pseudocode_display();
private: 
	int background_number;
	int speed_number;
	int background_speed;
	int info_display;
	int pseudocode_display;
};

#endif