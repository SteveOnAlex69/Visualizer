#include <Helper.hpp>
#include <GameLogic.hpp>
#include <MediaPlayer.hpp>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/Trie.hpp>
#include <DataStructures/BST.hpp>
#include <DataStructures/AVL.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

#include <Drawing/DrawingUnit.hpp>
#include <UI/MenuManager.hpp>
#include <UI/UIUnit.hpp>

#define ll long long
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

Trie tri;
LinkedList li;
sf::Font font;
DrawingUnit drawing_unit;
MenuManager menu_manager;

UIUnit menu;

void setup_menus() {
	menu.add_element(
		new Button(screen_center + sf::Vector2f(0, -300), sf::Vector2f(0, 0),
			BACKGROUND, sf::Color::White, 100, true, 
			"DATA VISUALIZER")
	);

	menu.add_element(
		new Button(screen_center + sf::Vector2f(0, -100), sf::Vector2f(300, 80),
			FORESKIN, sf::Color::White, 36, true,
			"START")
	);
	menu.add_element(
		new Button(screen_center + sf::Vector2f(0, 0), sf::Vector2f(300, 80),
			FORESKIN, sf::Color::White, 36, true,
			"SETTINGS")
	);
	menu.add_element(
		new Button(screen_center + sf::Vector2f(0, 100), sf::Vector2f(300, 80),
			FORESKIN, sf::Color::White, 36, true,
			"ABOUT")
	);
	menu.add_element(
		new Button(screen_center + sf::Vector2f(0, 200), sf::Vector2f(300, 80),
			FORESKIN, sf::Color::White, 36, true,
			"QUIT")
	);

	menu.add_element(
		new Button(sf::Vector2f(screen_center.x, screen_center.y * 2 - 10), sf::Vector2f(0, 0),
			BACKGROUND, sf::Color::Black, 20, true,
			"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock")
	);
}

void appStart(sf::RenderWindow& appwindow) {
	// load font
	font.openFromFile(FONT_PATH.c_str());

	tri = Trie();
	li = LinkedList();

	drawing_unit = DrawingUnit(&appwindow, font);
	menu = UIUnit(&appwindow, font);
	
	setup_menus();
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
bool just_clicked = false;
Point2 pre_mouse_pos;
void handle_mouse(sf::RenderWindow& appwindow, float delta) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (is_clicking == false) just_clicked = true;
		else just_clicked = false;
		is_clicking = true;
	}
	else {
		just_clicked = false;
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

void handle_menu(sf::RenderWindow& appwindow) {
	menu.draw(get_mouse_pos(appwindow));

	Button* cur = menu.check_hovering(get_mouse_pos(appwindow));
	if (just_clicked) {
		if (cur) {
			if (cur->get_string() == "START") {
				menu_manager.set_current_state(VISUALIZING);
			}
			else if (cur->get_string() == "ABOUT") {
				menu_manager.set_current_state(ABOUT);
			}
			else if (cur->get_string() == "SETTINGS") {
				menu_manager.set_current_state(SETTINGS);
			}
			else if (cur->get_string() == "QUIT") {
				appwindow.close();
			}
		}
	}
}

void appLoop(sf::RenderWindow& appwindow, float delta) { // receive delta in s
	int cur = pollEvent(appwindow);
	if (cur == 0) return;
	appwindow.clear(BACKGROUND);
	handle_mouse(appwindow, delta);

	if (menu_manager.get_current_state() == MENU) {
		handle_menu(appwindow);
	}

	appwindow.display();
}