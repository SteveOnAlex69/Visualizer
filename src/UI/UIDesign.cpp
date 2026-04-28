#include <UI/UIDesign.hpp>


Button* add_text(UIUnit& menu, sf::Vector2f pos, int text_size, 
	Alignment align_type, Alignment rel_pos, std::string name, std::string text) {
	Button* cur = new Button();
	cur->set_button_pos(pos);
	cur->set_font_size(text_size);
	cur->set_alignment(align_type);
	cur->set_relative_pos(rel_pos);
	cur->set_name(name);
	cur->set_string(text);
	cur->set_button_type(TEXT);
	cur->set_bg_color(sf::Color::Transparent);
	cur->set_font_color(FIRST_COLOR);
	cur->set_font_accent_color(SECOND_COLOR);
	menu.add_element(cur);
	return cur;
}

Button* add_button(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size, 
	int text_size, Alignment align_type, Alignment rel_pos,
	std::string name, std::string text) {
	Button* cur = new Button();
	cur->set_button_pos(pos);
	cur->set_button_size(size);
	cur->set_font_size(text_size);
	cur->set_alignment(align_type);
	cur->set_relative_pos(rel_pos);
	cur->set_name(name);
	cur->set_string(text);
	cur->set_button_type(BUTTON);
	cur->set_bg_color(BACKGROUND);
	cur->set_font_color(FIRST_COLOR);
	cur->set_font_accent_color(SECOND_COLOR);
	menu.add_element(cur);
	return cur;
}


Button* add_button_with_texture(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size,Alignment align_type, Alignment rel_pos,
	std::string name, std::string path) {
	Button* cur = new Button(path);
	cur->set_button_pos(pos);
	cur->set_button_size(size);
	cur->set_alignment(align_type);
	cur->set_relative_pos(rel_pos);
	cur->set_name(name);
	cur->set_button_type(BUTTON);
	cur->set_bg_color(BACKGROUND);
	cur->set_font_color(FIRST_COLOR);
	cur->set_font_accent_color(SECOND_COLOR);
	menu.add_element(cur);
	return cur;
}

Button* add_text_box(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size,
	int text_size, Alignment align_type, Alignment rel_pos,
	std::string name) {
	Button* cur = new Button();
	cur->set_button_pos(pos);
	cur->set_button_size(size);
	cur->set_font_size(text_size);
	cur->set_alignment(align_type);
	cur->set_relative_pos(rel_pos);
	cur->set_name(name);
	cur->set_button_type(TEXTBOX);
	cur->set_bg_color(BACKGROUND);
	cur->set_font_color(FIRST_COLOR);
	cur->set_font_accent_color(SECOND_COLOR);
	menu.add_element(cur);
	return cur;
}


Button* add_rectangle(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size,
	int text_size, Alignment align_type, Alignment rel_pos,
	std::string name, std::string text) {
	Button* cur = new Button();
	cur->set_button_pos(pos);
	cur->set_button_size(size);
	cur->set_font_size(text_size);
	cur->set_alignment(align_type);
	cur->set_relative_pos(rel_pos);
	cur->set_name(name);
	cur->set_string(text);
	cur->set_button_type(RECTANGLE);
	cur->set_bg_color(BACKGROUND);
	cur->set_font_color(FIRST_COLOR);
	cur->set_font_accent_color(SECOND_COLOR);
	menu.add_element(cur);
	return cur;
}

