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

	void draw(sf::Vector2f mouse_position, int type, float delta = 0);
private:
	sf::RenderWindow* appwindow;
	sf::Font font;
	float total_time;

	std::vector<sf::Vector3f> points;

	void draw0(sf::Vector2f mouse_position, float delta = 0);	
	void draw1(sf::Vector2f mouse_position, float delta = 0);
	void draw2(sf::Vector2f mouse_position, float delta = 0);
	void draw3(sf::Vector2f mouse_position, float delta = 0);
	void draw4(sf::Vector2f mouse_position, float delta = 0);


};


#endif