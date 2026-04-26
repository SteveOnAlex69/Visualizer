#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum InputState {
	RELEASE = 0,
	CLICK = 1,
	HOLD = 2
};

const int MAX_INPUT_KEY = 47;
enum InputKey {
    // number key
    ZERO = 0,ONE = 1,TWO = 2,THREE = 3,FOUR = 4,FIVE = 5,SIX = 6,SEVEN = 7,EIGHT = 8,NINE = 9,
    // alpha key
    KEY_A = 10,KEY_B = 11,KEY_C = 12,KEY_D = 13,KEY_E = 14,KEY_F = 15,KEY_G = 16,
    KEY_H = 17,KEY_I = 18,KEY_J = 19,KEY_K = 20,KEY_L = 21,KEY_M = 22,KEY_N = 23,KEY_O = 24,KEY_P = 25,
    KEY_Q = 26,KEY_R = 27,KEY_S = 28,
    KEY_T = 29,KEY_U = 30,KEY_V = 31,
    KEY_W = 32,KEY_X = 33,
    KEY_Y = 34,KEY_Z = 35,
    // control key
    ENTER = 36,
    ESC = 37,
    BACKSPACE = 38,
    LEFT_ARROW = 39,
    RIGHT_ARROW = 40,
    TABS = 41,
    LSHIFT = 42,
    RSHIFT = 43,
    SPACE = 44,
    LCTRL = 45,
    RCTRL = 46
};

class InputHandler {
public:
	InputHandler(sf::RenderWindow* appwindow = nullptr);
	InputState get_mouse_state();

	sf::Vector2f get_mouse_pos();
	void update_mouse(float delta);
	void update_keyboard(float delta);
    void set_scroll_delta(int delta);
    int get_scroll_delta();
	InputState get_keyboard_key(InputKey key);

    sf::Vector2f get_mouse_delta();
private:
	InputState mouse;
	InputState key_press[MAX_INPUT_KEY];

	sf::RenderWindow* appwindow;
    sf::Vector2f prev_mouse_pos, cur_mouse_pos;

    int scroll_delta;
};

#endif