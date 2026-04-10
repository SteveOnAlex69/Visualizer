#include <Input/InputHandler.hpp>
#include <iostream>

InputState transform(InputState x, int flag) {
	if (flag) {
		if (x == RELEASE) return CLICK;
		return HOLD;
	}
	return RELEASE;
}

InputHandler::InputHandler(sf::RenderWindow *window) {
	mouse = RELEASE;
	std::fill(key_press, key_press + MAX_INPUT_KEY, RELEASE);
	appwindow = window;
}
InputState InputHandler::get_mouse_state() {
	return mouse;
}

sf::Vector2f InputHandler::get_mouse_pos() {
	auto tmp = sf::Mouse::getPosition(*appwindow);
	return sf::Vector2f(tmp.x, tmp.y);
}


void InputHandler::update_mouse(float delta) {
	mouse = transform(mouse, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}


void InputHandler::update_keyboard(float delta) {
	for (int j = 0; j <= 9; ++j) {
		sf::Keyboard::Key num_key = (sf::Keyboard::Key)((int)sf::Keyboard::Key::Num0 + j);
		key_press[j] = transform(key_press[j], sf::Keyboard::isKeyPressed(num_key));
	}
	for (int j = 0; j < 26; ++j) {
		sf::Keyboard::Key num_key = (sf::Keyboard::Key)((int)sf::Keyboard::Key::A + j);
		key_press[j + 10] = transform(key_press[j + 10], sf::Keyboard::isKeyPressed(num_key));
	}
	key_press[(int)ENTER] = 
		transform(key_press[(int)ENTER], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter));
	key_press[(int)ESC] =
		transform(key_press[(int)ESC], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape));
	key_press[(int)BACKSPACE] =
		transform(key_press[(int)BACKSPACE], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace));
	key_press[(int)LEFT_ARROW] =
		transform(key_press[(int)LEFT_ARROW], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left));
	key_press[(int)RIGHT_ARROW] =
		transform(key_press[(int)RIGHT_ARROW], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right));
	key_press[(int)TABS] =
		transform(key_press[(int)TABS], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab));
	key_press[(int)LSHIFT] =
		transform(key_press[(int)LSHIFT], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift));
	key_press[(int)RSHIFT] =
		transform(key_press[(int)RSHIFT], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift));
	key_press[(int)SPACE] =
		transform(key_press[(int)SPACE], sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
}

InputState InputHandler::get_keyboard_key(InputKey key) {
	return key_press[(int)key];
}