#include <UI/Button.hpp>


Button::Button(sf::Vector2f _pos, sf::Vector2f _size, sf::Color btn_color, sf::Color fn_color, int fn_sz, bool c, std::string val) {
	pos = _pos, size = _size;
	text = val;
	centered = c;
	button_color = btn_color;
	font_color = fn_color;
	font_size = fn_sz;
}

void Button::set_button_color(sf::Color color) { button_color = color; }
void Button::set_font_color(sf::Color color) { font_color = color; }
void Button::set_font_size(int size) { font_size = size; }

sf::Color Button::get_button_color() { return button_color;}
sf::Color Button::get_font_color() { return font_color; }
int Button::get_font_size() { return font_size; }
sf::Vector2f Button::get_button_pos() { return pos; }
sf::Vector2f Button::get_button_size() {return size;}


bool Button::is_centered() {
	return centered;
}
void Button::set_centering(bool check) {
	centered = check;
}

std::string Button::get_string() {
	return text;
}


bool Button::check_hovering(sf::Vector2f mouse_pos) {
	sf::Vector2f s = pos, e = pos + size;
	if (centered) {
		s -= size * 0.5f;
		e -= size * 0.5f;
	}
	return (mouse_pos.x >= s.x && mouse_pos.y >= s.y && mouse_pos.x <= e.x && mouse_pos.y <= e.y);
}