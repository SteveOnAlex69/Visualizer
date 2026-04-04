#include <UI/Button.hpp>


Button::Button(sf::Vector2f _pos, sf::Vector2f _size, sf::Color btn_color, sf::Color fn_color, 
	int fn_sz, Alignment align_type, std::string val, ButtonType t) {
	pos = _pos, size = _size;
	text = val;
	alignment = align_type;
	button_color = btn_color;
	font_color = fn_color;
	font_size = fn_sz;
	type = t;
}

ButtonType Button::get_type() { return type; }

void Button::set_button_color(sf::Color color) { button_color = color; }
void Button::set_font_color(sf::Color color) { font_color = color; }
void Button::set_font_size(int size) { font_size = size; }

sf::Color Button::get_button_color() { return button_color;}
sf::Color Button::get_font_color() { return font_color; }
int Button::get_font_size() { return font_size; }
sf::Vector2f Button::get_button_pos() { return pos; }
sf::Vector2f Button::get_button_size() {return size;}


Alignment Button::get_alignment_type() {
	return alignment;
}
void Button::set_alignment(Alignment align_type) {
	alignment = align_type;
}

std::string Button::get_string() {
	return text;
}

void Button::set_string(std::string s) {
	text = s;
}


bool Button::check_hovering(sf::Vector2f mouse_pos) {
	sf::Vector2f s = pos, e = pos + size;

	int val = (int)alignment;
	int x = val % 3, y = val / 3;
	s -= sf::Vector2f(size.x * (0.5f * x), size.y * (0.5f * y));
	e -= sf::Vector2f(size.x * (0.5f * x), size.y * (0.5f * y));
	return (mouse_pos.x >= s.x && mouse_pos.y >= s.y && mouse_pos.x <= e.x && mouse_pos.y <= e.y);
}