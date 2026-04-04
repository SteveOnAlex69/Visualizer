#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum ButtonType {
	TEXT = 0, 
	BUTTON = 1,
	TEXTBOX = 2
};

enum Alignment {
	TOP_LEFT = 0,
	TOP_CENTER = 1,
	TOP_RIGHT = 2,
	MIDDLE_LEFT = 3,
	MIDDLE_CENTER = 4,
	MIDDLE_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_CENTER = 7,
	BOTTOM_RIGHT = 8
};

class Button {
public:
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color btn_color, sf::Color fn_color, int fn_sz, Alignment align = TOP_LEFT, std::string val = "", ButtonType type = TEXT);
	void set_button_color(sf::Color color);
	void set_font_color(sf::Color color);
	void set_font_size(int size);
	
	sf::Color get_button_color();
	sf::Color get_font_color();
	int get_font_size();
	sf::Vector2f get_button_pos();
	sf::Vector2f get_button_size();
	std::string get_string();
	void set_string(std::string s);

	ButtonType get_type();

	bool check_hovering(sf::Vector2f mouse_pos);
	Alignment get_alignment_type();
	void set_alignment(Alignment align);
private:
	sf::Vector2f pos, size;
	sf::Color button_color, font_color;
	sf::Font font;
	int font_size;
	std::string text;
	Alignment alignment;
	ButtonType type;
};

#endif