
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
#include <Drawing/AnimationController.hpp>
#include <Drawing/Pseudocode.hpp>

#include <UI/MenuManager.hpp>
#include <UI/UIDesign.hpp>
#include <UI/UIUnit.hpp>

#include <Decoration/Background.hpp>
#include <Input/InputHandler.hpp>
#include <StateMachine/AppSetting.hpp>
#include <FileReader/FileHandler.hpp>


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

AppSetting appsex;

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
	Button* cur = settings.check_hovering(input_state.get_mouse_pos());
	if (input_state.get_mouse_state() == CLICK) {
		if (cur) {
			if (menu_switcher(cur->get_name()));
			else {
				if (cur->get_name() == "BACKGROUND_BUTTON") {
					appsex.next_background();
				}
				else if (cur -> get_name() == "ANIMATION_BUTTON") {
					appsex.next_speed();
				}
				else if (cur->get_name() == "BG_SPEED_BUTTON") {
					appsex.next_bg_speed();
				}
				else if (cur->get_name() == "INFO_DISPLAY_BUTTON") {
					appsex.next_info_display();
				}
			}
		}
	}
	settings.find_button("BACKGROUND_BUTTON")->set_string(BACKGROUND_NAMES[appsex.get_background()]);
	settings.find_button("ANIMATION_BUTTON")->set_string(SPEED_MODIFIER_NAMES[appsex.get_speed()]);
	settings.find_button("BG_SPEED_BUTTON")->set_string(BACKGROUND_SPEED_NAMES[appsex.get_bg_speed()]);
	settings.find_button("INFO_DISPLAY_BUTTON")->set_string(INFO_DISPLAY_NAMES[appsex.get_info_display()]);

	settings.draw(input_state.get_mouse_pos());
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
				anim.clear_graph();
			}
		}
	}
}

void handle_ds_switcher() {
	bool check1 = input_state.get_keyboard_key(LSHIFT) != RELEASE &&
		(input_state.get_keyboard_key(LEFT_ARROW) == CLICK ||
			input_state.get_keyboard_key(RIGHT_ARROW) == CLICK);

	std::string highlighted_button = "";
	if (visualizer.find_button("PREVIOUS")->get_focused()) highlighted_button = "PREVIOUS";
	if (visualizer.find_button("NEXT")->get_focused()) highlighted_button = "NEXT";
	bool check2 = (highlighted_button == "PREVIOUS")
		|| (highlighted_button == "NEXT");
	if (check1 || check2) {
		if (input_state.get_keyboard_key(LEFT_ARROW) == CLICK ||
			(highlighted_button == "PREVIOUS"))
			ds.previous_data_structure();
		else if (input_state.get_keyboard_key(RIGHT_ARROW) == CLICK ||
			(highlighted_button == "NEXT"))
			ds.next_data_structure();

		visualizer.find_button("PREVIOUS")->set_focused(0);
		visualizer.find_button("NEXT")->set_focused(0);

		despawn_text_box(visualizer);
		despawn_form(visualizer);
		text_box_mode = NONE; 
		anim.clear_graph();

		for (int i = 1; ; ++i) {
			Button* b = visualizer.find_button("COMMAND_" + std::string(1, '0' + i));
			if (b) b->set_focused(0);
			else break;
		}
	}
}


UserCommand command_activated(std::string command) {
	if (input_state.get_keyboard_key(KEY_L) == CLICK || command == "COMMAND_" + std::string(1, '0' + (int)LOAD)) return LOAD;
	if (command == "COMMAND_" + std::string(1, '0' + (int)INIT)) return INIT;
	if (input_state.get_keyboard_key(KEY_I) == CLICK || command == "COMMAND_" + std::string(1, '0' + (int)INSERT)) return INSERT;
	if (input_state.get_keyboard_key(KEY_E) == CLICK || command == "COMMAND_" + std::string(1, '0' + (int)ERASE)) return ERASE;
	if (input_state.get_keyboard_key(KEY_S) == CLICK || command == "COMMAND_" + std::string(1, '0' + (int)SEARCH)) return SEARCH;
	if (input_state.get_keyboard_key(KEY_P) == CLICK || command == "COMMAND_" + std::string(1, '0' + (int)CLEAR)) return CLEAR;
	if (ds.get_current_type() == LINKED_LIST &&
		(input_state.get_keyboard_key(KEY_U) == CLICK || command == "COMMAND_" + std::string(1, '0' + (int)UPDATE))) return UPDATE;
	return NONE;
}

