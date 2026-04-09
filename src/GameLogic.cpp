
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
#include <DataStructures/Dijkstra.hpp>
#include <DataStructures/Kruskal.hpp>

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
std::string text_box_mode = "";

UIUnit menu, settings, about, visualizer;
BackgroundDrawer bg_drawer;
InputHandler input_state;

std::vector<Graph> graph_versions;
float epoch;

Graph get_graph() {
	void* current_ds = ds.get_current_structure();
	switch (ds.get_current_type()) {
	case LINKED_LIST:
		return drawing_unit.get_linked_list_graph(
			(LinkedList*)current_ds, LINKED_LIST_POS, (LLNode*)searched);
	case HASHMAP_CHAIN:
		return drawing_unit.get_hash_map_graph(
			(HashMapChaining*)current_ds, HASH_MAP_POS, (LLNode*)searched);
	case AVL_TREE:
		return drawing_unit.get_BST_graph(
			(AVL*)current_ds, BST_POS, (AVLNode*)searched);
	case TRIE:
		return drawing_unit.get_trie_graph(
			(Trie*)current_ds, TRIE_POS, (TrieNode*)searched);
	case KRUSKAL:
		return drawing_unit.get_kruskal_graph(
			(Kruskal*)current_ds, GRAPH_ROOT
		);
	case DIJKSTRA:
		return drawing_unit.get_dijkstra_graph(
			(Dijkstra*)current_ds, GRAPH_ROOT
		);

		break;
	}
	Graph empty_graph;
	return empty_graph;
}

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
	input_state = InputHandler(&appwindow);

	menu = UIUnit(&appwindow, font);
	settings = UIUnit(&appwindow, font);
	about = UIUnit(&appwindow, font);
	visualizer = UIUnit(&appwindow, font);

	add_text(visualizer, sf::Vector2f(0, 200), 36, 
		CENTER_CENTER, TOP_CENTER, "DS_NAME", get_ds_name(ds.get_current_type()));

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
			if (menu_switcher(cur->get_name()));
			else if (cur->get_name() == "QUIT") {
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
			if (menu_switcher(cur->get_name()));
		}
	}
}


void handle_about(sf::RenderWindow& appwindow, UIUnit& about, MenuManager& menu_manager) {
	about.draw(input_state.get_mouse_pos());

	Button* cur = about.check_hovering(input_state.get_mouse_pos());
	if (input_state.get_mouse_state() == CLICK) {
		if (cur) {
			if (menu_switcher(cur->get_name()));
		}
	}
}


void handle_ds_switcher() {
	if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK || input_state.get_keyboard_key(RIGHT_ARROW) == CLICK) {
		if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK)
			ds.previous_data_structure();
		else if (input_state.get_keyboard_key(RIGHT_ARROW) == CLICK)
			ds.next_data_structure();

		visualizer.erase_element(visualizer.find_button("TEXT_BOX"));
		despawn_form(visualizer);
		text_box_mode = ""; 
		graph_versions.clear();
	}
}

float message_time = 0;

