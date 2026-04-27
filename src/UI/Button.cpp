#include <UI/Button.hpp>
#include <Helper.hpp>


Button::Button() {
	pos = size = sf::Vector2f(0, 0);
	bg_color = font_color = accent_color = sf::Color(0, 0, 0);
	font_size = 0;
	text = button_name = "";
	alignment = relative_pos = TOP_LEFT;
	content = CENTER_CENTER;
	type = TEXT;
	focused = false;

	tex = nullptr;

	last_update = -1;
	hovering = 0;

	show = true;

	line_width = 1e9;
	border_width = 5;

	trans = FADE;
	transition_strength = 5;
}


Button::~Button() {
	delete tex;
	tex = nullptr;
}
Button::Button(std::string path) {
	tex = new sf::Texture(path.c_str());

	pos = size = sf::Vector2f(0, 0);
	bg_color = font_color = accent_color = sf::Color(0, 0, 0);
	font_size = 0;
	text = button_name = "";
	alignment = relative_pos = TOP_LEFT;
	content = CENTER_CENTER;
	type = TEXT;
	focused = false;

	show = true;

	trans = FADE;
	transition_strength = 5;


	line_width = 1e9;
}


void Button::set_bg_color(sf::Color color) { bg_color = color; }
void Button::set_font_color(sf::Color color) { font_color = color; }
void Button::set_font_size(int size) { font_size = size; }
void Button::set_font_accent_color(sf::Color color) { accent_color = color; }
void Button::set_justify_content(Alignment justify) { content = justify; }

void Button::set_string(std::string s) { text = s; }
void Button::set_name(std::string s) { button_name = s; }
void Button::set_alignment(Alignment align_type) { alignment = align_type; }
void Button::set_relative_pos(Alignment align_type) { relative_pos = align_type; }
void Button::set_button_size(sf::Vector2f sz) { size = sz; }
void Button::set_button_pos(sf::Vector2f p) { pos = p; }
void Button::set_button_type(ButtonType t) { type = t; }


sf::Color Button::get_bg_color() { return bg_color; }
sf::Color Button::get_font_color() {return font_color;}
sf::Color Button::get_font_accent_color() { return accent_color; }

std::string Button::get_string() { return text; }
std::string Button::get_name() {return button_name;}
Alignment Button::get_alignment() { return alignment; }
Alignment Button::get_relative_pos() { return relative_pos; }
Alignment Button::get_justify_content() { return content; }
sf::Vector2f Button::get_button_size() { return size; }
sf::Vector2f Button::get_button_pos() { return pos; }
ButtonType Button::get_button_type() { return type; }
int Button::get_font_size() { return font_size; }


bool Button::check_hovering(sf::Vector2f mouse_pos) {
	sf::Vector2f s = pos, e = pos + size;

	int val = (int)alignment;
	int x = val % 3, y = val / 3;
	s -= sf::Vector2f(size.x * (0.5f * x), size.y * (0.5f * y));
	e -= sf::Vector2f(size.x * (0.5f * x), size.y * (0.5f * y));

	val = (int)relative_pos;
	x = val % 3, y = val / 3;
	s += sf::Vector2f(screen_center.x * (1.f * x), screen_center.y * (1.f * y));
	e += sf::Vector2f(screen_center.x * (1.f * x), screen_center.y * (1.f * y));
	return (mouse_pos.x >= s.x && mouse_pos.y >= s.y && mouse_pos.x <= e.x && mouse_pos.y <= e.y);
}

void Button::set_focused(bool f) {focused = f;}
bool Button::get_focused() { return focused;  }


bool Button::have_texture() { return (tex != nullptr); }
sf::Texture* Button::get_texture() { return tex; }


float Button::send_update_state(float time, bool h) { 
	if (hovering != h) {
		last_update = time;
		hovering = h;
	}
	return time - last_update;
}


void Button::set_visibility(bool visibility) {
	show = visibility;
}
bool Button::get_visibility() {
	return show;
}


int Button::get_line_width() { return line_width; }
void Button::set_line_width(int width) { line_width = width; }


int Button::get_border_width() { return border_width; }
void Button::set_border_width(int width) { border_width= width; }


TransitionType Button::get_transition_type() {
	return trans;
}
void Button::set_transition_type(TransitionType t) {
	trans = t;
}


void Button::set_transition_strength(float s) {
	transition_strength = s;
}
float Button::get_transition_strength() {
	return transition_strength;
}