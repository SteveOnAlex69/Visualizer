
#include <GameLogic.hpp>
#include <Helper.hpp>
#include <MediaPlayer.hpp>
#include <algorithm>
#include <concepts>
#include <filesystem>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include <DataStructures/AVL.hpp>
#include <DataStructures/General.hpp>
#include <DataStructures/Hashmap.hpp>
#include <DataStructures/LinkedList.hpp>
#include <DataStructures/Trie.hpp>

#include <Drawing/DrawingUnit.hpp>
#include <Drawing/Graph.hpp>
#include <Drawing/Node.hpp>

#include <UI/MenuManager.hpp>
#include <UI/UIDesign.hpp>
#include <UI/UIUnit.hpp>

#include <Decoration/Background.hpp>
#include <Input/InputHandler.hpp>


#define ll long long
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

sf::Font font;
DrawingUnit drawing_unit;
MenuManager menu_manager;


GeneralData ds;
void* searched = nullptr;
Button* text_box = nullptr;
std::string text_box_mode = "";
Button* ds_name = nullptr;

UIUnit menu, settings, about, visualizer;
BackgroundDrawer bg_drawer;
InputHandler input_state;

std::vector<Graph> graph_versions;
float epoch;


void setup_menus() {
	setup_menu(menu);
	setup_about(about);
	setup_settings(settings);
	setup_visualizer(visualizer);
}

Graph get_graph() {
	void* current_ds = ds.get_current_structure();
	switch (ds.get_current_type()) {
	case LINKED_LIST:
		return drawing_unit.get_linked_list_graph(
			(LinkedList*)current_ds, LINKED_LIST_POS, (LLNode*)searched);
	case HASHMAP_CHAIN:
		return drawing_unit.get_hash_map_graph(
			(HashMapChaining*)current_ds, HASH_MAP_POS, (LLNode*)searched);
	case BST_TREE:
	case AVL_TREE:
		return drawing_unit.get_BST_graph(
			(AVL*)current_ds, BST_POS, (AVLNode*)searched);
	case TRIE:
		return drawing_unit.get_trie_graph(
			(Trie*)current_ds, TRIE_POS, (TrieNode*)searched);
	}
}

void appStart(sf::RenderWindow& appwindow) {
	// load font
	font.openFromFile(FONT_PATH.c_str());

	ds = GeneralData();
	drawing_unit = DrawingUnit(&appwindow, font);
	bg_drawer = BackgroundDrawer(&appwindow, font);
	input_state = InputHandler(&appwindow);

	menu = UIUnit(&appwindow, font);
	settings = UIUnit(&appwindow, font);
	about = UIUnit(&appwindow, font);
	visualizer = UIUnit(&appwindow, font);

	ds_name = add_text_box(visualizer, sf::Vector2f(screen_center.x, 200), sf::Vector2f(0, 0), 36, MIDDLE_CENTER,
		get_ds_name(ds.get_current_type()));
	
	setup_menus();
}
void handle_keypress() {

}

bool menu_switcher(std::string s) { // true means switching away from the current menu
	if (s == "BACK")
		menu_manager.set_current_state(MENU);
	else if (s == "START")
		menu_manager.set_current_state(VISUALIZING);
	else if (s == "ABOUT")
		menu_manager.set_current_state(ABOUT);
	else if (s == "SETTINGS")
		menu_manager.set_current_state(SETTINGS);
	else return false;
	return true;
}

void handle_menu(sf::RenderWindow& appwindow, UIUnit &menu, MenuManager &menu_manager) {
	menu.draw(input_state.get_mouse_pos());
	Button* cur = menu.check_hovering(input_state.get_mouse_pos());
	if (input_state.get_mouse_state() == CLICK) {
		if (cur) {
			if (menu_switcher(cur->get_string()));
			else if (cur->get_string() == "QUIT") {
				appwindow.close();
			}
		}
	}
}


void handle_settings(sf::RenderWindow& appwindow, UIUnit& settings, MenuManager& menu_manager) {
	settings.draw(input_state.get_mouse_pos());
	Button* cur = settings.check_hovering(input_state.get_mouse_pos());
	if (input_state.get_mouse_state() == CLICK) {
		if (cur) {
			if (menu_switcher(cur->get_string()));
		}
	}
}


void handle_about(sf::RenderWindow& appwindow, UIUnit& about, MenuManager& menu_manager) {
	about.draw(input_state.get_mouse_pos());

	Button* cur = about.check_hovering(input_state.get_mouse_pos());
	if (input_state.get_mouse_state() == CLICK) {
		if (cur) {
			if (menu_switcher(cur->get_string()));
		}
	}
}


