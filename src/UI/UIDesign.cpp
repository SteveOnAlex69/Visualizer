#include <UI/UIDesign.hpp>


Button* add_text(UIUnit& menu, sf::Vector2f pos, int text_size, bool centered, std::string s) {
	Button* cur = new Button(pos, sf::Vector2f(0, 0), BACKGROUND, sf::Color::White, text_size, centered, s, TEXT);
	menu.add_element(cur);
	return cur;
}

Button* add_button(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size, int text_size, bool centered, std::string s) {
	Button* cur = new Button(pos, size,FORESKIN, sf::Color::White, text_size, centered, s, BUTTON);
	menu.add_element(cur);
	return cur;
}

Button* add_text_box(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size, int text_size, bool centered, std::string s) {
	Button* cur = new Button(pos, size, FORESKIN, sf::Color::White, text_size, centered, s, TEXTBOX);
	menu.add_element(cur);
	return cur;
}

void setup_menu(UIUnit& menu) {
	// set up menu
	add_text(menu, screen_center + sf::Vector2f(0, -300), 100, true, "DATA VISUALIZER");
	add_text(menu, sf::Vector2f(screen_center.x, screen_center.y * 2 - 10), 20, true,
		"This project was made by Le Kien Thanh, APCS 2025, First year, with 2 days left on the clock");
	add_button(menu, screen_center + sf::Vector2f(0, -100), sf::Vector2f(300, 80), 36, true,
		"START");
	add_button(menu, screen_center + sf::Vector2f(0, 0), sf::Vector2f(300, 80), 36, true,
		"SETTINGS");
	add_button(menu, screen_center + sf::Vector2f(0, 100), sf::Vector2f(300, 80), 36, true,
		"ABOUT");
	add_button(menu, screen_center + sf::Vector2f(0, 200), sf::Vector2f(300, 80), 36, true,
		"QUIT");
}


void setup_about(UIUnit& about) {
	// set up about
	add_button(about, sf::Vector2f(30, 30), sf::Vector2f(200, 60), 26, false, "BACK");
	add_text(about, screen_center + sf::Vector2f(0, -500), 100, true, "ABOUT");

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
		sf::Vector2f po(screen_center.x, 200);
		po += sf::Vector2f(0, 36) * (i * 1.0f);
		add_text(about, po, 30, true, lines[i]);
	}
}

void setup_settings(UIUnit& settings) {
	// set up settings
	add_button(settings, sf::Vector2f(30, 30), sf::Vector2f(200, 60), 26, false, "BACK");
	add_text(settings, screen_center + sf::Vector2f(0, -500), 100, true, "SETTINGS");
}

void setup_visualizer(UIUnit& visualizer) {
	// set up visualizer
	add_button(visualizer, sf::Vector2f(30, 30), sf::Vector2f(200, 60), 26, false, "BACK");
	add_text(visualizer, screen_center + sf::Vector2f(0, -500), 100, true, "VISUALIZER");

	add_button(visualizer, sf::Vector2f(30, 700), sf::Vector2f(200, 60), 26, false, "INSERT");
	add_button(visualizer, sf::Vector2f(30, 770), sf::Vector2f(200, 60), 26, false, "ERASE");
	add_button(visualizer, sf::Vector2f(30, 840), sf::Vector2f(200, 60), 26, false, "SEARCH");
}