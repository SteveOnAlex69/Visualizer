#ifndef UIUNIT_HPP
#define UIUNIT_HPP

#include <SFML/Graphics.hpp>
#include <UI/Button.hpp>
#include <Helper.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

class UIUnit {
public:
	UIUnit();
	UIUnit(sf::RenderWindow* window, sf::Font f);

	void add_element(Button *button);
	void draw(sf::Vector2f mouse_pos = sf::Vector2f(-1, -1));
	Button* check_hovering(sf::Vector2f mouse_pos);
private:
	sf::RenderWindow* appwindow;
	sf::Font font;
	std::vector<Button*> buttons;

	void draw_button(Button* button, sf::Vector2f mouse_pos);
};


#endif