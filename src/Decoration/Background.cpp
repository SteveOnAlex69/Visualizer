#include <Decoration/Background.hpp>
#include <Helper.hpp>


BackgroundDrawer::BackgroundDrawer() {
	appwindow = nullptr;
}
BackgroundDrawer::BackgroundDrawer(sf::RenderWindow* window, sf::Font f) {
	appwindow = window;
	font = f;
	total_time = 0;
	for (int i = 0; i < 1000; ++i) {
		points.push_back(sf::Vector3f(rngesus(-2000, 2000), rngesus(-2000, 2000), rngesus(100, 2000)));
	}

	std::sort(points.begin(), points.end(), [](sf::Vector3f a, sf::Vector3f b) {
		return a.z > b.z;
	});
}

void BackgroundDrawer::draw(sf::Vector2f mouse_pos, float delta) {
	appwindow->clear(BACKGROUND);
	total_time += delta;
	draw3(mouse_pos, delta);
}


void BackgroundDrawer::draw4(sf::Vector2f mouse_pos, float delta) {
	mouse_pos -= screen_center;

	for (sf::Vector3f i : points) {
		int num = i.z;
		sf::Vector2f cur2d(i.x, i.y);
		cur2d = cur2d.rotatedBy(sf::radians(total_time));
		
		i.z += total_time * 500;
		ll dih = (i.z - 100) / 1900;
		i.z -= dih * 1900;

		sf::Vector2f node_pos = sf::Vector2f(cur2d.x / i.z, cur2d.y / i.z);
		node_pos.x *= screen_center.x;
		node_pos.y *= screen_center.x;
		node_pos += screen_center;

		const float DEF = 120;
		const float SUB = -20;
		sf::Color cur(DEF - pow(num, 0.57), DEF - pow(num, 0.57), DEF - pow(num, 0.57));
		if (GETBIT(num, 0)) cur.r -= SUB;
		if (GETBIT(num, 1)) cur.g -= SUB;
		if (GETBIT(num, 2)) cur.b -= SUB;

		sf::CircleShape cyka(10000.0f / i.z);
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setRotation(sf::radians(total_time + num % 8));
		cyka.setFillColor(cur);
		cyka.setPosition(node_pos);
		appwindow->draw(cyka);
	}

}

void BackgroundDrawer::draw3(sf::Vector2f mouse_pos, float delta) {
	mouse_pos -= screen_center;

	int cnt = 0;
	for(int x = -1260; x <= 1260; x += 60)
	for (int y = -1260; y <= 1260; y += 60) {
		sf::Vector2f p(x, y);
		p = p.rotatedBy(sf::radians(total_time * 0.1));
		float dih = sf::Vector2f(p.x - mouse_pos.x, p.y - mouse_pos.y).lengthSquared();
		p = mouse_pos + sf::Vector2f(p.x - mouse_pos.x, p.y - mouse_pos.y) 
			/ (1 + 10000/dih);

		cnt++;
		const float DEF = 120;
		const float SUB = -36;
		sf::Color cur(DEF, DEF, DEF);
		if (GETBIT(cnt, 0)) cur.r += SUB;
		if (GETBIT(cnt, 1)) cur.g += SUB;
		if (GETBIT(cnt, 2)) cur.b += SUB;

		sf::CircleShape cyka(5);
		cyka.setFillColor(cur);
		cyka.setPosition(p + screen_center);
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		appwindow->draw(cyka);
	}
}

void BackgroundDrawer::draw2(sf::Vector2f mouse_pos, float delta) {
	mouse_pos -= screen_center;

	for (sf::Vector3f i : points) {
		sf::Vector2f cur2d(i.x, i.y);
		cur2d.y += total_time * 100;
		long long dih = (long long)((cur2d.y + 2000)) / 4000;
		cur2d.y -= dih * 4000;

		cur2d.x -= mouse_pos.x * 0.3f;
		cur2d.y -= mouse_pos.y * 0.3f;

		sf::Vector2f screen_pos = sf::Vector2f(cur2d.x / i.z + 1, cur2d.y / i.z + 1);
		screen_pos.x *= screen_center.x;
		screen_pos.y *= screen_center.y;

		const float DEF = 120;
		const float SUB = -20;
		int num = i.z;
		sf::Color cur(DEF - pow(num, 0.57), DEF - pow(num, 0.57), DEF - pow(num, 0.57));
		if (GETBIT(num, 0)) cur.r -= SUB;
		if (GETBIT(num, 1)) cur.g -= SUB;
		if (GETBIT(num, 2)) cur.b -= SUB;

		sf::CircleShape cyka(20000.0f / i.z, 3);
		cyka.setRotation(sf::radians(total_time + num % 8));
		cyka.setFillColor(cur);
		cyka.setPosition(screen_pos);
		appwindow->draw(cyka);
	}
}


void BackgroundDrawer::draw1(sf::Vector2f mouse_pos, float delta) {
	mouse_pos -= screen_center;

	for (sf::Vector3f i : points) {
		sf::Vector2f cur2d(i.x, i.y);
		cur2d.y += total_time * 200;
		long long dih = (long long)((cur2d.y + 2000)) / 4000;
		cur2d.y -= dih * 4000;

		cur2d.x -= mouse_pos.x * 0.3f;
		cur2d.y -= mouse_pos.y * 0.3f;

		sf::Vector2f screen_pos = sf::Vector2f(cur2d.x / i.z + 1, cur2d.y / i.z + 1);
		screen_pos.x *= screen_center.x;
		screen_pos.y *= screen_center.y;

		const int SUB = 50;
		int num = i.z;
		sf::Color cur(250, 250, 250);

		if (GETBIT(num, 0)) cur.r -= SUB;
		if (GETBIT(num, 1)) cur.g -= SUB;
		if (GETBIT(num, 2)) cur.b -= SUB;

		sf::Color half_cur(cur.r / 2, cur.g / 2, cur.b / 2);

		sf::RectangleShape cyka(sf::Vector2f(10000.0f / i.z, 10000.0f / i.z));
		cyka.setRotation(sf::Vector2f(1, 1).angle());
		cyka.setFillColor(half_cur);
		cyka.setPosition(screen_pos);
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		appwindow->draw(cyka);


		sf::RectangleShape inner_cyka(sf::Vector2f(5000.0f / i.z, 5000.0f / i.z));
		inner_cyka.setRotation(sf::Vector2f(1, 1).angle());
		inner_cyka.setFillColor(cur);
		inner_cyka.setPosition(screen_pos);
		inner_cyka.setOrigin(sf::Vector2f(inner_cyka.getLocalBounds().size) * 0.5f);
		appwindow->draw(inner_cyka);
	}
}