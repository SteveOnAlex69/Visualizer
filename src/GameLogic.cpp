#include <Helper.hpp>
#include <GameLogic.hpp>
#include <MediaPlayer.hpp>
#include <Node.hpp>
#include <Graph.hpp>
#include <LinkedList.hpp>
#include <Hashmap.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>

#define ll long long
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

sf::Font font;
std::string FONT_PATH = std::string(PROJECT_DIR) + "assets/Font/Consola.ttf";
sf::Vector2f screen_center;

HashMapChaining umap;
void appStart(sf::RenderWindow& appwindow) {
	screen_center = Point2(windowSize.x / 2, windowSize.y / 2);
	font.openFromFile(FONT_PATH.c_str());

	umap = HashMapChaining(13);
	umap.insert(36);
	umap.insert(67);
	umap.insert(420);
	umap.insert(69);
}

bool pressing = false;
void handle_keypress(float delta) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
	}
	else {
	}
}


Point2 get_mouse_pos(sf::RenderWindow& appwindow) {
	auto tmp = sf::Mouse::getPosition(appwindow);
	return Point2(tmp.x, tmp.y);
}

bool is_clicking = false;
Point2 pre_mouse_pos;
void handle_mouse(sf::RenderWindow& appwindow, float delta) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		is_clicking = true;
	}
	else {
		is_clicking = false;
	}
}

int pollEvent(sf::RenderWindow& appwindow) { // if window is closed, return 0
	int return_val = 1;
	while (const std::optional event = appwindow.pollEvent()) {
		if (event->is <sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			std::cerr << "Closing the window" << std::endl;
			appwindow.close();
			return 0;
		}
	}

	return return_val;
}

void draw_node(sf::RenderWindow& appwindow, Node i) {
	if (i.get_shape() == NO) {
	}
	else if (i.get_shape() == CIRCLE) {
		sf::CircleShape cyka(6 * 7);
		cyka.setPosition(i.get_pos());
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(FORESKIN);
		cyka.setFillColor(BACKGROUND);
		appwindow.draw(cyka);
	}
	else if (i.get_shape() == SQUARE || i.get_shape() == DIAMOND) {
		sf::RectangleShape rect(sf::Vector2f(6 * 7 * 2, 6 * 7 * 2));
		if (i.get_shape() == DIAMOND) {
			rect.setRotation(sf::Vector2f(1, 1).angle());
		}
		rect.setPosition(i.get_pos());
		rect.setOrigin(sf::Vector2f(rect.getLocalBounds().size) * 0.5f);
		rect.setOutlineThickness(6);
		rect.setOutlineColor(FORESKIN);
		rect.setFillColor(BACKGROUND);
		appwindow.draw(rect);
	}
	else if (i.get_shape() == TRIANGLE) {
		sf::CircleShape cyka(67, 3);
		cyka.setPosition(i.get_pos());
		cyka.setOrigin(cyka.getLocalBounds().size * 0.5f + cyka.getLocalBounds().position
			+ sf::Vector2f(0, cyka.getLocalBounds().size.y * 0.1f));
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(FORESKIN);
		cyka.setFillColor(BACKGROUND);
		appwindow.draw(cyka);
	}

	sf::Text inner(font);
	inner.setString(std::to_string(i.get_val()));
	inner.setCharacterSize(36);
	inner.setFillColor(FORESKIN);
	inner.setPosition(i.get_pos());
	sf::FloatRect textRect = inner.getLocalBounds();
	inner.setOrigin(textRect.size * 0.5f + textRect.position);
	appwindow.draw(inner);
}

void draw_graph(sf::RenderWindow& appwindow, Graph& graph) {
	std::vector<Node> li = graph.get_node_list();
	std::vector<std::pair<int, int>> relation = graph.get_edges_idx();

	for (auto i : relation) {
		int u = i.first, v = i.second;
		sf::RectangleShape line;
		line.setSize(Point2((li[u].get_pos() - li[v].get_pos()).length(), EDGE_WIDTH));
		line.setOrigin(Point2(0, EDGE_WIDTH / 2));
		line.setFillColor(FORESKIN);
		line.setPosition(li[u].get_pos());
		line.setRotation((li[v].get_pos() - li[u].get_pos()).angle());
		appwindow.draw(line);
	}
	for (auto i : li) draw_node(appwindow, i);
}

void draw_linked_list(sf::RenderWindow& appwindow, LinkedList& linked_list, sf::Vector2f ROOT) {
	std::vector<int> arr = linked_list.get_array();
	sf::Vector2f OFFSET(200, 0);
	Graph vcl;
	for (int i = 0; i < (int)arr.size(); ++i) {
		vcl.add_node(Node(arr[i], ROOT + OFFSET * (1.0f * i), SQUARE));
		if (i > 0) vcl.add_edge(arr[i - 1], arr[i]);
	}
	draw_graph(appwindow, vcl);
}


void draw_hash_map(sf::RenderWindow& appwindow, HashMapChaining& chenning, sf::Vector2f ROOT) {
	sf::Vector2f OFFSET(0, 150);
	sf::Vector2f SPACING(150, 0);

	Graph vcl;
	for (int i = 0; i < chenning.n; ++i) {
		vcl.add_node(Node(i, ROOT + OFFSET * (1.0f * i), NO));
		draw_linked_list(appwindow, chenning.buckets[i], ROOT + OFFSET * (1.0f * i) + SPACING);
	}
	draw_graph(appwindow, vcl);
}


void appLoop(sf::RenderWindow& appwindow, float delta) {
	int cur = pollEvent(appwindow);
	if (cur == 0) return;
	appwindow.clear(BACKGROUND);
	handle_mouse(appwindow, delta);

	draw_hash_map(appwindow, umap, sf::Vector2f(200, 200));

	appwindow.display();
}