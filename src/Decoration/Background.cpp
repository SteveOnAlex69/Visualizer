#include <Decoration/Background.hpp>


BackgroundDrawer::BackgroundDrawer() {
	appwindow = nullptr;
}
BackgroundDrawer::BackgroundDrawer(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;
	for (int i = 0; i < 500; ++i) {
		points.push_back(sf::Vector3f(rngesus(-2000, 2000), rngesus(-2000, 2000), rngesus(100, 2000)));
	}

	std::sort(points.begin(), points.end(), [](sf::Vector3f a, sf::Vector3f b) {
		return a.z > b.z;
	});
}

void BackgroundDrawer::draw(sf::Vector2f mouse_pos, float delta) {
	draw1(mouse_pos, delta);
}


void BackgroundDrawer::draw1(sf::Vector2f mouse_pos, float delta) {
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

		sf::Color half_cur(cur.r / 2, cur.g / 2, cur.b / 2);

		sf::RectangleShape cyka(sf::Vector2f(10000.0f / num, 10000.0f / num));
		cyka.setRotation(sf::Vector2f(1, 1).angle());
		cyka.setFillColor(half_cur);
		cyka.setPosition(screen_pos);
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		appwindow->draw(cyka);



		sf::RectangleShape inner_cyka(sf::Vector2f(5000.0f / num, 5000.0f / num));
		inner_cyka.setRotation(sf::Vector2f(1, 1).angle());
		inner_cyka.setFillColor(cur);
		inner_cyka.setPosition(screen_pos);
		inner_cyka.setOrigin(sf::Vector2f(inner_cyka.getLocalBounds().size) * 0.5f);
		appwindow->draw(inner_cyka);
	}

	for (sf::Vector3f &i : points) {
		sf::Vector2f cur(i.x, i.y);
		cur = cur.rotatedBy(sf::radians(delta * 0.01));
		i.x = cur.x;
		i.y = cur.y;
	}

}