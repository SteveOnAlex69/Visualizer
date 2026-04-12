
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

#include <Drawing/AnimationUnit.hpp>
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
std::string text_box_mode = "";

UIUnit menu, settings, about, visualizer, selection;
BackgroundDrawer bg_drawer;
InputHandler input_state;

AnimationUnit anim;
float message_time = 0;
Graph get_graph(void* bruno = nullptr, int cnt = 1) {
	void* current_ds = ds.get_current_structure();
	std::vector<void*> search_nodes;
	if (bruno) {
		while (cnt--)
			search_nodes.push_back(bruno);
	}

	switch (ds.get_current_type()) {
	case LINKED_LIST:
		return drawing_unit.get_linked_list_graph(
			(LinkedList*)current_ds, LINKED_LIST_POS, search_nodes);
	case HASHMAP_CHAIN:
		return drawing_unit.get_hash_map_graph(
			(HashMapChaining*)current_ds, HASH_MAP_POS, search_nodes);
	case AVL_TREE:
		return drawing_unit.get_BST_graph(
			(AVL*)current_ds, BST_POS, search_nodes);
	case TRIE:
		return drawing_unit.get_trie_graph(
			(Trie*)current_ds, TRIE_POS, search_nodes);
	case KRUSKAL:
		return drawing_unit.get_kruskal_graph(
			(Kruskal*)current_ds, GRAPH_ROOT
		);
	case DIJKSTRA:
		std::vector<int> empty_list;
		std::vector<std::pair<int, int>> empty_edges;
		return drawing_unit.get_dijkstra_graph(
			(Dijkstra*)current_ds, GRAPH_ROOT, empty_list, empty_list, empty_edges, empty_edges
		);

		break;
	}
	Graph empty_graph;
	return empty_graph;
}

void update_graph(bool flag = 1) { // for a single update
	anim.add_graph(get_graph(), flag);
}

void load_kruskal() { // for loading the entire kruskal family
	anim.force_latest();
	void* current_ds = ds.get_current_structure();
	anim.clear_graph();
	for (int i = 0; ; ++i) {
		Graph cur = drawing_unit.get_kruskal_graph(
			(Kruskal*)current_ds, GRAPH_ROOT, i
		);
		if (cur.get_node_list().size() == 0) break;
		anim.add_graph(cur, 0);
	}
}

void execute_graph_search(std::vector<void*> searched_nodes) {
	anim.force_latest();
	void* current_ds = ds.get_current_structure();
	for (auto i : searched_nodes) {
		anim.add_graph(get_graph(i), 0);
	}
	if (searched_nodes.size() && searched_nodes.back() != nullptr)
		anim.add_graph(get_graph(searched_nodes.back(), 2), 0);
}

void load_dijkstra(std::string x, std::string y) {
	int u = std::stoi(x), v = std::stoi(y);

	Dijkstra* dih = (Dijkstra*)ds.get_current_structure();
	std::vector<int> vertices = dih->get_vertices();
	if (std::binary_search(vertices.begin(), vertices.end(), u) &&
		std::binary_search(vertices.begin(), vertices.end(), v)) {
		anim.force_latest();

		std::vector<std::pair<int, int>> spread_adventure =
			dih->run_dijkstra(u, v);
		
		std::vector<int> lmao;
		std::vector<int> matter;
		std::vector<std::pair<int,int>> edges1, edges2;
		for (auto i : spread_adventure) {
			lmao.push_back(i.first);
			edges1.push_back(std::make_pair(i.second, i.first));
			Graph cur = drawing_unit.get_dijkstra_graph(
				dih, GRAPH_ROOT, lmao, matter, edges1, edges2
			);
			anim.add_graph(cur, 0);
		}

		matter = dih->get_shortest_path(u, v);

		std::vector<int> shortest_path;
		for (int i = 0; i < (int)matter.size(); ++i) {
			shortest_path.push_back(matter[i]);
			if (i > 0)
				edges2.push_back(std::make_pair(matter[i - 1], matter[i]));
			Graph cur = drawing_unit.get_dijkstra_graph(
				dih, GRAPH_ROOT, lmao, shortest_path, edges1, edges2
			);
			anim.add_graph(cur, 0);
		}
	}
	else {
		spawn_message_box(visualizer, "The two vertices you inputed doesn't exist!");
		message_time = 0;
	}
}

