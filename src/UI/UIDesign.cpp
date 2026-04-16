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
	int text_size, Alignment align_type, Alignment rel_pos, std::string name) {
	Button* cur = new Button();
	cur->set_button_pos(pos);
	cur->set_button_size(size);
	cur->set_font_size(text_size);
	cur->set_alignment(align_type);
	cur->set_relative_pos(rel_pos);
	cur->set_name(name);
	cur->set_string("");
	cur->set_button_type(TEXTBOX);
	cur->set_bg_color(BACKGROUND);
	cur->set_font_color(FIRST_COLOR);
	cur->set_font_accent_color(SECOND_COLOR);
	menu.add_element(cur);
	return cur;
}

void setup_menu(UIUnit& menu) {
	// set up menu
	add_text(menu, sf::Vector2f(0, -300), 100, CENTER_CENTER, CENTER_CENTER, "TITLE", "DATA VISUALIZER");
	add_text(menu, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
	add_button(menu, sf::Vector2f(0, -100), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"START", "START");
	add_button(menu, sf::Vector2f(0, 10), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"SETTINGS", "SETTINGS");
	add_button(menu, sf::Vector2f(0, 120), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"ABOUT", "ABOUT");
	add_button(menu, sf::Vector2f(0, 230), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"QUIT", "QUIT");
}


void setup_about(UIUnit& about) {
	// set up about

	add_text(about, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");

	add_button(about, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	add_button(about, sf::Vector2f(-50, 50), sf::Vector2f(200, 60), 26,
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");


	add_text(about, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER, 
		"ABOUT", "ABOUT");

	std::vector<std::string> lines;
	lines.push_back("This project (Data structure visualizer) was made by Le Kien Thanh - 25125035");
	lines.push_back("My nickname is steveonalex");
	lines.push_back("This was created on 31st of March.");
	lines.push_back("It's just a random college project.");
	lines.push_back("I procrastinated this like crazy. Life is tough");
	lines.push_back("At least we managed to push this out, cool I guess.");
	lines.push_back("===========");
	lines.push_back("HOW TO USE:");
	lines.push_back("There are five data structures, namely AVL Tree, BST, Trie, Linked List and Hash map");
	lines.push_back("You can insert, erase, or search for an element and see what happens.");
	lines.push_back("That's it!");
	lines.push_back("===========");
	lines.push_back("DEV LOGS:");
	lines.push_back("1 month before deadlines: nothing");
	lines.push_back("1 week before deadlines: implemented the data structures");
	lines.push_back("3 days before deadlines: adding the option system");
	lines.push_back("2 days before deadlines: redesigning the entire project");
	lines.push_back("===========");
	lines.push_back("QUOTE OF THE DAY:");
	lines.push_back("\"In my next magic trick, I will code a project worth half my grade in 2 hours.\"");
	for (int i = 0; i < (int)lines.size(); ++i) {
		sf::Vector2f po(0, 200);
		po += sf::Vector2f(0, 36) * (i * 1.0f);
		add_text(about, po, 30, CENTER_CENTER, TOP_CENTER, "AHH", lines[i]);
	}
}

void setup_settings(UIUnit& settings) {
	// set up settings
	add_button(settings, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	add_text(settings, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER, "SETTINGS", "SETTINGS");

	Button* bg_text = add_text(settings, sf::Vector2f(-50, -200), 36, CENTER_CENTER, CENTER_CENTER, 
		"BACKGROUND_TEXT", "Background:");
	bg_text->set_justify_content(CENTER_RIGHT);

	Button* animation_text = add_text(settings, sf::Vector2f(-50, -100), 36, CENTER_CENTER, CENTER_CENTER,
		"ANIMATION_TEXT", "Animation Speed:");
	animation_text->set_justify_content(CENTER_RIGHT);

	Button* bg_button = add_button(settings, sf::Vector2f(50, -200), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"BACKGROUND_BUTTON", "Starry Sky");
	bg_button->set_border_width(0);

	Button* animation_button = add_button(settings, sf::Vector2f(50, -100), sf::Vector2f(200, 50), 36, CENTER_LEFT, CENTER_CENTER,
		"ANIMATION_BUTTON", "1x");
	animation_button->set_border_width(0);

	add_text(settings, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
}


void setup_selection(UIUnit& selection) {
	add_button(selection, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26,
		TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	add_button(selection, sf::Vector2f(-50, 50), sf::Vector2f(200, 60), 26,
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");
	add_text(selection, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER, "SELECT", "SELECT YOUR DATA");

	add_text(selection, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");


	add_button_with_texture(selection, sf::Vector2f(-650, -100), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA1", ART_PATH + "LinkedList.png");
	add_button_with_texture(selection, sf::Vector2f(0, -100), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA2", ART_PATH + "HashMap.png");
	add_button_with_texture(selection, sf::Vector2f(650, -100), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA3", ART_PATH + "AVLTree.png");

	add_button_with_texture(selection, sf::Vector2f(-650, 300), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA4", ART_PATH + "Trie.png");
	add_button_with_texture(selection, sf::Vector2f(0, 300), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA5", ART_PATH + "Kruskal.png");
	add_button_with_texture(selection, sf::Vector2f(650, 300), sf::Vector2f(571, 352),
		CENTER_CENTER, CENTER_CENTER, "DATA6", ART_PATH + "Dijkstra.png");
}

void setup_visualizer(UIUnit& visualizer) {
	// set up visualizer
	add_button(visualizer, sf::Vector2f(50, 50), sf::Vector2f(200, 60), 26,
		TOP_LEFT, TOP_LEFT, "SELECT", "SELECT");
	add_button(visualizer, sf::Vector2f(-50, 50), sf::Vector2f(200, 60), 26,
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");

	add_text(visualizer, sf::Vector2f(0, -500), 100, 
		CENTER_CENTER, CENTER_CENTER, "VISUALIZER", "VISUALIZER");

	add_button(visualizer, sf::Vector2f(30, 540), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_1", "INIT");
	add_button(visualizer, sf::Vector2f(30, 620), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT, 
		"COMMAND_2", "INSERT");
	add_button(visualizer, sf::Vector2f(30, 700), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_3", "ERASE");
	add_button(visualizer, sf::Vector2f(30, 780), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_4", "SEARCH");
	add_button(visualizer, sf::Vector2f(30, 860), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_5", "CLEAR");
	add_button(visualizer, sf::Vector2f(30, 940), sf::Vector2f(150, 50), 23, TOP_LEFT, TOP_LEFT,
		"COMMAND_6", "UPDATE");



	Button* nigger1 = add_button(visualizer, sf::Vector2f(30, -30), sf::Vector2f(200, 50), 20, BOTTOM_LEFT, BOTTOM_LEFT,
		"PREVIOUS", "Previous");
	nigger1 -> set_border_width(0);
	nigger1->set_justify_content(CENTER_LEFT);
	Button* nigger2 = add_button(visualizer, sf::Vector2f(-30, -30), sf::Vector2f(200, 50), 20, BOTTOM_RIGHT, BOTTOM_RIGHT,
		"NEXT", "Next");
	nigger2->set_border_width(0);
	nigger2->set_justify_content(CENTER_RIGHT);

	std::string vcl[] = {"<<", "<", "||", ">", ">>"};

	for (int i = 1; i <= 5; ++i) {
		Button* BUTTON = add_button(visualizer, sf::Vector2f((i-3) * 170, -50), sf::Vector2f(150, 60), 50, BOTTOM_CENTER, BOTTOM_CENTER,
			"CONTROLFLOW" + std::string(1, i + '0'), vcl[i-1]);
		BUTTON->set_border_width(0);
		BUTTON->set_justify_content(CENTER_CENTER);
	}

	add_text(visualizer, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
}



void spawn_text_box(UIUnit& scene, UserCommand user_command) {
	despawn_text_box(scene);

	if (user_command == INIT) {
		Button* lmao = add_text_box(scene, sf::Vector2f(220, 540), sf::Vector2f(300, 400), 23,
				TOP_LEFT, TOP_LEFT, "TEXT_BOX");
		lmao->set_justify_content(TOP_LEFT);
		lmao->set_focused(1);
		lmao->set_line_width(20);
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
	Button* form = add_button(scene, sf::Vector2f(0, 0), sf::Vector2f(500, 200), 0, CENTER_CENTER, CENTER_CENTER,
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