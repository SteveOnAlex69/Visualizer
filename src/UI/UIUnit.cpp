#include <UI/UIUnit.hpp>
#include <UI/Button.hpp>
#include <fstream>


UIUnit::UIUnit() {}
UIUnit::UIUnit(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;
}

void UIUnit::add_element(Button* button) {
	buttons.push_back(button);
}

void UIUnit::erase_element(Button* button) {
	for (int i = 0; i < (int)buttons.size(); ++i) if (buttons[i] == button) {
		buttons.erase(buttons.begin() + i);
		delete button;
		return;
	}
}

Button* UIUnit::find_button(std::string name) {
	for (auto i : buttons) if (i->get_name() == name)
		return i;
	return nullptr;
}

void UIUnit::draw(sf::Vector2f mouse_pos) {
	for (auto i : buttons) draw_button(i, mouse_pos);
}

void UIUnit::draw_button(Button* button, sf::Vector2f mouse_pos) {
	sf::Vector2f pos = button->get_button_pos();
	sf::Vector2f size = button->get_button_size();
	sf::Color btn_color = button->get_font_color();


	int rel_pos = (int)button->get_relative_pos();
	pos += sf::Vector2f(screen_center.x * (rel_pos % 3), screen_center.y * (rel_pos / 3));

	int alignment = (int)button->get_alignment();
	pos -= sf::Vector2f(size.x * 0.5f * (alignment % 3), size.y * 0.5f * (alignment / 3));

	if (button->check_hovering(mouse_pos)) 
		btn_color = button->get_font_accent_color();
	if (button->get_button_type() == TEXTBOX && button->get_focused())
		btn_color = button->get_font_accent_color();
	
	sf::RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);

	rect.setFillColor(button -> get_bg_color());

	rect.setOutlineThickness(5);
	rect.setOutlineColor(btn_color);
	appwindow->draw(rect);

	sf::Text tex(font);
	tex.setString(button -> get_string());
	tex.setPosition(pos + size * 0.5f);
	tex.setCharacterSize(button->get_font_size());
	tex.setFillColor(btn_color);

	sf::FloatRect textRect = tex.getLocalBounds();
	tex.setOrigin(textRect.size * 0.5f + textRect.position);
	appwindow->draw(tex);
}


Button* UIUnit::check_hovering(sf::Vector2f mouse_pos) {
	for (auto i : buttons) if (i->check_hovering(mouse_pos))
		return i;
	return nullptr;
}

void UIUnit::click(sf::Vector2f mouse_pos) {
	for (auto i : buttons) if (i -> get_button_type() == TEXTBOX) {
		i->set_focused(i->check_hovering(mouse_pos));
	}
}