#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Menu { // drawing the menu
public:
	Menu(sf::RenderWindow* window, sf::Font font);
private:
	sf::RenderWindow* appwindow;
	sf::Font default_font;
};

#endif