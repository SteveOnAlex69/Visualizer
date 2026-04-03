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
#include <UI/UIDesign.hpp>

#define ll long long
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

Trie tri;
LinkedList li;
sf::Font font;
DrawingUnit drawing_unit;
MenuManager menu_manager;
LLNode* searched = nullptr;
Button* text_box = nullptr;

UIUnit menu, settings, about, visualizer;


void setup_menus() {
	setup_menu(menu);
	setup_about(about);
	setup_settings(settings);
	setup_visualizer(visualizer);
}

void appStart(sf::RenderWindow& appwindow) {
	// load font
	font.openFromFile(FONT_PATH.c_str());

	tri = Trie();
	li = LinkedList();

	drawing_unit = DrawingUnit(&appwindow, font);

	menu = UIUnit(&appwindow, font);
	settings = UIUnit(&appwindow, font);
	about = UIUnit(&appwindow, font);
	visualizer = UIUnit(&appwindow, font);
	
	setup_menus();
}

bool pressing = false;
void handle_textbox_input(float delta);
void handle_keypress(float delta) {
	handle_textbox_input(delta);
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
		if (event->is <sf::Event::Closed>()) {
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


void handle_settings(sf::RenderWindow& appwindow) {
	settings.draw(get_mouse_pos(appwindow));

	Button* cur = settings.check_hovering(get_mouse_pos(appwindow));
	if (just_clicked) {
		if (cur) {
			if (cur->get_string() == "BACK") {
				menu_manager.set_current_state(MENU);
			}
		}
	}
}


void handle_about(sf::RenderWindow& appwindow) {
	about.draw(get_mouse_pos(appwindow));

	Button* cur = about.check_hovering(get_mouse_pos(appwindow));
	if (just_clicked) {
		if (cur) {
			if (cur->get_string() == "BACK") {
				menu_manager.set_current_state(MENU);
			}
		}
	}
}

int prev_mask = 0;
std::string text_box_mode = "";
void handle_textbox_input(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
		visualizer.erase_element(text_box);
		text_box = nullptr;

		text_box = add_text_box(visualizer, sf::Vector2f(250, 700), sf::Vector2f(200, 60), 26, false, "");
		text_box_mode = "INSERT";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		visualizer.erase_element(text_box);
		text_box = nullptr;

		text_box = add_text_box(visualizer, sf::Vector2f(250, 770), sf::Vector2f(200, 60), 26, false, "");
		text_box_mode = "ERASE";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		visualizer.erase_element(text_box);
		text_box = nullptr;

		text_box = add_text_box(visualizer, sf::Vector2f(250, 840), sf::Vector2f(200, 60), 26, false, "");
		text_box_mode = "SEARCH";
	}
	else if (text_box) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			visualizer.erase_element(text_box);
			text_box = nullptr;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			if (text_box_mode == "INSERT") {
				li.insert(text_box->get_string());
				searched = nullptr;
			}
			else if (text_box_mode == "ERASE") {
				li.erase(text_box->get_string());
				searched = nullptr;
			}
			else if (text_box_mode == "SEARCH") {
				searched = li.locate(text_box->get_string());
			}

			visualizer.erase_element(text_box);
			text_box = nullptr;
		}
		else {
			int cur_mask = 0;
			for (int j = 0; j <= 9; ++j) {
				sf::Keyboard::Key num_key = (sf::Keyboard::Key)((int)sf::Keyboard::Key::Num0 + j);
				if (sf::Keyboard::isKeyPressed(num_key))
					cur_mask += (1 << j);
			}

			int x = prev_mask, y = cur_mask;
			prev_mask = cur_mask;
			for (int j = 0; j < 10; ++j) {
				if (x % 2 == 0 && y % 2 == 1) {
					std::string cur = text_box->get_string();
					if (cur.size() < 10) cur.push_back('0' + j);
					text_box->set_string(cur);
				}
				x /= 2; y /= 2;
			}
		}
		
	}
}

void handle_visualizing(sf::RenderWindow& appwindow) {
	visualizer.draw(get_mouse_pos(appwindow));

	Button* cur = visualizer.check_hovering(get_mouse_pos(appwindow));
	if (just_clicked) {
		if (cur && cur->get_type() != TEXTBOX) {
			if (cur->get_string() == "BACK") {
				menu_manager.set_current_state(MENU);
				searched = nullptr;
				li.clear();

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";
			}
			else if (cur->get_string() == "INSERT") {
				searched = nullptr;

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";


				text_box = add_text_box(visualizer, sf::Vector2f(250, 700), sf::Vector2f(200, 60), 26, false, "");
				text_box_mode = "INSERT";
			}	
			else if (cur->get_string() == "ERASE") {

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";

				text_box = add_text_box(visualizer, sf::Vector2f(250, 770), sf::Vector2f(200, 60), 26, false, "");
				text_box_mode = "ERASE";
			}
			else if (cur->get_string() == "SEARCH") {

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";

				text_box = add_text_box(visualizer, sf::Vector2f(250, 840), sf::Vector2f(200, 60), 26, false, "");
				text_box_mode = "SEARCH";
			}
		}
	}
	drawing_unit.draw_linked_list(li, sf::Vector2f(300, 400), searched);
}

void appLoop(sf::RenderWindow& appwindow, float delta) { // receive delta in s
	int cur = pollEvent(appwindow);
	if (cur == 0) return;

	appwindow.clear(BACKGROUND);
	
	handle_mouse(appwindow, delta);
	handle_keypress(delta);

	switch (menu_manager.get_current_state()) {
	case MENU:
		handle_menu(appwindow);
		break;
	case SETTINGS:
		handle_settings(appwindow);
		break;
	case ABOUT:
		handle_about(appwindow);
		break;
	case VISUALIZING:
		handle_visualizing(appwindow);
		break;
	}

	appwindow.display();
}