void handle_textbox_input(Button* cur, UIUnit &visualizer) {
	std::string pressed_button = "";
	sf::Vector2f mouse_pos = input_state.get_mouse_pos();
	if (input_state.get_mouse_state() == CLICK) {
		visualizer.click(mouse_pos);
		if (cur) {
			pressed_button = cur->get_name();
		}
	}

	if (pressed_button.size())
		despawn_message_box(visualizer);

	if (menu_switcher(pressed_button)) {
		searched = nullptr;
		ds.reset_current();
		visualizer.erase_element(visualizer.find_button("TEXT_BOX"));		
		despawn_message_box(visualizer);

		graph_versions.clear();
		epoch = 0;
		text_box_mode = "";
	}
	else if (input_state.get_keyboard_key(KEY_I) == CLICK || pressed_button == "COMMAND_1") {
		visualizer.erase_element(visualizer.find_button("TEXT_BOX"));
		despawn_message_box(visualizer);
		if (ds.is_drawing_ds())
			text_box_mode = spawn_text_box(visualizer, "INSERT");
		else {
			spawn_form(visualizer);
			text_box_mode = "INSERT";
		}
	}
	else if (input_state.get_keyboard_key(KEY_E) == CLICK || pressed_button == "COMMAND_2") {
		visualizer.erase_element(visualizer.find_button("TEXT_BOX"));
		despawn_message_box(visualizer);
		if (ds.is_drawing_ds())
			text_box_mode = spawn_text_box(visualizer, "ERASE");
		else {
			spawn_form(visualizer);
			text_box_mode = "ERASE";
		}
	}
	else if (input_state.get_keyboard_key(KEY_S) == CLICK || pressed_button == "COMMAND_3") {
		visualizer.erase_element(visualizer.find_button("TEXT_BOX"));
		despawn_message_box(visualizer);

		if (ds.is_drawing_ds())
			text_box_mode = spawn_text_box(visualizer, "SEARCH");
	}
	else if (visualizer.get_focused_text_box()) {
		if (input_state.get_keyboard_key(ESC) == CLICK) {
			visualizer.erase_element(visualizer.find_button("TEXT_BOX"));
			despawn_message_box(visualizer);
			text_box_mode = "";
		}
		else if (input_state.get_keyboard_key(TABS) == CLICK && input_state.get_keyboard_key(LSHIFT) != RELEASE) {
			Button* cur = visualizer.get_focused_text_box();
			if (cur->get_name() == "TEXT_BOX_W") {
				cur->set_focused(0);
				visualizer.find_button("TEXT_BOX_V")->set_focused(1);
			}
			else if (cur->get_name() == "TEXT_BOX_V") {
				cur->set_focused(0);
				visualizer.find_button("TEXT_BOX_U")->set_focused(1);
			}
		}
		else if (input_state.get_keyboard_key(TABS) == CLICK 
			|| input_state.get_keyboard_key(ENTER) == CLICK
			|| input_state.get_keyboard_key(SPACE) == CLICK) {
			despawn_message_box(visualizer);
			if (ds.is_drawing_ds()) {
				if (visualizer.find_button("TEXT_BOX")->get_string().size()) {
					searched = nullptr;
					if (text_box_mode == "INSERT") {
						if (ds.insert(visualizer.find_button("TEXT_BOX")->get_string())) {
							graph_versions.push_back(get_graph());
							epoch = 0;
						}
					}
					else if (text_box_mode == "ERASE") {
						if (ds.erase(visualizer.find_button("TEXT_BOX")->get_string())) {
							graph_versions.push_back(get_graph());
							epoch = 0;
						}
						else {
							spawn_message_box(visualizer, "You erased a non-existing element!");
							message_time = 0;
						}
					}
					else if (text_box_mode == "SEARCH") {
						searched = ds.search(visualizer.find_button("TEXT_BOX")->get_string());
						graph_versions.push_back(get_graph());
						epoch = 0;
					}
					visualizer.erase_element(visualizer.find_button("TEXT_BOX"));
					text_box_mode = "";
				}
			}
			else {
				Button* cur = visualizer.get_focused_text_box();
				if (cur->get_name() == "TEXT_BOX_U") {
					cur->set_focused(0);
					visualizer.find_button("TEXT_BOX_V")->set_focused(1);
				}
				else if (cur->get_name() == "TEXT_BOX_V") {
					cur->set_focused(0);
					visualizer.find_button("TEXT_BOX_W")->set_focused(1);
				}
				else {
					std::string u = visualizer.find_button("TEXT_BOX_U")->get_string();
					std::string v = visualizer.find_button("TEXT_BOX_V")->get_string();
					std::string w = visualizer.find_button("TEXT_BOX_W")->get_string();

					if (u.size() && v.size() && w.size()) {
						if (text_box_mode == "INSERT") {
							if (ds.insert(" " + u + " " + v + " " + w))
								graph_versions.push_back(get_graph());
						}
						if (text_box_mode == "ERASE") {
							if (ds.erase(" " + u + " " + v + " " + w))
								graph_versions.push_back(get_graph());
						}
						visualizer.find_button("FORM")->set_focused(0);
						text_box_mode = "";
					}
					else {
						spawn_message_box(visualizer, "You didn't inputed enough items for edge!");
						message_time = 0;
					}
				}
			}
		}
		else if (input_state.get_keyboard_key(BACKSPACE) == CLICK) {
			std::string cur = visualizer.get_focused_text_box()->get_string();
			if (cur.size()) cur.pop_back();
			visualizer.get_focused_text_box()->set_string(cur);
		}
		else {
			for (int j = 0; j < 10; ++j) {
				InputKey current = (InputKey)((int)ZERO + j);
				if (input_state.get_keyboard_key(current) == CLICK) {
					std::string cur = visualizer.get_focused_text_box()->get_string();
					if (cur.size() < 4) cur.push_back('0' + j);
					visualizer.get_focused_text_box()->set_string(cur);
				}
			}
		}
	}
}


void handle_visualizing(sf::RenderWindow& appwindow, UIUnit& visualizer, MenuManager& menu_manager) {
	handle_ds_switcher();

	if (message_time >= 1) {
		despawn_message_box(visualizer);
		message_time = 0;
	}


	Button* text_box = visualizer.find_button("TEXT_BOX");
	if (text_box != nullptr && text_box->get_focused() == false) {
		visualizer.erase_element(text_box);
		text_box_mode = "";
	}
	Button* form_box = visualizer.find_button("FORM");
	if (form_box != nullptr && form_box->get_focused() == false) {
		despawn_form(visualizer);
		text_box_mode = "";
	}

	visualizer.find_button("DS_NAME")->set_string(get_ds_name( ds.get_current_type() ));
	if (ds.is_drawing_ds()) {
		visualizer.find_button("COMMAND_1")->set_string("INSERT");
		visualizer.find_button("COMMAND_2")->set_string("ERASE");
		visualizer.find_button("COMMAND_3")->set_string("SEARCH");
	}
	else {
		visualizer.find_button("COMMAND_1")->set_string("INSERT");
		visualizer.find_button("COMMAND_2")->set_string("ERASE");
		visualizer.find_button("COMMAND_3")->set_string("RUN");
	}

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
	message_time += delta;

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