#include <Helper.hpp>
#include <GameLogic.hpp>
#include <MediaPlayer.hpp>
#include <Node.hpp>
#include <Graph.hpp>
#include <LinkedList.hpp>
#include <Hashmap.hpp>
#include <Trie.hpp>
#include <BST.hpp>
#include <AVL.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

#include <DrawingUnit.hpp>

#define ll long long
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

Trie tri;
sf::Font font;
DrawingUnit drawing_unit;

void appStart(sf::RenderWindow& appwindow) {
	// load font
	font.openFromFile(FONT_PATH.c_str());

	tri = Trie();

	drawing_unit = DrawingUnit(&appwindow, font);
}

bool pressing = false;
void handle_keypress(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
	}
	else {
	}
}


Point2 get_mouse_pos(sf::RenderWindow& appwindow) {
	auto tmp = sf::Mouse::getPosition(appwindow);
	return Point2(tmp.x, tmp.y);
}

bool is_clicking = false;
Point2 pre_mouse_pos;
void handle_mouse(sf::RenderWindow& appwindow, float delta) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		is_clicking = true;
	}
	else {
		is_clicking = false;
	}
}

int pollEvent(sf::RenderWindow& appwindow) { // if window is closed, return 0
	int return_val = 1;
	while (const std::optional event = appwindow.pollEvent()) {
		if (event->is <sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			std::cerr << "Closing the window" << std::endl;
			appwindow.close();
			return 0;
		}
	}

	return return_val;
}

float clockcock = 0;
std::set<int> S;

void appLoop(sf::RenderWindow& appwindow, float delta) { // receive delta in s
	int cur = pollEvent(appwindow);
	if (cur == 0) return;
	appwindow.clear(BACKGROUND);
	handle_mouse(appwindow, delta);

	
	clockcock += delta;
	if (clockcock >= 1) {
		clockcock = 0;
		std::string ahh(rngesus(1, 5), 'a');
		for (char& c : ahh)
			c += rngesus(0, 25);

		tri.add(ahh);
		std::cout << ahh << "\n";
	}

	drawing_unit.draw_trie(tri, sf::Vector2f(screen_center.x, 200));

	appwindow.display();
}