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

class Button {
public:
	Button(sf::Vector2f pos, sf::Vector2f size, sf::Color btn_color, sf::Color fn_color, int fn_sz, bool c = false, std::string val = "", ButtonType type = TEXT);
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
	bool is_centered();
	void set_centering(bool check);
private:
	sf::Vector2f pos, size;
	sf::Color button_color, font_color;
	sf::Font font;
	int font_size;
	std::string text;
	bool centered;
	ButtonType type;
};

#endif