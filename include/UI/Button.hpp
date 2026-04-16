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
	CENTER_LEFT = 3,
	CENTER_CENTER = 4,
	CENTER_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_CENTER = 7,
	BOTTOM_RIGHT = 8
};

class Button {
public:
	Button();
	~Button();
	Button(std::string path);
	void set_bg_color(sf::Color color);
	void set_string(std::string s);
	void set_alignment(Alignment align_type);
	void set_button_size(sf::Vector2f size);
	void set_button_pos(sf::Vector2f pos);
	void set_justify_content(Alignment justify);
	void set_relative_pos(Alignment align_type);
	void set_name(std::string s);
	void set_button_type(ButtonType type);

	void set_font_color(sf::Color color);
	void set_font_accent_color(sf::Color color);
	void set_font_size(int size);
	
	sf::Color get_bg_color();
	sf::Color get_font_color();
	sf::Color get_font_accent_color();

	std::string get_string();
	std::string get_name();
	Alignment get_alignment();
	Alignment get_relative_pos();
	Alignment get_justify_content();
	sf::Vector2f get_button_size();
	sf::Vector2f get_button_pos();
	ButtonType get_button_type();
	int get_font_size();

	void set_focused(bool f);
	bool get_focused();

	bool check_hovering(sf::Vector2f mouse_pos);

	bool have_texture();
	sf::Texture *get_texture();

	float send_update_state(float time, bool hovering);

	void set_visibility(bool visibility);
	bool get_visibility();

	int get_line_width();
	void set_line_width(int width);
private:
	sf::Vector2f pos, size;
	sf::Color bg_color, font_color, accent_color;
	int font_size;
	std::string text, button_name;
	Alignment alignment, relative_pos, content;
	ButtonType type;
	bool focused;

	sf::Texture *tex;

	float last_update;
	bool hovering;

	bool show;

	int line_width;
};

#endif