void handle_ds_switcher() {
	if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK || input_state.get_keyboard_key(RIGHT_ARROW) == CLICK) {
		if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK)
			ds.previous_data_structure();
		else if (input_state.get_keyboard_key(RIGHT_ARROW) == CLICK)
			ds.next_data_structure();

		visualizer.erase_element(text_box);
		text_box_mode = ""; text_box = nullptr;
		graph_versions.clear();
	}
}


void handle_textbox_input(Button* cur, UIUnit &visualizer) {
	std::string pressed_button = "";
	if (input_state.get_mouse_state() == CLICK) {
		if (cur && cur->get_type() != TEXTBOX) {
			pressed_button = cur->get_string();
		}
	}
	if (menu_switcher(pressed_button)) {
		searched = nullptr;
		ds.reset_current();
		visualizer.erase_element(text_box);
		graph_versions.clear();
		epoch = 0;
		text_box = nullptr; text_box_mode = "";
	}
	else if (input_state.get_keyboard_key(KEY_I) == CLICK || pressed_button == "INSERT") {
		visualizer.erase_element(text_box);
		text_box_mode = spawn_text_box(visualizer, text_box, "INSERT");
	}
	else if (input_state.get_keyboard_key(KEY_E) == CLICK || pressed_button == "ERASE") {
		visualizer.erase_element(text_box);
		text_box_mode = spawn_text_box(visualizer, text_box, "ERASE");
	}
	else if (input_state.get_keyboard_key(KEY_S) == CLICK || pressed_button == "SEARCH") {
		visualizer.erase_element(text_box);
		text_box_mode = spawn_text_box(visualizer, text_box, "SEARCH");
	}
	else if (text_box) {
		if (input_state.get_keyboard_key(ESC) == CLICK) {
			visualizer.erase_element(text_box);
			text_box = nullptr; text_box_mode = "";
		}
		else if (input_state.get_keyboard_key(ENTER) == CLICK) {
			if (text_box->get_string().size()) {
				searched = nullptr;
				if (text_box_mode == "INSERT") {
					if (ds.insert(text_box->get_string())) {
						graph_versions.push_back(get_graph());
						epoch = 0;
					}
				}
				else if (text_box_mode == "ERASE") {
					if (ds.erase(text_box->get_string())) {
						graph_versions.push_back(get_graph());
						epoch = 0;
					}
				}
				else if (text_box_mode == "SEARCH") {
					searched = ds.search(text_box->get_string());
					graph_versions.push_back(get_graph());
					epoch = 0;
				}
				visualizer.erase_element(text_box);
				text_box = nullptr; text_box_mode = "";
			}
		}
		else if (input_state.get_keyboard_key(BACKSPACE) == CLICK) {
			std::string cur = text_box->get_string();
			if (cur.size()) cur.pop_back();
			text_box->set_string(cur);
		}
		else {
			for (int j = 0; j < 10; ++j) {
				InputKey current = (InputKey)((int)ZERO + j);
				if (input_state.get_keyboard_key(current) == CLICK) {
					std::string cur = text_box->get_string();
					if (cur.size() < 4) cur.push_back('0' + j);
					text_box->set_string(cur);
				}
			}
		}
	}
}


void handle_visualizing(sf::RenderWindow& appwindow, UIUnit& visualizer, MenuManager& menu_manager) {
	handle_ds_switcher();
	ds_name->set_string(get_ds_name( ds.get_current_type() ));
	Button* cur = visualizer.check_hovering(input_state.get_mouse_pos());
	handle_textbox_input(cur, visualizer);

	if (graph_versions.empty()) {
		graph_versions.push_back(get_graph());
		epoch = 0;
	}

	if (epoch >= ANIMATION_TIME || graph_versions.size() == 1)
		drawing_unit.draw_graph(graph_versions.back());
	else drawing_unit.draw_graph(graph_versions[graph_versions.size() - 2], 
		graph_versions[graph_versions.size() - 1], epoch);
	visualizer.draw(input_state.get_mouse_pos());
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

void appLoop(sf::RenderWindow& appwindow, float delta) { // receive delta in s
	int cur = pollEvent(appwindow);
	if (cur == 0) return;

	bg_drawer.draw(input_state.get_mouse_pos(), delta);
	input_state.update_mouse(delta);
	input_state.update_keyboard(delta);

	epoch += delta;

	switch (menu_manager.get_current_state()) {
	case MENU:
		handle_menu(appwindow, menu, menu_manager);
		break;
	case SETTINGS:
		handle_settings(appwindow, settings, menu_manager);
		break;
	case ABOUT:
		handle_about(appwindow, about, menu_manager);
		break;
	case VISUALIZING:
		handle_visualizing(appwindow, visualizer, menu_manager);
		break;
	}

	appwindow.display();
}