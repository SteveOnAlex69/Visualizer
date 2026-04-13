// fucked up font size
// fucked up AVL offset
// fucked up Trie offset
// fucked up Kruskal offset
// fucked up Dijkstra offset

#include <Drawing/DrawingUnit.hpp>
#include <Helper.hpp>

DrawingUnit::DrawingUnit() {

}
DrawingUnit::DrawingUnit(sf::RenderWindow *window, sf::Font f) {
	appwindow = window;
	font = f;
}

void DrawingUnit::draw_node(Node i) {
	float opacity = i.get_opacity();
	sf::Color border_color = i.get_color();

	border_color.a = opacity * 255;
	if (i.get_shape() == NO) {
	}
	else if (i.get_shape() == CIRCLE) {
		sf::CircleShape cyka(6 * 7);
		cyka.setPosition(i.get_pos());
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(border_color);
		cyka.setFillColor(BACKGROUND);
		appwindow -> draw(cyka);
	}
	else if (i.get_shape() == SQUARE || i.get_shape() == DIAMOND) {
		sf::RectangleShape rect(sf::Vector2f(6 * 7 * 2, 6 * 7 * 2));
		if (i.get_shape() == DIAMOND) {
			rect.setRotation(sf::Vector2f(1, 1).angle());
		}
		rect.setPosition(i.get_pos());
		rect.setOrigin(sf::Vector2f(rect.getLocalBounds().size) * 0.5f);
		rect.setOutlineThickness(6);
		rect.setOutlineColor(border_color);
		rect.setFillColor(BACKGROUND);
		appwindow -> draw(rect);
	}
	else if (i.get_shape() == TRIANGLE) {
		sf::CircleShape cyka(67, 3);
		cyka.setPosition(i.get_pos());
		cyka.setOrigin(cyka.getLocalBounds().size * 0.5f + cyka.getLocalBounds().position
			+ sf::Vector2f(0, cyka.getLocalBounds().size.y * 0.1f));
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(border_color);
		cyka.setFillColor(BACKGROUND);
		appwindow -> draw(cyka);
	}

	sf::Text inner(font);
	inner.setString(i.get_val());
	inner.setCharacterSize(40); // 36
	inner.setFillColor(border_color);
	inner.setPosition(i.get_pos());
	sf::FloatRect textRect = inner.getLocalBounds();
	inner.setOrigin(textRect.size * 0.5f + textRect.position);
	appwindow -> draw(inner);
}

void DrawingUnit::draw_edge(Node u, Node v, std::string val, float opacity, sf::Color color) {
	if (u.get_val() == "null" || v.get_val() == "null") return;
	sf::Color border_color = color;
	border_color.a = opacity * 255;

	sf::Vector2f fi = u.get_pos(), se = v.get_pos();
	sf::RectangleShape line;
	line.setSize(Point2((fi - se).length(), EDGE_WIDTH));
	line.setOrigin(Point2(0, EDGE_WIDTH / 2));
	line.setFillColor(border_color);
	line.setPosition(fi);
	line.setRotation((se - fi).angle());
	appwindow->draw(line);

	// draw arrow
	sf::Vector2f arrow_pos = se + sf::Vector2f(50, 0).rotatedBy((fi - se).angle());
	sf::CircleShape arrow(18, 3);
	arrow.setRotation((se - fi).angle() + sf::Vector2f(0, 1).angle());
	arrow.setPosition(arrow_pos);
	arrow.setOrigin(sf::Vector2f(arrow.getLocalBounds().size) * 0.5f);
	arrow.setFillColor(border_color);

	appwindow->draw(arrow);
	if (val.size()) {
		sf::CircleShape cyka(18);
		cyka.setPosition((fi + se) * 0.5f);
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setFillColor(BACKGROUND);

		appwindow->draw(cyka);
		sf::Text inner(font);
		inner.setString(val);
		inner.setCharacterSize(30); // 30
		inner.setFillColor(border_color);
		inner.setPosition((fi + se) * 0.5f);
		sf::FloatRect textRect = inner.getLocalBounds();
		inner.setOrigin(textRect.size * 0.5f + textRect.position);
		appwindow->draw(inner);
	}
}


void DrawingUnit::draw_graph(Graph& graph) {
	std::vector<Node> li = graph.get_node_list();
	std::vector<Edge> relation = graph.get_edges_idx();

	for (Edge i : relation) {
		draw_edge(graph.find_node(i.first), graph.find_node(i.second), i.val, i.opacity, i.color);
	}
	for (auto i : li) {
		draw_node(i);
	}
}