void handle_insertion(std::string s) {
	void* current_ds = ds.get_current_structure();
	anim.force_latest();
	switch (ds.get_current_type()) {
	case AVL_TREE:
	{
		std::vector<void*> searched_nodes = ds.search_before_insert(s);
		for (auto i : searched_nodes) 
			anim.add_graph(get_graph(i), 0);
		if (searched_nodes.size() && searched_nodes.back() != nullptr)
			anim.add_graph(get_graph(searched_nodes.back(), 2), 0);

		ds.insert(s); update_graph(0);
		if (ds.balance_structure()) update_graph(0);
		break;
	}
	case TRIE:
	{
		std::vector<void*> searched_nodes = ds.search(s);
		for (auto i : searched_nodes)
			anim.add_graph(get_graph(i), 0);
		while (true) {
			int val = ds.insert(s);
			std::vector<void*> searched_nodes = ds.search(s);
			if (searched_nodes.back() == nullptr) searched_nodes.pop_back();
			anim.add_graph(get_graph(searched_nodes.back(), 3 - val), 0);
			if (val == 1) break;
		}
		break;
	}
	default:
	{
		ds.insert(s); update_graph(0);
		break;
	}
	}
}



void handle_deletion(std::string s) {
	void* current_ds = ds.get_current_structure();
	switch (ds.get_current_type()) {
	case LINKED_LIST:
	case HASHMAP_CHAIN:
	case TRIE:
	{
		std::vector<void*> searched = ds.search(s);
		execute_graph_search(searched);
		if (searched.back()) {
			while (true) {
				std::vector<void*> searched = ds.search(s);
				while (searched.size() && searched.back() == nullptr) searched.pop_back();
				anim.add_graph(get_graph(searched.back(), 2), 0);

				int val = ds.erase(s);
				update_graph(0);
				if (val == 0) return;
			}
		}
		
		break;
	}
	case AVL_TREE:
	{
		std::vector<void*> searched = ds.search(s);
		execute_graph_search(searched);
		if (ds.erase(s)) update_graph(0);
		if (ds.balance_structure()) update_graph(0);
		break;
	}
	case KRUSKAL:
	case DIJKSTRA:
	{
		anim.force_latest();
		if (ds.erase(s)) update_graph(0);
		break;
	}
	}
}

void setup_menus() {
	setup_menu(menu);
	setup_about(about);
	setup_settings(settings);
	setup_visualizer(visualizer);
	setup_selection(selection);
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
	selection = UIUnit(&appwindow, font);

	add_text(visualizer, sf::Vector2f(0, 200), 36, 
		CENTER_CENTER, TOP_CENTER, "DS_NAME", get_ds_name(ds.get_current_type()));

	setup_menus();
}

void handle_keypress() {

}

bool menu_switcher(std::string s) { // true means switching away from the current menu
	if (s == "BACK")
		menu_manager.set_current_state(MENU);
	else if (s == "START" || s == "SELECT")
		menu_manager.set_current_state(SELECTION);
	else if (s == "ABOUT")
		menu_manager.set_current_state(ABOUT);
	else if (s == "SETTINGS")
		menu_manager.set_current_state(SETTINGS);
	else if (s == "VISUALIZE")
		menu_manager.set_current_state(VISUALIZING);
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


void handle_selection(sf::RenderWindow& appwindow, UIUnit& selection, MenuManager& menu_manager) {
	selection.draw(input_state.get_mouse_pos());

	Button* cur = selection.check_hovering(input_state.get_mouse_pos());
	if (input_state.get_mouse_state() == CLICK) {
		if (cur) {
			std::string btn_name = cur->get_name();
			if (menu_switcher(btn_name));
			if (btn_name.substr(0, 4) == "DATA") {
				int threat = btn_name.back() - '1';
				menu_switcher("VISUALIZE");
				ds.change_data_structure((DS)threat);
			}
		}
	}
}


void handle_ds_switcher() {
	if (input_state.get_keyboard_key(LSHIFT) != RELEASE)
	if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK || input_state.get_keyboard_key(RIGHT_ARROW) == CLICK) {
		if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK)
			ds.previous_data_structure();
		else if (input_state.get_keyboard_key(RIGHT_ARROW) == CLICK)
			ds.next_data_structure();

		despawn_text_box(visualizer);
		despawn_form(visualizer);
		text_box_mode = ""; 
		anim.clear_graph();


		for (int i = 1; i <= 3; ++i)
			visualizer.find_button("COMMAND_" + std::string(1, '0' + i))->set_focused(0);
	}
}


int command_activated(std::string command) {
	if (input_state.get_keyboard_key(KEY_I) == CLICK || command == "COMMAND_1") return 1;
	if (input_state.get_keyboard_key(KEY_E) == CLICK || command == "COMMAND_2") return 2;
	if (input_state.get_keyboard_key(KEY_S) == CLICK || command == "COMMAND_3") return 3;
	return 0;
}

