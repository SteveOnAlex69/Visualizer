#include <UI/UIUnit.hpp>


UIUnit::UIUnit() {}
UIUnit::UIUnit(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;
}

void UIUnit::add_element(Button* button) {
	buttons.push_back(button);
}

void UIUnit::erase_element(Button* button) {
	for(int i = 0; i < (int) buttons.size(); ++i) 
		if (buttons[i] == button) {
			buttons.erase(buttons.begin() + i);
			break;
		}
	delete button;
}

void UIUnit::draw(sf::Vector2f mouse_pos) {
	for (auto i : buttons) draw_button(i, mouse_pos);
}

void UIUnit::draw_button(Button* button, sf::Vector2f mouse_pos) {
	sf::Vector2f pos = button->get_button_pos();
	sf::Vector2f size = button->get_button_size();

	sf::Color btn_color = FIRST_COLOR;

	int val = (int)button->get_alignment_type();
	pos -= sf::Vector2f(size.x * 0.5f * (val % 3), size.y * 0.5f * (val / 3));

	if (button->check_hovering(mouse_pos)) {
		btn_color = SECOND_COLOR;
	}
	
	sf::RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);

	if (button->get_type() == TEXT)
		rect.setFillColor(sf::Color::Transparent);
	else rect.setFillColor(BACKGROUND);

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