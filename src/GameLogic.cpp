
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
#include <Drawing/GraphExtractor.hpp>
#include <Drawing/AnimationController.hpp>>

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

UserCommand text_box_mode = NONE;

UIUnit menu, settings, about, visualizer, selection;
BackgroundDrawer bg_drawer;
InputHandler input_state;
AnimationController anim;

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

	anim = AnimationController(new AnimationUnit(), &ds);

	add_text(visualizer, sf::Vector2f(0, 200), 36, 
		CENTER_CENTER, TOP_CENTER, "DS_NAME", get_ds_name(ds.get_current_type()));

	setup_menus();
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
		text_box_mode = NONE; 
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
	despawn_form(visualizer);

	for (int i = 1; i <= 3; ++i) 
		visualizer.find_button("COMMAND_" + std::string(1, '0' + i)) -> set_focused(0);
	visualizer.find_button("COMMAND_" + std::string(1, '0' + command))->set_focused(1);
	if (ds.is_drawing_ds()) {
		spawn_text_box(visualizer, (UserCommand) command);
		text_box_mode = (UserCommand)command;
	}
	else {
		if (command <= 2) {
			spawn_form(visualizer, 3);		
			text_box_mode = (UserCommand)command;
		}
		else {
			if (ds.get_current_type() == KRUSKAL)
				anim.load_kruskal();
			else {
				spawn_form(visualizer, 2);
				text_box_mode = RUN;
			}
		}
	}
}

void text_box_receive(std::string s) {
	if (text_box_mode == NONE) debug_error("text box mode is NONE, yet text_box_receive was called");
	if (text_box_mode == INSERT) 
		anim.handle_insertion(s);
	else if (text_box_mode == ERASE) 
		anim.handle_deletion(s);
	else if (text_box_mode == SEARCH) {
		std::vector<void*> searched = ds.search(s);
		anim.execute_graph_search(searched);
	}
	else if (text_box_mode == RUN) {
		std::vector<std::string> cur = split(s);
		if (cur.size() != 2) debug_error("not exactly 2 strings when calling RUN");
		anim.load_dijkstra(cur[0], cur[1]);
	}
	despawn_text_box(visualizer);
	despawn_form(visualizer);
	text_box_mode = NONE;
}

std::string handle_text_input(std::string cur) {
	if (input_state.get_keyboard_key(BACKSPACE) == CLICK) {
		if (cur.size()) cur.pop_back();
	}
	else {
		for (int j = 0; j < 10; ++j) {
			InputKey current = (InputKey)((int)ZERO + j);
			if (input_state.get_keyboard_key(current) == CLICK) {
				if (cur.size() < 4) cur.push_back('0' + j);
			}
		}
	}
	return cur;
}

void handle_textbox_input(UIUnit& visualizer) { // should only be called when there is a focused textbox
	Button* cur = visualizer.get_focused_text_box();
	if (cur == nullptr) debug_error("Textbox was null when calling handle_textbox_input");
	if (input_state.get_keyboard_key(ESC) == CLICK) {
		despawn_text_box(visualizer);
		text_box_mode = NONE;
	}
	else if ((input_state.get_keyboard_key(TABS) == CLICK && input_state.get_keyboard_key(LSHIFT) != RELEASE)
		|| (input_state.get_keyboard_key(LEFT_ARROW) == CLICK)) {
		std::string name = cur->get_name();
		name.back() = max('1', name.back() - 1);
		cur->set_focused(0);
		visualizer.find_button(name)->set_focused(1);
	}
	else if (input_state.get_keyboard_key(TABS) == CLICK
		|| input_state.get_keyboard_key(ENTER) == CLICK
		|| input_state.get_keyboard_key(SPACE) == CLICK
		|| (input_state.get_keyboard_key(RIGHT_ARROW) == CLICK
		&& input_state.get_keyboard_key(LSHIFT) == RELEASE)) {
		if (ds.is_drawing_ds()) {
			std::string s = cur->get_string();
			if (s.size())
				text_box_receive(s);
		}
		else {
			std::string name = cur->get_name();
			name.back()++;
			cur->set_focused(0);
			if (visualizer.find_button(name)) visualizer.find_button(name)->set_focused(1);
			else {
				cur->set_focused(1);
				if (text_box_mode == INSERT || text_box_mode == ERASE) {
					std::string u = visualizer.find_button("TEXT_BOX_1")->get_string(),
						v = visualizer.find_button("TEXT_BOX_2")->get_string(),
						w = visualizer.find_button("TEXT_BOX_3")->get_string();
					if (u.size() && v.size() && w.size()) 
						text_box_receive(" " + u + " " + v + " " + w);
				}
				else {
					std::string u = visualizer.find_button("TEXT_BOX_1")->get_string(),
						v = visualizer.find_button("TEXT_BOX_2")->get_string();
					if (u.size() && v.size()) 
						text_box_receive(" " + u + " " + v);
				}
			}
		}
	}
	else {
		std::string cur = visualizer.get_focused_text_box()->get_string();
		cur = handle_text_input(cur);
		visualizer.get_focused_text_box()->set_string(cur);
	}
}

void handle_input(UIUnit &visualizer) {
	Button* cur = visualizer.check_hovering(input_state.get_mouse_pos());

	std::string pressed_button = "";
	sf::Vector2f mouse_pos = input_state.get_mouse_pos();
	if (input_state.get_mouse_state() == CLICK) {
		visualizer.click(mouse_pos);
		if (cur) pressed_button = cur->get_name();
	}

	if (menu_switcher(pressed_button)) {
		ds.reset_current();
		despawn_text_box(visualizer);

		anim.clear_graph();
		text_box_mode = NONE;
	}
	else if (command_activated(pressed_button)) 
		execute_command(command_activated(pressed_button));
	else if (visualizer.get_focused_text_box()) 
		handle_textbox_input(visualizer);
}

void handle_visualizing(sf::RenderWindow& appwindow, UIUnit& visualizer, MenuManager& menu_manager) {
	handle_ds_switcher();

	Button* text_box = visualizer.find_button("TEXT_BOX");
	if (text_box != nullptr && text_box->get_focused() == false) {
		despawn_text_box(visualizer);
		text_box_mode = NONE;
	}
	Button* form_box = visualizer.find_button("FORM");
	if (form_box != nullptr && form_box->get_focused() == false) {
		despawn_form(visualizer);
		text_box_mode = NONE;
	}

	visualizer.find_button("DS_NAME")->set_string(get_ds_name( ds.get_current_type() ));
	visualizer.find_button("COMMAND_3")->set_string((ds.is_drawing_ds())?"SEARCH":"RUN");

	handle_input(visualizer);

	if (anim.is_empty()) anim.update_graph();
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

	anim.update_timer(delta);

	switch (menu_manager.get_current_state()) {
	case MENU:
		menu.update_timer(delta);
		handle_menu(appwindow, menu, menu_manager);
		break;
	case SETTINGS:
		settings.update_timer(delta);
		handle_settings(appwindow, settings, menu_manager);
		break;
	case ABOUT:
		about.update_timer(delta);
		handle_about(appwindow, about, menu_manager);
		break;
	case VISUALIZING:
		visualizer.update_timer(delta);
		handle_visualizing(appwindow, visualizer, menu_manager);
		break;
	case SELECTION:
		selection.update_timer(delta);
		handle_selection(appwindow, selection, menu_manager);
		break;
	}
	
	appwindow.display();
}