void execute_command(int command) {
	despawn_text_box(visualizer);
	despawn_message_box(visualizer);
	despawn_form(visualizer);

	for (int i = 1; i <= 3; ++i) 
		visualizer.find_button("COMMAND_" + std::string(1, '0' + i)) -> set_focused(0);
	visualizer.find_button("COMMAND_" + std::string(1, '0' + command))->set_focused(1);
	if (ds.is_drawing_ds()) {
		text_box_mode = spawn_text_box(visualizer, command_name[command - 1]);
	}
	else {
		if (command <= 2) {
			spawn_form(visualizer, 3);
			text_box_mode = command_name[command - 1];
		}
		else {
			if (ds.get_current_type() == KRUSKAL)
				load_kruskal();
			else {
				spawn_form(visualizer, 2);
				text_box_mode = "RUN";
			}
		}
	}
}

void text_box_receive(std::string s) {
	if (text_box_mode == "INSERT") {
		handle_insertion(s);
	}
	else if (text_box_mode == "ERASE") {
		handle_deletion(s);
	}
	else if (text_box_mode == "SEARCH") {
		std::vector<void*> searched = ds.search(s);
		execute_graph_search(searched);
	}
	despawn_text_box(visualizer);
	text_box_mode = "";
}

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
		ds.reset_current();
		despawn_text_box(visualizer);
		despawn_message_box(visualizer);

		anim.clear_graph();
		text_box_mode = "";
	}
	else if (command_activated(pressed_button)) {
		execute_command(command_activated(pressed_button));
	}
	else if (visualizer.get_focused_text_box()) {
		if (input_state.get_keyboard_key(ESC) == CLICK) {
			despawn_text_box(visualizer);
			despawn_message_box(visualizer);
			text_box_mode = "";
		}
		else if ((input_state.get_keyboard_key(TABS) == CLICK && input_state.get_keyboard_key(LSHIFT) != RELEASE)
			|| (input_state.get_keyboard_key(LEFT_ARROW) == CLICK)) {
			Button* cur = visualizer.get_focused_text_box();
			std::string name = cur->get_name();
			name.back() = max('1', name.back() - 1);
			cur->set_focused(0);
			visualizer.find_button(name)->set_focused(1);
		}
		else if (input_state.get_keyboard_key(TABS) == CLICK 
			|| input_state.get_keyboard_key(ENTER) == CLICK
			|| input_state.get_keyboard_key(SPACE) == CLICK
			|| input_state.get_keyboard_key(RIGHT_ARROW) == CLICK) {
			despawn_message_box(visualizer);
			if (ds.is_drawing_ds()) {
				std::string s = visualizer.find_button("TEXT_BOX")->get_string();
				if (s.size()) {
					text_box_receive(s);
				}
			}
			else {
				Button* cur = visualizer.get_focused_text_box();
				std::string name = cur->get_name();
				name.back()++;
				cur->set_focused(0);
				if (visualizer.find_button(name)) visualizer.find_button(name)->set_focused(1);
				else {
					cur->set_focused(1);
					if (text_box_mode == "INSERT" || text_box_mode == "ERASE") {
						std::string u = visualizer.find_button("TEXT_BOX_1")->get_string(),
							v = visualizer.find_button("TEXT_BOX_2")->get_string(),
							w = visualizer.find_button("TEXT_BOX_3")->get_string();
						if (u.size() && v.size() && w.size()) {
							bool check = false;
							if (text_box_mode == "INSERT")
								handle_insertion(" " + u + " " + v + " " + w);
							if (text_box_mode == "ERASE")
								handle_deletion(" " + u + " " + v + " " + w);
							visualizer.find_button("FORM")->set_focused(0);
							text_box_mode = "";
						}
						else {
							spawn_message_box(visualizer, "You didn't inputed enough items for edge!");
							message_time = 0;
						}
					}
					else {
						std::string u = visualizer.find_button("TEXT_BOX_1")->get_string(),
							v = visualizer.find_button("TEXT_BOX_2")->get_string();
						if (u.size() && v.size()) {
							load_dijkstra(u, v);

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
		despawn_text_box(visualizer);
		text_box_mode = "";
	}
	Button* form_box = visualizer.find_button("FORM");
	if (form_box != nullptr && form_box->get_focused() == false) {
		despawn_form(visualizer);
		text_box_mode = "";
	}

	visualizer.find_button("DS_NAME")->set_string(get_ds_name( ds.get_current_type() ));
	if (ds.is_drawing_ds()) 
		visualizer.find_button("COMMAND_3")->set_string("SEARCH");
	else 
		visualizer.find_button("COMMAND_3")->set_string("RUN");

	Button* cur = visualizer.check_hovering(input_state.get_mouse_pos());
	handle_textbox_input(cur, visualizer);

	if (anim.is_empty())
		update_graph();

	drawing_unit.draw_graph(anim.get_graph());
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

	message_time += delta;
	anim.update_timer(delta);

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
	case SELECTION:
		handle_selection(appwindow, selection, menu_manager);
		break;
	}
	
	appwindow.display();
}