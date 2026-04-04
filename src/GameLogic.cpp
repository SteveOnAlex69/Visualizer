#include <Helper.hpp>
#include <GameLogic.hpp>
#include <MediaPlayer.hpp>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>


#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/Trie.hpp>
#include <DataStructures/AVL.hpp>
#include <DataStructures/General.hpp>

#include <Drawing/DrawingUnit.hpp>
#include <UI/MenuManager.hpp>
#include <UI/UIUnit.hpp>
#include <UI/UIDesign.hpp>

#include <Decoration/Background.hpp>

#define ll long long
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

sf::Font font;
DrawingUnit drawing_unit;
MenuManager menu_manager;


GeneralData ds;
void* searched = nullptr;
Button* text_box = nullptr;
Button* ds_name = nullptr;

UIUnit menu, settings, about, visualizer;

BackgroundDrawer bg_drawer;


void setup_menus() {
	setup_menu(menu);
	setup_about(about);
	setup_settings(settings);
	setup_visualizer(visualizer);
}

void appStart(sf::RenderWindow& appwindow) {
	// load font
	font.openFromFile(FONT_PATH.c_str());

	ds = GeneralData();

	drawing_unit = DrawingUnit(&appwindow, font);
	bg_drawer = BackgroundDrawer(&appwindow, font);

	menu = UIUnit(&appwindow, font);
	settings = UIUnit(&appwindow, font);
	about = UIUnit(&appwindow, font);
	visualizer = UIUnit(&appwindow, font);

	ds_name = add_text_box(visualizer, sf::Vector2f(screen_center.x, 200), sf::Vector2f(0, 0), 36, MIDDLE_CENTER,
		get_ds_name(ds.get_current_type()));
	
	setup_menus();
}

bool pressing = false;
void handle_textbox_input(float delta);
void handle_ds_switcher(float delta);

void handle_keypress(float delta) {
	handle_textbox_input(delta);
	handle_ds_switcher(delta);
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
			if (cur->get_string() == "BACK" || cur->get_string() == "SETTINGS") {
				if (cur->get_string() == "BACK")
					menu_manager.set_current_state(MENU);
				else menu_manager.set_current_state(SETTINGS);
			}
		}
	}
}

int prev_mask = 0, back_space = 0;
std::string text_box_mode = "";
void handle_textbox_input(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
		visualizer.erase_element(text_box);
		text_box = nullptr;

		text_box = add_text_box(visualizer, sf::Vector2f(250, 700), sf::Vector2f(200, 60), 26, TOP_LEFT, "");
		text_box_mode = "INSERT";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		visualizer.erase_element(text_box);
		text_box = nullptr;

		text_box = add_text_box(visualizer, sf::Vector2f(250, 790), sf::Vector2f(200, 60), 26, TOP_LEFT, "");
		text_box_mode = "ERASE";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		visualizer.erase_element(text_box);
		text_box = nullptr;

		text_box = add_text_box(visualizer, sf::Vector2f(250, 880), sf::Vector2f(200, 60), 26, TOP_LEFT, "");
		text_box_mode = "SEARCH";
	}
	else if (text_box) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			visualizer.erase_element(text_box);
			text_box = nullptr;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			if (text_box_mode == "INSERT") {
				if (text_box -> get_string().size())
					ds.insert(text_box->get_string());
				searched = nullptr;
			}
			else if (text_box_mode == "ERASE") {
				if (text_box->get_string().size())
					ds.erase(text_box->get_string());
				searched = nullptr;
			}
			else if (text_box_mode == "SEARCH") {
				if (text_box->get_string().size())
					searched = ds.search(text_box->get_string());
			}

			visualizer.erase_element(text_box);
			text_box = nullptr;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
			if (back_space == 0) {
				std::string cur = text_box->get_string();
				if (cur.size()) cur.pop_back();
				text_box->set_string(cur);
				back_space = 1;
			}
		}
		else {
			back_space = 0;
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
					if (cur.size() < 4) cur.push_back('0' + j);
					text_box->set_string(cur);
				}
				x /= 2; y /= 2;
			}
		}
		
	}
}

int prev_arrow = 0;
void handle_ds_switcher(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		if (prev_arrow == 0) {
			ds.previous_data_structure();
			delete text_box;
			text_box_mode = "";
			text_box = nullptr;
		}
		prev_arrow = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		if (prev_arrow == 0) {
			ds.next_data_structure();

			visualizer.erase_element(text_box);
			delete text_box;
			text_box_mode = "";
			text_box = nullptr;
		}
		prev_arrow = 1;
	}
	else {
		prev_arrow = 0;
	}
}


void handle_visualizing(sf::RenderWindow& appwindow) {
	ds_name->set_string(get_ds_name( ds.get_current_type() ));

	Button* cur = visualizer.check_hovering(get_mouse_pos(appwindow));
	if (just_clicked) {
		if (cur && cur->get_type() != TEXTBOX) {
			if (cur->get_string() == "BACK" || cur->get_string() == "SETTINGS") {
				if (cur->get_string() == "BACK")
					menu_manager.set_current_state(MENU);
				else menu_manager.set_current_state(SETTINGS);
				searched = nullptr;
				ds.reset_current();

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";
			}
			else if (cur->get_string() == "INSERT") {
				searched = nullptr;

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";


				text_box = add_text_box(visualizer, sf::Vector2f(250, 700), sf::Vector2f(200, 60), 26, TOP_LEFT, "");
				text_box_mode = "INSERT";
			}	
			else if (cur->get_string() == "ERASE") {

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";

				text_box = add_text_box(visualizer, sf::Vector2f(250, 790), sf::Vector2f(200, 60), 26, TOP_LEFT, "");
				text_box_mode = "ERASE";
			}
			else if (cur->get_string() == "SEARCH") {

				visualizer.erase_element(text_box);
				text_box = nullptr;
				text_box_mode = "";

				text_box = add_text_box(visualizer, sf::Vector2f(250, 880), sf::Vector2f(200, 60), 26, TOP_LEFT, "");
				text_box_mode = "SEARCH";
			}
		}
	}
	void* current_ds = ds.get_current_structure();
	switch (ds.get_current_type()) {
	case LINKED_LIST:	
		drawing_unit.draw_linked_list((LinkedList*)current_ds, LINKED_LIST_POS, (LLNode*)searched);
		break;
	case HASHMAP_CHAIN:
		drawing_unit.draw_hash_map((HashMapChaining*)current_ds, HASH_MAP_POS, (LLNode*)searched);
		break;
	case BST_TREE:
		drawing_unit.draw_BST((AVL*)current_ds, BST_POS, (AVLNode*)searched);
		break;
	case AVL_TREE:
		drawing_unit.draw_BST((AVL*)current_ds, AVL_POS, (AVLNode*)searched);
		break;
	case TRIE:
		drawing_unit.draw_trie((Trie*)current_ds, TRIE_POS, (TrieNode*)searched);
		break;
	}


	visualizer.draw(get_mouse_pos(appwindow));

}

void appLoop(sf::RenderWindow& appwindow, float delta) { // receive delta in s
	int cur = pollEvent(appwindow);
	if (cur == 0) return;

	bg_drawer.draw(get_mouse_pos(appwindow), delta);
	
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