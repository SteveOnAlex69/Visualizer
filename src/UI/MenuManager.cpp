#include <UI/MenuManager.hpp>

MenuManager::MenuManager() {
	current_state = MENU;
}

bool MenuManager::set_current_state(MenuState nxt) {
	current_state = nxt;
	return true;
}

MenuState MenuManager::get_current_state() {
	return current_state;
}