void setup_menu(UIUnit& menu) {
	// set up menu
	Button* title = 
		add_text(menu, sf::Vector2f(0, -300), 100, CENTER_CENTER, CENTER_CENTER, "TITLE", "DATA VISUALIZER");
	title->set_transition_type(DOWN);
	title->set_transition_strength(10);

	add_text(menu, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");

	Button* start = add_button(menu, sf::Vector2f(0, -100), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"START", "START");
	Button* settings = add_button(menu, sf::Vector2f(0, 10), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"SETTINGS", "SETTINGS");
	Button* about = add_button(menu, sf::Vector2f(0, 120), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"ABOUT", "ABOUT");
	Button* quit = add_button(menu, sf::Vector2f(0, 230), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"QUIT", "QUIT");

	start->set_transition_type(UP);
	start->set_transition_strength(7);
	settings->set_transition_type(UP);
	settings->set_transition_strength(6);
	about->set_transition_type(UP);
	about->set_transition_strength(5);
	quit->set_transition_type(UP);
	quit->set_transition_strength(4);
}

void setup_about(UIUnit& about) {
	// set up about

	Button* bottom_text = add_text(about, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");

	Button* back = add_button(about, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	Button* settings = add_button(about, sf::Vector2f(-50, 50), sf::Vector2f(200, 60), 26,
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");

	Button* about_text = add_text(about, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER,
		"ABOUT", "ABOUT");

	back->set_transition_type(LEFT);
	settings->set_transition_type(RIGHT);
	about_text->set_transition_type(RIGHT);
	back->set_transition_strength(7);
	settings->set_transition_strength(7);
	about_text->set_transition_strength(7);

	const int PAGE_COUNT = 5;
	for (int i = 0; i < PAGE_COUNT; ++i) {
		Button* about_page = add_button_with_texture(about, sf::Vector2f(screen_center.x * 2 * i, 0), sf::Vector2f(1225, 725),
			CENTER_CENTER, CENTER_CENTER, "PAGE" + std::string(1, '1' + i), ART_PATH + "page" + std::string(1, '1' + i) + ".png");
		Button* dot = add_button(about, sf::Vector2f(0, 500), sf::Vector2f(0, 0), 67, CENTER_CENTER, CENTER_CENTER,
			"DOT" + std::string(1, '1' + i), ".");
	}

	Button* next_page = add_button(about, sf::Vector2f(-10, 0), sf::Vector2f(200, 50), 80, CENTER_RIGHT, CENTER_RIGHT,
		"NEXT_PAGE", "[>]");
	next_page->set_border_width(0);
	next_page->set_justify_content(CENTER_RIGHT);

	Button* previous_page = add_button(about, sf::Vector2f(10, 0), sf::Vector2f(200, 50), 80, CENTER_LEFT, CENTER_LEFT,
		"PREV_PAGE", "[<]");
	previous_page->set_border_width(0);
	previous_page->set_justify_content(CENTER_LEFT);
}

void setup_settings(UIUnit& settings) {
	// set up settings
	Button* back = add_button(settings, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	Button* settings_title = add_text(settings, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER, "SETTINGS", "SETTINGS");


	back->set_transition_type(LEFT);
	settings_title->set_transition_type(DOWN);
	back->set_transition_strength(7);
	settings_title->set_transition_strength(7);

	Button* bg_text = add_text(settings, sf::Vector2f(-50, -200), 36, CENTER_CENTER, CENTER_CENTER,
		"BACKGROUND_TEXT", "Background:");
	bg_text->set_justify_content(CENTER_RIGHT);
	Button* animation_text = add_text(settings, sf::Vector2f(-50, -100), 36, CENTER_CENTER, CENTER_CENTER,
		"ANIMATION_TEXT", "Animation Speed:");
	animation_text->set_justify_content(CENTER_RIGHT);
	Button* bg_speed_text = add_text(settings, sf::Vector2f(-50, 0), 36, CENTER_CENTER, CENTER_CENTER,
		"BG_SPEED_TEXT", "Background Speed:");
	bg_speed_text->set_justify_content(CENTER_RIGHT);
	Button* info_text = add_text(settings, sf::Vector2f(-50, 100), 36, CENTER_CENTER, CENTER_CENTER,
		"INFO_DISPLAY_TEXT", "Display Info:");
	info_text->set_justify_content(CENTER_RIGHT);
	Button* pseudocode_text = add_text(settings, sf::Vector2f(-50, 200), 36, CENTER_CENTER, CENTER_CENTER,
		"PSEUDOCODE_DISPLAY_TEXT", "Display Pseudocode:");
	pseudocode_text->set_justify_content(CENTER_RIGHT);

	Button* bg_button = add_button(settings, sf::Vector2f(50, -200), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"BACKGROUND_BUTTON", "Starry Sky");
	bg_button->set_border_width(0);
	Button* animation_button = add_button(settings, sf::Vector2f(50, -100), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"ANIMATION_BUTTON", "1x");
	animation_button->set_border_width(0);
	Button* bg_speed_button = add_button(settings, sf::Vector2f(50, 0), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"BG_SPEED_BUTTON", "1x");
	bg_speed_button->set_border_width(0);
	Button* info_button = add_button(settings, sf::Vector2f(50, 100), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"INFO_DISPLAY_BUTTON", "Yes");
	info_button->set_border_width(0);
	Button* pseudocode_button = add_button(settings, sf::Vector2f(50, 200), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"PSEUDOCODE_DISPLAY_BUTTON", "Yes");
	pseudocode_button->set_border_width(0);

	bg_text->set_transition_type(LEFT);
	animation_text->set_transition_type(LEFT);
	bg_speed_text->set_transition_type(LEFT);
	info_text->set_transition_type(LEFT);
	pseudocode_text->set_transition_type(LEFT);

	bg_button->set_transition_type(RIGHT);
	animation_button->set_transition_type(RIGHT);
	bg_speed_button->set_transition_type(RIGHT);
	info_button->set_transition_type(RIGHT);
	pseudocode_button->set_transition_type(RIGHT);

	Button* bottom_text = add_text(settings, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
}

void setup_visualizer(UIUnit& visualizer) {
	// set up visualizer
	Button* select = add_button(visualizer, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26,
		TOP_LEFT, TOP_LEFT, "SELECT", "SELECT");
	Button* settings = add_button(visualizer, sf::Vector2f(-50, 50), sf::Vector2f(200, 60), 26,
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");

	Button* visualizer_text = add_text(visualizer, sf::Vector2f(0, -500), 100,
		CENTER_CENTER, CENTER_CENTER, "VISUALIZER", "VISUALIZER");


	Button* ds_name = add_text(visualizer, sf::Vector2f(0, 200), 36,
		CENTER_CENTER, TOP_CENTER, "DS_NAME", "nil");

	select->set_transition_type(LEFT);
	settings->set_transition_type(RIGHT);
	visualizer_text->set_transition_type(DOWN);
	select->set_transition_strength(7);
	settings->set_transition_strength(7);
	visualizer_text->set_transition_strength(7);

	ds_name->set_transition_type(DOWN);
	ds_name->set_transition_strength(10);

	Button* command_1 = add_button(visualizer, sf::Vector2f(30, 460), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_1", "LOAD");
	Button* command_2 = add_button(visualizer, sf::Vector2f(30, 540), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_2", "INIT");
	Button* command_3 = add_button(visualizer, sf::Vector2f(30, 620), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_3", "INSERT");
	Button* command_4 = add_button(visualizer, sf::Vector2f(30, 700), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_4", "ERASE");
	Button* command_5 = add_button(visualizer, sf::Vector2f(30, 780), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_5", "SEARCH");
	Button* command_6 = add_button(visualizer, sf::Vector2f(30, 860), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_6", "CLEAR");
	Button* command_7 = add_button(visualizer, sf::Vector2f(30, 940), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_7", "UPDATE");

	command_1->set_transition_type(LEFT);
	command_2->set_transition_type(LEFT);
	command_3->set_transition_type(LEFT);
	command_4->set_transition_type(LEFT);
	command_5->set_transition_type(LEFT);
	command_6->set_transition_type(LEFT);
	command_7->set_transition_type(LEFT);

	Button* prev_button = add_button(visualizer, sf::Vector2f(30, -30), sf::Vector2f(200, 50), 20, BOTTOM_LEFT, BOTTOM_LEFT,
		"PREVIOUS", "Previous");
	prev_button->set_border_width(0);
	prev_button->set_justify_content(CENTER_LEFT);
	Button* next_button = add_button(visualizer, sf::Vector2f(-30, -30), sf::Vector2f(200, 50), 20, BOTTOM_RIGHT, BOTTOM_RIGHT,
		"NEXT", "Next");
	next_button->set_border_width(0);
	next_button->set_justify_content(CENTER_RIGHT);

	prev_button->set_transition_type(UP);
	next_button->set_transition_type(UP);


	Button* toggle_pseudocode = add_button(visualizer, sf::Vector2f(-10, 0), sf::Vector2f(200, 50), 40, CENTER_RIGHT, CENTER_RIGHT,
		"TOGGLE_PSEUDOCODE", "<");
	toggle_pseudocode->set_border_width(0);
	toggle_pseudocode->set_justify_content(CENTER_RIGHT);


	std::string vcl[] = { "<<", "<", "||", ">", ">>" };

	for (int i = 1; i <= 5; ++i) {
		Button* BUTTON = add_button(visualizer, sf::Vector2f((i - 3) * 170, -50), sf::Vector2f(150, 60), 50, BOTTOM_CENTER, BOTTOM_CENTER,
			"CONTROLFLOW" + std::string(1, i + '0'), vcl[i - 1]);
		BUTTON->set_border_width(0);
		BUTTON->set_justify_content(CENTER_CENTER);
		BUTTON->set_transition_type(UP);
	}

	Button* SPEED = add_button(visualizer, sf::Vector2f(-3 * 170, -50), sf::Vector2f(150, 60), 40, BOTTOM_CENTER, BOTTOM_CENTER,
		"CONTROLFLOW6", "1x");
	SPEED->set_border_width(0);
	SPEED->set_justify_content(CENTER_CENTER);
	SPEED->set_transition_type(UP);


	Button* TIMELINE = add_text(visualizer, sf::Vector2f(3 * 170, -50), 25, BOTTOM_CENTER, BOTTOM_CENTER,
		"TIMELINE", "0/0s");
	TIMELINE->set_justify_content(CENTER_CENTER);
	TIMELINE->set_transition_type(UP);

	Button* bottom_text = add_text(visualizer, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
}
void setup_selection(UIUnit& selection) {
	Button* back = add_button(selection, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26,
		TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	Button* settings = add_button(selection, sf::Vector2f(-50, 50), sf::Vector2f(200, 60), 26,
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");
	Button* selection_text = add_text(selection, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER, "SELECT", "SELECT YOUR DATA");

	back->set_transition_type(LEFT);
	settings->set_transition_type(RIGHT);
	selection_text->set_transition_type(DOWN);

	back->set_transition_strength(7);
	settings->set_transition_strength(7);
	selection_text->set_transition_strength(7);

	Button* bottom_text = add_text(selection, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");

	Button* data1 = add_button_with_texture(selection, sf::Vector2f(-650, -100), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA1", ART_PATH + "LinkedList.png");
	Button* data2 = add_button_with_texture(selection, sf::Vector2f(0, -100), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA2", ART_PATH + "HashMap.png");
	Button* data3 = add_button_with_texture(selection, sf::Vector2f(650, -100), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA3", ART_PATH + "AVLTree.png");

	Button* data4 = add_button_with_texture(selection, sf::Vector2f(-650, 300), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA4", ART_PATH + "Trie.png");
	Button* data5 = add_button_with_texture(selection, sf::Vector2f(0, 300), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA5", ART_PATH + "Kruskal.png");
	Button* data6 = add_button_with_texture(selection, sf::Vector2f(650, 300), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA6", ART_PATH + "Dijkstra.png");

	data1->set_transition_type(UP);
	data2->set_transition_type(UP);
	data3->set_transition_type(UP);
	data4->set_transition_type(UP);
	data5->set_transition_type(UP);
	data6->set_transition_type(UP);


	data1->set_transition_strength(6);
	data2->set_transition_strength(6);
	data3->set_transition_strength(6);
	data4->set_transition_strength(4);
	data5->set_transition_strength(4);
	data6->set_transition_strength(4);
}



void spawn_text_box(UIUnit& scene, UserCommand user_command) {
	despawn_text_box(scene);

	if (user_command == INIT) {
		Button* lmao = add_text_box(scene, sf::Vector2f(220, 540), sf::Vector2f(300, 400), 23,
				TOP_LEFT, TOP_LEFT, "TEXT_BOX");
		lmao->set_justify_content(TOP_LEFT);
		lmao->set_focused(1);
		lmao->set_line_width(20);


		Button* command_8 = add_button(scene, sf::Vector2f(220, 980), sf::Vector2f(125, 50), 23, TOP_LEFT, TOP_LEFT,
			"COMMAND_8", "RANDOM");
		Button* command_9 = add_button(scene, sf::Vector2f(395, 980), sf::Vector2f(125, 50), 23, TOP_LEFT, TOP_LEFT,
			"COMMAND_9", "SUBMIT");

	}
	else {
		sf::Vector2f pos = sf::Vector2f(220, 620);
		if (user_command == ERASE) pos += sf::Vector2f(0, 80);
		if (user_command == SEARCH) pos += sf::Vector2f(0, 160);
		Button* lmao = add_text_box(scene, pos, sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT, "TEXT_BOX");
		lmao->set_focused(1);
	}

}

void despawn_text_box(UIUnit& scene) {
	scene.erase_element(scene.find_button("TEXT_BOX"));
	scene.erase_element(scene.find_button("COMMAND_8"));
	scene.erase_element(scene.find_button("COMMAND_9"));
}

void spawn_message_box(UIUnit& scene, std::string message) {
	despawn_message_box(scene);
	add_button(scene, sf::Vector2f(0, -50), sf::Vector2f(200 + message.size() * 15, 60), 26, BOTTOM_CENTER, BOTTOM_CENTER,
		"MESSAGE", message);
}
void despawn_message_box(UIUnit& scene) {
	scene.erase_element(scene.find_button("MESSAGE"));
}

void spawn_form(UIUnit& scene, int text_field_count, std::string name) {
	despawn_form(scene);
	Button* form = add_rectangle(scene, sf::Vector2f(0, 0), sf::Vector2f(500, 200), 0, CENTER_CENTER, CENTER_CENTER,
		"FORM", "");
	form->set_focused(1);

	add_text(scene, sf::Vector2f(0, -50), 50, CENTER_CENTER, CENTER_CENTER,
		"FORM_TITLE", name);

	if (text_field_count < 1) assert(false);
	sf::Vector2f ROOT(20, 50);
	ROOT -= sf::Vector2f(80, 0) * (1.0f * text_field_count);

	for (int i = 1; i <= text_field_count; ++i) {
		std::string lmao = "u:";
		lmao[0] += i - 1;
		add_text(scene, ROOT, 26, CENTER_CENTER, CENTER_CENTER,
			"TEXT_" + std::string(1, '0' + i), lmao);
		ROOT += sf::Vector2f(80, 0);
		add_text_box(scene, ROOT, sf::Vector2f(60, 40), 26, CENTER_CENTER, CENTER_CENTER,
			"TEXT_BOX_" + std::string(1, '0' + i));
		ROOT += sf::Vector2f(80, 0);
	}

	scene.find_button("TEXT_BOX_1")->set_focused(1);
}

void despawn_form(UIUnit& scene) {
	if (scene.erase_element(scene.find_button("FORM")) == false)
		return;
	scene.erase_element(scene.find_button("FORM_TITLE"));

	for (int i = 1; ; ++i) {
		if (scene.erase_element(scene.find_button("TEXT_" + std::string(1, '0' + i))) == false)
			break;
		scene.erase_element(scene.find_button("TEXT_BOX_" + std::string(1, '0' + i)));
	}
}