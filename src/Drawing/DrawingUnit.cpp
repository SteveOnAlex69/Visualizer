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

void DrawingUnit::draw_node(Node i, bool flag) {
	float opacity = i.get_opacity();
	sf::Color border_color = i.get_color();
	sf::Color background_color = i.get_background_color();
	sf::Color font_color = i.get_font_color();
	sf::Color weight_color = SIXTH_COLOR;

	border_color.a = opacity * 255;
	background_color.a = opacity * 255;
	font_color.a = opacity * 255;
	weight_color.a = opacity * 255;
	if (i.get_shape() == NO) {
	}
	else if (i.get_shape() == CIRCLE) {
		sf::CircleShape cyka(6 * 7);
		cyka.setPosition(i.get_pos());
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(border_color);
		cyka.setFillColor(background_color);
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
		rect.setFillColor(background_color);
		appwindow -> draw(rect);
	}
	else if (i.get_shape() == TRIANGLE) {
		sf::CircleShape cyka(67, 3);
		cyka.setPosition(i.get_pos());
		cyka.setOrigin(cyka.getLocalBounds().size * 0.5f + cyka.getLocalBounds().position
			+ sf::Vector2f(0, cyka.getLocalBounds().size.y * 0.1f));
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(border_color);
		cyka.setFillColor(background_color);
		appwindow -> draw(cyka);
	}

	sf::Text inner(font);
	inner.setString(i.get_val());
	inner.setCharacterSize(36); // 36
	inner.setFillColor(font_color);
	inner.setPosition(i.get_pos());
	sf::FloatRect innertextRect = inner.getLocalBounds();
	inner.setOrigin(innertextRect.size * 0.5f + innertextRect.position);
	appwindow -> draw(inner);

	if (flag) {
		sf::Text outer(font);
		outer.setString(i.get_weight());
		outer.setCharacterSize(24); // 36
		outer.setFillColor(weight_color);
		outer.setPosition(i.get_pos() + sf::Vector2f(0, 80));
		sf::FloatRect outertextRect = outer.getLocalBounds();
		outer.setOrigin(outertextRect.size * 0.5f + outertextRect.position);
		appwindow->draw(outer);
	}
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

void DrawingUnit::draw_viz_state(VisualizerState& viz_lu, bool flag) {
	draw_graph(viz_lu.get_graph(), flag);
	draw_pseudo_code(viz_lu.get_pseudo_code());
}

void DrawingUnit::draw_graph(Graph& graph, bool flag) {
	std::vector<Node> li = graph.get_node_list();
	std::vector<Edge> relation = graph.get_edges_idx();

	for (Edge i : relation) {
		draw_edge(graph.find_node(i.first), graph.find_node(i.second), i.val, i.opacity, i.color);
	}
	for (auto i : li) {
		draw_node(i, flag);
	}
}

void DrawingUnit::draw_pseudo_code(Pseudocode& sudo_code) {
	sf::RectangleShape rect(sf::Vector2f(400, 700));

	sf::Vector2f rectsize = rect.getLocalBounds().size;
	rect.setOrigin(sf::Vector2f(rectsize.x, rectsize.y * 0.5f));

	rect.setPosition(sf::Vector2f(screen_center.x * 2 - 67, screen_center.y));
	rect.setFillColor(sf::Color(36, 36, 36, 150));
	rect.setOutlineColor(SECOND_COLOR);
	rect.setOutlineThickness(4);
	appwindow->draw(rect);

	std::string content = sudo_code.get_content();
	sf::Vector2f ROOT_POS(screen_center.x * 2 - 67 - 370, screen_center.y - 340);
	sf::Text tex(font);
	tex.setString(sudo_code.get_content());
	tex.setFillColor(FIRST_COLOR * FIRST_COLOR * FIRST_COLOR);
	tex.setCharacterSize(20);
	tex.setPosition(ROOT_POS);
	appwindow->draw(tex);

	std::vector<std::string> s; s.emplace_back();
	for (char c : content) {
		if (c == '\n') s.emplace_back();
		else s.back().push_back(c);
	}
	if (s.back().empty()) s.pop_back();

	std::vector<int> highlighted_line = sudo_code.get_highlighted();
	for(int h: highlighted_line) {
		sf::Text high_tex(font);
		high_tex.setString(std::string(h - 1, '\n') + s[h - 1]);
		high_tex.setFillColor(THIRD_COLOR);
		high_tex.setCharacterSize(20);
		high_tex.setPosition(ROOT_POS);
		appwindow->draw(high_tex);
	}
	

	std::string line_indices;
	for (int i = 1; i <= s.size(); ++i)
		line_indices += std::to_string(i) + "\n";

	sf::Text shit(font);
	shit.setString(line_indices);
	shit.setFillColor(FIRST_COLOR);
	shit.setCharacterSize(20);
	shit.setPosition(ROOT_POS - sf::Vector2f(20, 0));
	appwindow->draw(shit);
}