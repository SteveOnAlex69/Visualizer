#include <UI/UIUnit.hpp>


UIUnit::UIUnit() {}
UIUnit::UIUnit(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;
}

void UIUnit::add_element(Button* button) {
	buttons.push_back(button);
}
void UIUnit::draw(sf::Vector2f mouse_pos) {
	for (auto i : buttons) draw_button(i, mouse_pos);
}

void UIUnit::draw_button(Button* button, sf::Vector2f mouse_pos) {
	sf::Vector2f pos = button->get_button_pos();
	sf::Vector2f size = button->get_button_size();
	sf::Color btn_color = button->get_button_color();
	sf::Color fn_color = button->get_font_color();
	if (button->is_centered()) pos -= size * 0.5f;
	if (button->check_hovering(mouse_pos)) {
		std::swap(btn_color, fn_color);
	}
	
	sf::RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setFillColor(btn_color);
	appwindow->draw(rect);

	sf::Text tex(font);
	tex.setString(button -> get_string());
	tex.setPosition(pos + size * 0.5f);
	tex.setCharacterSize(button->get_font_size());
	tex.setFillColor(fn_color);

	sf::FloatRect textRect = tex.getLocalBounds();
	tex.setOrigin(textRect.size * 0.5f + textRect.position);
	appwindow->draw(tex);
}


Button* UIUnit::check_hovering(sf::Vector2f mouse_pos) {
	for (auto i : buttons) if (i->check_hovering(mouse_pos))
		return i;
	return nullptr;
}