void text_box_receive(std::string s);
void execute_command(UserCommand command) {
	std::cout << "Command activated: " << command << std::endl;
	despawn_text_box(visualizer);
	despawn_form(visualizer);

	for (int i = 1; ; ++i) {
		Button* b = visualizer.find_button("COMMAND_" + std::string(1, '0' + i));
		if (b) b->set_focused(0);
		else break;
	}
	visualizer.find_button("COMMAND_" + std::string(1, '0' + command))->set_focused(1);
	if (command == CLEAR) {
		anim.clear_current_ds();
		return;
	}
	if (command == LOAD) {
		std::string loaded = loadTextFile();
		if (loaded.size()) {
			text_box_mode = (UserCommand)INIT;
			std::string input = "";
			for (char i : loaded) {
				if (i == ' ' || i == '\n' || ('0' <= i && i <= '9')) 
					input.push_back(i);
				else input.push_back('\n');
			}
			text_box_receive(input);
		}
		return;
	}
	if (ds.is_drawing_ds()) {
		if (command == UPDATE) {
			spawn_form(visualizer, 2, "INPUT YOUR UPDATE");
			text_box_mode = UPDATE;
		}
		else {
			spawn_text_box(visualizer, (UserCommand)command);
			text_box_mode = (UserCommand)command;
		}
	}
	else {
		if (command == INIT) {
			spawn_text_box(visualizer, (UserCommand)command);
			text_box_mode = (UserCommand)command;
		}
		else if (command == INSERT || command == ERASE) {
			spawn_form(visualizer, 3, "INPUT YOUR EDGE");
			text_box_mode = (UserCommand)command;
		}
		else {
			if (ds.get_current_type() == KRUSKAL)
				anim.load_kruskal();
			else {
				spawn_form(visualizer, 2, "INPUT YOUR QUERY");
				text_box_mode = SEARCH;
			}
		}
	}
}

int control_activated(std::string s) {
	if (s.substr(0, 11) == "CONTROLFLOW") {
		return s.back() - '0';
	}
	return 0;
}

void execute_control(int control) {
	for (int i = 1; ; ++i) {
		Button* b = visualizer.find_button("CONTROLFLOW" + std::string(1, '0' + i));
		if (b) b->set_focused(0);
		else break;
	}
	switch (control) {
	case 1:
		anim.jump_to_back();
		break;
	case 2:
		anim.jump_back();
		break;
	case 3:
		anim.toggle_flow();
		break;
	case 4:
		anim.jump_front();
		break;
	case 5:
		anim.jump_to_front();
		break;
	}
}

void text_box_receive(std::string s) {
	if (text_box_mode == NONE) debug_error("text box mode is NONE, yet text_box_receive was called");
	if (text_box_mode == INIT) {
		anim.handle_init(s);
	}
	else if (text_box_mode == INSERT) 
		anim.handle_insertion(s);
	else if (text_box_mode == ERASE) 
		anim.handle_deletion(s);
	else if (text_box_mode == SEARCH) {
		if (ds.is_drawing_ds()) {
			anim.handle_search(s);
		}
		else {
			std::vector<std::string> cur = split(s);
			if (cur.size() != 2) debug_error("not exactly 2 strings when calling RUN");
			anim.load_dijkstra(cur[0], cur[1]);
		}
	}
	else if (text_box_mode == UPDATE) {
		std::vector<std::string> cur = split(s);
		if (cur.size() != 2) debug_error("not exactly 2 strings when calling UPDATE");
		anim.handle_update(cur[0], cur[1]);
	}
	despawn_text_box(visualizer);
	despawn_form(visualizer);
	text_box_mode = NONE;
}

