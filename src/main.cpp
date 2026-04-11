#include <SFML/Graphics.hpp>
#include <iostream>
#include <Helper.hpp>
#include <GameLogic.hpp>

sf::RenderWindow appWindow;
const int FRAME_TIME = 5;

int main(int argv, char* args[]) {
	std::cout << "booted" << std::endl;
	
	appWindow = sf::RenderWindow(sf::VideoMode(windowSize), "Visualizer",
		sf::Style::Titlebar | sf::Style::Close);

	if (appWindow.isOpen() == false) {
		std::cerr << "Error creating window" << std::endl;
		return false;
	}

	appStart(appWindow);

	clock_t prev = clock();
	while (appWindow.isOpen()) {
		clock_t cur = clock();
		int efn = cur - prev;
		if (efn >= FRAME_TIME) {
			prev = cur;
			appLoop(appWindow, efn * 0.001f);
		}
	}

	return EXIT_SUCCESS;
}