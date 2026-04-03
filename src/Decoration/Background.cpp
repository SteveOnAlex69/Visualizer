#include <Decoration/Background.hpp>


BackgroundDrawer::BackgroundDrawer() {
	appwindow = nullptr;
}
BackgroundDrawer::BackgroundDrawer(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;

	for (int i = 0; i < 100; ++i) {
		points.push_back(sf::Vector3f(rngesus(-2000, 2000), rngesus(-2000, 2000), rngesus(100, 2000)));
	}
}

void BackgroundDrawer::draw(sf::Vector2f mouse_pos) {
	draw1(mouse_pos);
}


void BackgroundDrawer::draw1(sf::Vector2f mouse_pos) {
	mouse_pos -= screen_center;
	appwindow->clear(BACKGROUND);


	for (sf::Vector3f i : points) {
		i.x -= mouse_pos.x;
		i.y -= mouse_pos.y;

		sf::Vector2f screen_pos = sf::Vector2f(i.x / i.z + 1, i.y / i.z + 1);
		screen_pos.x *= screen_center.x;
		screen_pos.y *= screen_center.y;

		const int SUB = 50;
		int num = i.z;
		sf::Color cur(250, 250, 250);
		if (num % 3 == 0) cur.r -= SUB;
		else if (num % 3 == 1) cur.g -= SUB;
		else cur.b -= SUB;

		sf::CircleShape cyka(200 / pow(i.z, 0.6));
		cyka.setFillColor(cur);
		cyka.setPosition(screen_pos);
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		appwindow->draw(cyka);
	}
}