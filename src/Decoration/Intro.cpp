#include <Decoration/Intro.hpp>


namespace Intro {
	void draw_intro(sf::RenderWindow& appwindow, float timer) {
		if (timer <= 5) {
			float scale = std::exp(-timer * 0.2);
			float current_phase = std::pow(timer, 2);


			for(int x = -2; x <= 2; ++x)
				for (int y = -2; y <= 2; ++y) {
					int wing_amount = (x * 3 + y * 6 + 367) % 4 + 3;

					const int SPACING = 1500;
					sf::Vector2f center = screen_center + 
						sf::Vector2f(0, SPACING * scale * y).rotatedBy(sf::degrees(67))
						+ sf::Vector2f(SPACING * scale * x, 0).rotatedBy(sf::degrees(67));

					sf::CircleShape cyka(40 * scale);
					cyka.setPosition(center);
					cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
					cyka.setFillColor(FIRST_COLOR);
					appwindow.draw(cyka);

					sf::CircleShape outer_cyka(80 * scale);
					outer_cyka.setPosition(center);
					outer_cyka.setOrigin(sf::Vector2f(outer_cyka.getLocalBounds().size) * 0.5f);
					outer_cyka.setOutlineThickness(20 * scale);
					outer_cyka.setOutlineColor(FIRST_COLOR);
					outer_cyka.setFillColor(sf::Color::Transparent);
					appwindow.draw(outer_cyka);

					float bruh = (float)360 / wing_amount;
					for (int i = 0; i < wing_amount; ++i) {
						sf::Angle omega = sf::radians(current_phase) + sf::degrees(bruh * i + wing_amount * 67);
						sf::Vector2f pos = center;
						sf::Vector2f dih_placement =
							sf::Vector2f(500 * scale, 0).rotatedBy(omega);
						pos += dih_placement;

						sf::CircleShape cyka(40 * scale);
						cyka.setPosition(pos);
						cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
						cyka.setFillColor(FIRST_COLOR);
						appwindow.draw(cyka);

						sf::CircleShape outer_cyka(80 * scale);
						outer_cyka.setPosition(pos);
						outer_cyka.setOrigin(sf::Vector2f(outer_cyka.getLocalBounds().size) * 0.5f);
						outer_cyka.setOutlineThickness(20 * scale);
						outer_cyka.setOutlineColor(FIRST_COLOR);
						outer_cyka.setFillColor(sf::Color::Transparent);
						appwindow.draw(outer_cyka);

						sf::RectangleShape bro(sf::Vector2f(500 * scale, 20 * scale));
						bro.setPosition(center);
						bro.setOrigin(sf::Vector2f(0, 10 * scale));
						bro.setFillColor(FIRST_COLOR);
						bro.setRotation(omega);
						appwindow.draw(bro);
					}
			}
		}
		else {
			timer -= 5;
			sf::RectangleShape bro(screen_center * 2.f);

			float opacity = std::exp(-timer);
			bro.setPosition(sf::Vector2f(0, 0));
			bro.setFillColor(sf::Color(FIRST_COLOR.r, FIRST_COLOR.g, FIRST_COLOR.b, 255 * opacity));
			appwindow.draw(bro);
		}

	}


}