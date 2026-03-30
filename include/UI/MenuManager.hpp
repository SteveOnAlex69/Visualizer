#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum MenuState {
	MENU = 0,
	VISUALIZING = 1,
	ABOUT = 2,
	SETTINGS = 3
};

class MenuManager { // managing the state of the menu
	public:
		MenuManager();
		MenuState get_current_state();
		bool set_current_state(MenuState nxt);
	private:
		MenuState  current_state;
};

#endif