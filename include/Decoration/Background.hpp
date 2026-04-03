#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

class BackgroundDrawer {
public:
	BackgroundDrawer();
	BackgroundDrawer(sf::RenderWindow* window, sf::Font f);

	void draw(sf::Vector2f mouse_position);
private:
	sf::RenderWindow* appwindow;
	sf::Font font;

	std::vector<sf::Vector3f> points;

	void draw1(sf::Vector2f mouse_position);	
	void draw2(sf::Vector2f mouse_position);

};


#endif