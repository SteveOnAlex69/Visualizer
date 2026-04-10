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
	add_button(menu, sf::Vector2f(0, 0), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"SETTINGS", "SETTINGS");
	add_button(menu, sf::Vector2f(0, 100), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"ABOUT", "ABOUT");
	add_button(menu, sf::Vector2f(0, 200), sf::Vector2f(300, 80), 36, CENTER_CENTER, CENTER_CENTER,
		"QUIT", "QUIT");
}


void setup_about(UIUnit& about) {
	// set up about

	add_text(about, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");

	add_button(about, sf::Vector2f(30, 30), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	add_button(about, sf::Vector2f(-30, 30), sf::Vector2f(200, 60), 26, 
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
	add_button(settings, sf::Vector2f(30, 30), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	add_text(settings, sf::Vector2f(0, -500), 100, CENTER_CENTER, CENTER_CENTER, "SETTINGS", "SETTINGS");


	add_text(settings, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
}

void setup_visualizer(UIUnit& visualizer) {
	// set up visualizer
	add_button(visualizer, sf::Vector2f(30, 30), sf::Vector2f(200, 60), 26, 
		TOP_LEFT, TOP_LEFT, "BACK", "BACK");
	add_button(visualizer, sf::Vector2f(-30, 30), sf::Vector2f(200, 60), 26, 
		TOP_RIGHT, TOP_RIGHT, "SETTINGS", "SETTINGS");


	add_text(visualizer, sf::Vector2f(0, -500), 100, 
		CENTER_CENTER, CENTER_CENTER, "VISUALIZER", "VISUALIZER");

	add_button(visualizer, sf::Vector2f(30, 700), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, 
		"COMMAND_1", "INSERT");
	add_button(visualizer, sf::Vector2f(30, 790), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT,
		"COMMAND_2", "ERASE");
	add_button(visualizer, sf::Vector2f(30, 880), sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, 
		"COMMAND_3", "SEARCH");


	add_text(visualizer, sf::Vector2f(0, -10), 20, BOTTOM_CENTER, BOTTOM_CENTER,
		"BOTTOM_TEXT",
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
}

std::string spawn_text_box(UIUnit& scene, std::string category) {
	sf::Vector2f pos = sf::Vector2f(250, 700);
	if (category == "ERASE") pos += sf::Vector2f(0, 90);
	if (category == "SEARCH") pos += sf::Vector2f(0, 180);
	Button* lmao = add_text_box(scene, pos, sf::Vector2f(200, 60), 26, TOP_LEFT, TOP_LEFT, "TEXT_BOX");
	lmao->set_focused(1);
	return category;
}

void despawn_text_box(UIUnit& scene) {
	scene.erase_element(scene.find_button("TEXT_BOX"));
}

void spawn_message_box(UIUnit& scene, std::string message) {
	add_button(scene, sf::Vector2f(0, -50), sf::Vector2f(200 + message.size() * 15, 60), 26, BOTTOM_CENTER, BOTTOM_CENTER,
		"MESSAGE", message);
}
void despawn_message_box(UIUnit& scene) {
	scene.erase_element(scene.find_button("MESSAGE"));
}

void spawn_form(UIUnit& scene) {
	Button* form = add_button(scene, sf::Vector2f(0, 0), sf::Vector2f(500, 200), 0, CENTER_CENTER, CENTER_CENTER,
		"FORM", "");
	form->set_focused(1);

	add_text(scene, sf::Vector2f(0, -50), 50, CENTER_CENTER, CENTER_CENTER,
		"FORM_TITLE", "INPUT EDGE");

	add_text(scene, sf::Vector2f(-220, 50), 26, CENTER_CENTER, CENTER_CENTER,
		"TEXT_U", "u:");
	add_text(scene, sf::Vector2f(-60, 50), 26, CENTER_CENTER, CENTER_CENTER,
		"TEXT_V", "v:");
	add_text(scene, sf::Vector2f(100, 50), 26, CENTER_CENTER, CENTER_CENTER,
		"TEXT_W", "w:");

	add_text_box(scene, sf::Vector2f(-140, 50), sf::Vector2f(60, 40), 26, CENTER_CENTER, CENTER_CENTER,
		"TEXT_BOX_1");
	add_text_box(scene, sf::Vector2f(20, 50), sf::Vector2f(60, 40), 26, CENTER_CENTER, CENTER_CENTER,
		"TEXT_BOX_2");
	add_text_box(scene, sf::Vector2f(180, 50), sf::Vector2f(60, 40), 26, CENTER_CENTER, CENTER_CENTER,
		"TEXT_BOX_3");

	scene.find_button("TEXT_BOX_1")->set_focused(1);
	std::cout << scene.find_button("TEXT_BOX_1")->get_focused() << "\n";
}

void despawn_form(UIUnit& scene) {
	scene.erase_element(scene.find_button("FORM"));
	scene.erase_element(scene.find_button("FORM_TITLE"));
	scene.erase_element(scene.find_button("TEXT_U"));
	scene.erase_element(scene.find_button("TEXT_V"));
	scene.erase_element(scene.find_button("TEXT_W"));
	scene.erase_element(scene.find_button("TEXT_BOX_1"));
	scene.erase_element(scene.find_button("TEXT_BOX_2"));
	scene.erase_element(scene.find_button("TEXT_BOX_3"));
}