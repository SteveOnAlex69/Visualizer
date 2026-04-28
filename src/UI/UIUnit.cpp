#include <UI/UIUnit.hpp>
#include <UI/Button.hpp>
#include <fstream>


UIUnit::UIUnit() { current_time = 0; }
UIUnit::UIUnit(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;
	kick_start();
}

void UIUnit::kick_start() {
	current_time = 0;
	last_frame_time = 0;
}

void UIUnit::update_timer(float delta) {
	current_time += delta;
	last_frame_time = delta;
}

float UIUnit::get_last_frame() { return last_frame_time; }

void UIUnit::add_element(Button* button) {
	buttons.push_back(button);
}

bool UIUnit::erase_element(Button* button) {
	for (int i = 0; i < (int)buttons.size(); ++i) if (buttons[i] == button) {
		buttons.erase(buttons.begin() + i);
		delete button;
		return true;
	}
	return false;
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
	if (button->get_visibility() == 0) return;
	sf::Vector2f pos = button->get_button_pos();
	sf::Vector2f size = button->get_button_size();
	sf::Color btn_color = button->get_font_color();
	sf::Color font_color = button->get_font_color();
	sf::Color background_color = button->get_bg_color();

	float transition_strength = button->get_transition_strength();
	float transition_state = std::exp(-current_time * transition_strength);

	float opacity = 1;
	sf::Vector2f dumb_pos(0, 0);
	switch (button->get_transition_type()) {
	case FADE:
		opacity -= transition_state;
		break;
	case UP:
		dumb_pos.y += transition_state * screen_center.y * 2;
		break;
	case DOWN:
		dumb_pos.y -= transition_state * screen_center.y * 2;
		break;
	case LEFT:
		dumb_pos.x -= transition_state * screen_center.x * 2;
		break;
	case RIGHT:
		dumb_pos.x += transition_state * screen_center.x * 2;
		break;
	}


	btn_color.a *= opacity;
	font_color.a *= opacity;
	background_color.a *= opacity;

	float font_size = button->get_font_size();
	if (button->get_button_type() == BUTTON) {
		float hover_time = button->send_update_state(current_time, button->check_hovering(mouse_pos));
		if (button->check_hovering(mouse_pos)) {
			size += size * 0.05f * sigmoid(hover_time * 10);
			font_size += font_size * 0.1f * sigmoid(hover_time * 10);
		}
		else {
			size += size * 0.05f * (1 - sigmoid(hover_time * 10));
			font_size += font_size * 0.1f * (1 - sigmoid(hover_time * 10));
		}
	}


	if (button->check_hovering(mouse_pos)) {
		btn_color = button->get_font_accent_color();
		font_color = btn_color;
	}
	if (button->get_focused()) {
		if (button->get_button_type() == BUTTON) {
			btn_color = button->get_font_accent_color();
			font_color = background_color;
			background_color = btn_color;
		}
		else {
			btn_color = button->get_font_accent_color();
			font_color = btn_color;
		}
	}
	int rel_pos = (int)button->get_relative_pos();
	pos += sf::Vector2f(screen_center.x * (rel_pos % 3), screen_center.y * (rel_pos / 3));

	int alignment = (int)button->get_alignment();
	pos -= sf::Vector2f(size.x * 0.5f * (alignment % 3), size.y * 0.5f * (alignment / 3));

	pos += dumb_pos;



	if (button->have_texture()) {
		sf::Sprite sp(*(button->get_texture()));

		sf::FloatRect spRect = sp.getLocalBounds();
		float scaleX = (float)size.x / spRect.size.x;
		float scaleY = (float)size.y / spRect.size.y;
		sp.setScale(sf::Vector2f(scaleX, scaleY));

		spRect = sp.getLocalBounds();
		sp.setOrigin(spRect.size * 0.5f + spRect.position);
		sp.setPosition(pos + size * 0.5f);
		sp.setColor(btn_color);
		appwindow->draw(sp);
	}
	else {
		if (button->get_border_width()) {
			sf::RectangleShape rect;
			rect.setPosition(pos);
			rect.setSize(size);

			rect.setFillColor(background_color);

			rect.setOutlineThickness(button->get_border_width());
			rect.setOutlineColor(btn_color);
			appwindow->draw(rect);
		}
		Alignment justify_content = button->get_justify_content();
		int x = (int)justify_content % 3, y = (int)justify_content / 3;
		sf::Text tex(font);
		std::vector<std::string> brah = split(" " + button->get_string());
		int cnt = 0;
		std::string ans = "";
		for (auto i : brah) {
			if (cnt == 0 || i == "\n") {
				ans += i;
				if (i == "\n") cnt = 0;
				else cnt = i.size();
			}
			else if (cnt + 1 + i.size() > button -> get_line_width()) {
				ans += "\n" + i;
				cnt = i.size();
			}
			else {
				ans += " " + i;
				cnt += 1 + i.size();
			}
		}
		tex.setString(ans);
		tex.setPosition(pos + size * 0.5f +
			sf::Vector2f( (size.x * 0.5f - 10) * (x-1), (size.y * 0.5f - 10) * (y-1)));
		tex.setCharacterSize(font_size);
		tex.setFillColor(font_color);
		sf::FloatRect textRect = tex.getLocalBounds();
		tex.setOrigin(sf::Vector2f(textRect.size.x * 0.5f * x, textRect.size.y * 0.5f * y)
			+ textRect.position);
		appwindow->draw(tex);

		if (button->get_button_type() == TEXTBOX && button->get_focused()) {
			sf::Text tuff(font);
			tuff.setString("|");
			tuff.setCharacterSize(font_size);
			tuff.setFillColor(button->get_font_color());
			int str_sz = tex.getString().getSize();
			sf::Vector2f caretPos = tex.findCharacterPos(str_sz);
			if (str_sz == 0) {
				caretPos = tex.getPosition();
				sf::FloatRect flightreact = tuff.getLocalBounds();
				tuff.setOrigin(sf::Vector2f(flightreact.size.x * 0.5f * x, flightreact.size.y * 0.5f * y)
					+ flightreact.position);
			}
			tuff.setPosition(caretPos);
			
			appwindow->draw(tuff);
		}

	}
	
}


Button* UIUnit::check_hovering(sf::Vector2f mouse_pos) {
	Button* hovering = nullptr;
	for (auto i : buttons) {
		if (i->check_hovering(mouse_pos) && i->get_visibility()) hovering = i;
		i->send_update_state(current_time, i->check_hovering(mouse_pos));
	}
	return hovering;
}

void UIUnit::click(sf::Vector2f mouse_pos) {
	for (auto i : buttons) {
		i->set_focused(i->check_hovering(mouse_pos));
	}
}

Button* UIUnit::get_focused_text_box() {
	for (Button* i : buttons) {
		if (i->get_button_type() == TEXTBOX && i->get_focused())
			return i;
	}
	return nullptr;
}