bool received_text_input() {
	if (text_box_mode == NONE) debug_error("received text input while there are no textbox");
	if (input_state.get_keyboard_key(KEY_V) == CLICK && input_state.get_keyboard_key(LCTRL) != RELEASE)
		return true;
	if (input_state.get_keyboard_key(BACKSPACE) == CLICK) return true;
	for (int j = 0; j < 10; ++j) {
		if (input_state.get_keyboard_key((InputKey)((int)ZERO + j)) == CLICK)
			return true;
	}
	if (text_box_mode == INIT) {
		if (input_state.get_keyboard_key(SPACE) == CLICK) return true;
		if (input_state.get_keyboard_key(ENTER) == CLICK) return true;
	}

	return false;
}

std::string handle_text_input(std::string cur) {
	if (input_state.get_keyboard_key(KEY_V) == CLICK && input_state.get_keyboard_key(LCTRL) != RELEASE) {
		sf::String pastedText = sf::Clipboard::getString();
		std::string parge = (std::string)pastedText;
		if (parge.size()) {
			if (text_box_mode != INIT) cur.clear();
			std::vector<std::string> s = split(" " + parge);
			for (auto i : s) if (i.size()) {
				if (i.size() > 4) i.resize(4);
				if (cur.size() && cur.back() != ' ') cur.push_back(' ');
				cur += i;

				if (text_box_mode != INIT) break;
			}
		}
	}
	if (input_state.get_keyboard_key(BACKSPACE) == CLICK) {
		if (input_state.get_keyboard_key(LCTRL) == RELEASE) {
			if (cur.size()) cur.pop_back();
		}
		else {
			if (cur.size()) cur.pop_back();
			while (cur.size() && cur.back() != ' ' && cur.back() != '\n') cur.pop_back();
		}
	}
	else if (text_box_mode == INIT && input_state.get_keyboard_key(SPACE) == CLICK) {
		if (cur.size() && cur.back() != ' ') cur.push_back(' ');
	}
	else if (text_box_mode == INIT && input_state.get_keyboard_key(ENTER) == CLICK) {
		cur.push_back('\n');
	}
	else {
		for (int j = 0; j < 10; ++j) {
			InputKey current = (InputKey)((int)ZERO + j);
			if (input_state.get_keyboard_key(current) == CLICK) {
				cur.push_back('0' + j);
				if (check_valid_string(cur) == false) cur.pop_back();
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
	else if (text_box_mode == INIT && (input_state.get_keyboard_key(ENTER) == CLICK) 
		&& (input_state.get_keyboard_key(LSHIFT) != RELEASE)) {
		std::string s = cur->get_string();
		if (s.size()) text_box_receive(s);
	}
	else if (received_text_input()){
		std::string cur = visualizer.get_focused_text_box()->get_string();
		cur = handle_text_input(cur);
		visualizer.get_focused_text_box()->set_string(cur);
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
		if (cur -> get_name() == "TEXT_BOX") {
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
				std::string ans = "";
				bool valid = true;
				for (int i = 1; ; ++i) {
					Button* cur = visualizer.find_button("TEXT_BOX_" + std::string(1, '0' + i));
					if (cur == nullptr) break;
					ans += " " + cur->get_string();
					if (cur->get_string().empty()) valid = false;
				}
				if (valid) text_box_receive(ans);
			}
		}
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
	else if (control_activated(pressed_button))
		execute_control(control_activated(pressed_button));
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
	visualizer.find_button("COMMAND_" + std::string(1, '0' + (int) SEARCH))->set_string((ds.is_drawing_ds()) ? "SEARCH" : "RUN");
	visualizer.find_button("COMMAND_" + std::string(1, '0' + (int) UPDATE))->set_visibility(ds.get_current_type() == LINKED_LIST);

	visualizer.find_button("CONTROLFLOW3")->set_string(
		(anim.get_flow()) ? "||" : "[>]"
	);

	handle_input(visualizer);

	if (anim.is_empty()) anim.update_graph();
	drawing_unit.draw_viz_state(anim.get_state(), appsex.get_info_display());
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
	delta *= SPEED_MODIFIER[appsex.get_speed()];
	bg_drawer.draw(input_state.get_mouse_pos(), appsex.get_background(), 
		delta * BACKGROUND_SPEED[appsex.get_bg_speed()]);

	input_state.update_mouse(delta);
	input_state.update_keyboard(delta);

	anim.update_timer(delta);

	if (input_state.get_keyboard_key(KEY_L) == CLICK) {
		loadTextFile();
	}

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