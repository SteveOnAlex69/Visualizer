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
	inner.setCharacterSize(36);
	inner.setFillColor(border_color);
	inner.setPosition(i.get_pos());
	sf::FloatRect textRect = inner.getLocalBounds();
	inner.setOrigin(textRect.size * 0.5f + textRect.position);
	appwindow -> draw(inner);
}

void DrawingUnit::draw_edge(Node u, Node v, std::string val, float opacity) {
	if (u.get_val() == "null" || v.get_val() == "null") return;
	sf::Color border_color = FIRST_COLOR;
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
		inner.setCharacterSize(30);
		inner.setFillColor(border_color);
		inner.setPosition((fi + se) * 0.5f);
		sf::FloatRect textRect = inner.getLocalBounds();
		inner.setOrigin(textRect.size * 0.5f + textRect.position);
		appwindow->draw(inner);
	}
}

Graph DrawingUnit::get_linked_list_graph(LinkedList* linked_list, sf::Vector2f ROOT, 
	std::vector<void*> highlighted) {
	std::vector<LLNode*> arr = linked_list->get_array();
	sf::Vector2f OFFSETX(200, 0);
	sf::Vector2f OFFSETY(0, 150);
	Graph vcl;

	Node prev = vcl.add_node(Node("", ROOT, (unsigned long long)arr[0], SQUARE, 1));

	for (int i = 1; i < (int)arr.size(); ++i) {
		int y = (i-1) / 7;
		int x = (i-1) % 7;
		if (y % 2) x = 6 - x;
		x++;

		Node cur = vcl.add_node(Node(arr[i]->val, ROOT + OFFSETX * (1.0f * x) + OFFSETY * (1.0f * y),
			(unsigned long long) arr[i], SQUARE, 
			2 * (std::find(highlighted.begin(), highlighted.end(), arr[i]) != highlighted.end())
		));
		vcl.add_edge(prev, cur);
		prev = cur;
	}
	return vcl;
}

Graph DrawingUnit::get_hash_map_graph(HashMapChaining* hash_map, sf::Vector2f ROOT,
	std::vector<void*> highlighted){
	sf::Vector2f OFFSETY(0, 120);
	sf::Vector2f OFFSETX(150, 0);

	Graph vcl;
	for (int i = 0; i < hash_map->get_size(); ++i) {
		vcl.add_node(Node(std::to_string(i), ROOT + OFFSETY * (1.0f * i), 0, NO));
		Graph single_line = get_linked_list_graph(&(hash_map->buckets[i]), 
			ROOT + OFFSETY * (1.0f * i) + OFFSETX, highlighted);
		
		std::vector<Node> vertices = single_line.get_node_list();
		std::vector<Edge> edges = single_line.get_edges_idx();
		
		for (Node j : vertices) vcl.add_node(j);
		for (Edge e : edges)
			vcl.add_edge(e.first, e.second, e.val);
	}
	return vcl;
}

Node loadingBST(AVLNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET,
	std::vector<void*> highlighted) {
	if (root == nullptr) return Node();
	Node cur = graph.add_node(Node(std::to_string(root -> val), ROOT, (unsigned long long) root,
		CIRCLE, 2 * (std::find(highlighted.begin(), highlighted.end(), root) != highlighted.end())
	));
	OFFSET.x *= 0.4f;
	if (root->childL) {
		Node left_child = 
			loadingBST(root->childL, graph, ROOT + sf::Vector2f(-OFFSET.x, OFFSET.y), OFFSET, 
				highlighted);
		graph.add_edge(cur, left_child);
	}
	if (root->childR) {
		Node right_child = 
			loadingBST(root->childR, graph, ROOT + sf::Vector2f(OFFSET.x, OFFSET.y), OFFSET, 
				highlighted);
		graph.add_edge(cur, right_child);
	}
	return cur;
}

Graph DrawingUnit::get_BST_graph(AVL *bst, sf::Vector2f ROOT, std::vector<void*> highlighted) {
	sf::Vector2f OFFSET(1000, 150);

	Graph vcl;
	loadingBST(bst -> root, vcl, ROOT, OFFSET, highlighted);
	return vcl;
}


Node loadingTrie(TrieNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET, 
	std::vector<void*> highlighted) {
	if (root == nullptr) return Node();
	if (root == nullptr) return Node();
	Node cur = graph.add_node(Node(std::to_string(root -> cnt), ROOT, (unsigned long long)root,
		CIRCLE, (std::find(highlighted.begin(), highlighted.end(), root) != highlighted.end())
	));
	int child_cnt = 0;
	for (int i = 0; i < ALPHA; ++i) if (root->child[i]) child_cnt++;
	if (child_cnt == 0) return cur;

	int cur_child = 0;
	sf::Vector2f nOFFSET = sf::Vector2f(OFFSET.x / child_cnt, OFFSET.y);
	for (int i = 0; i < ALPHA; ++i) if (root->child[i]) {
		cur_child++;
		sf::Vector2f nROOT = ROOT;
		nROOT.y += OFFSET.y;
		nROOT.x += OFFSET.x * (-0.5f + (cur_child - 0.5f) / child_cnt);

		Node child = loadingTrie(root->child[i], graph, nROOT, nOFFSET, highlighted);
		graph.add_edge(cur, child, std::string(1, '0' + i));
	}
	
	return cur;
}

Graph DrawingUnit::get_trie_graph(Trie* tri, sf::Vector2f ROOT, std::vector<void*> highlighted) {
	sf::Vector2f OFFSET(1800, 180);

	Graph vcl;
	loadingTrie(tri->root, vcl, ROOT, OFFSET, highlighted);
	return vcl;
}

Graph DrawingUnit::get_kruskal_graph(Kruskal* kurst, sf::Vector2f ROOT, int it) {
	Graph ans;
	std::vector<int> vertices = kurst->get_vertices();


	for (int i = 0; i < (int)vertices.size(); ++i) {
		int y = (i * 5) % 7;
		ans.add_node(Node(std::to_string(vertices[i]), ROOT + sf::Vector2f(i * 200.f, y * 120.0f),
			(unsigned long long)vertices[i],
			CIRCLE, false));
	}

	std::vector<KruskalEdge> e = kurst->run_kruskal();
	if (it == -1) {
		for (auto i : e) {
			ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w));
			ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w));
		}
	}
	else {
		for (auto i : e) {
			if (it <= 0) break;
			if (i.flag) {
				ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w));
				ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w));
				it--;
			}
			else {
				if (it == 1) {
					ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w));
					ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w));
				}
				it -= 2;
			}
		}
		if (it > 0) {
			Graph empty_graph;
			return empty_graph;
		}
	}


	return ans;
}


Graph DrawingUnit::get_dijkstra_graph(Dijkstra* dik, sf::Vector2f ROOT, 
	std::vector<int> highlight1, std::vector<int> highlight2) {
	Graph ans;
	std::vector<int> vertices = dik->get_vertices();
	const int C = 7;

	for (int i = 0; i < (int)vertices.size(); ++i) {
		int y = (i * 5) % 7;
		
		int node_color = 0;
		if (std::find(highlight1.begin(), highlight1.end(), vertices[i]) != highlight1.end())
			node_color = 2;
		if (std::find(highlight2.begin(), highlight2.end(), vertices[i]) != highlight2.end())
			node_color = 3;
		ans.add_node(Node(std::to_string(vertices[i]), ROOT + sf::Vector2f(i * 200.f, y * 120.f),
			(unsigned long long)vertices[i],
			CIRCLE, node_color));
	}
	std::vector<DijkstraEdge> e = dik->get_edges();
	for (auto i : e) {
		ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w));
	}
	return ans;
}

void DrawingUnit::draw_graph(Graph& graph) {
	std::vector<Node> li = graph.get_node_list();
	std::vector<Edge> relation = graph.get_edges_idx();

	for (Edge i : relation) {
		draw_edge(graph.find_node(i.first), graph.find_node(i.second), i.val, i.opacity);
	}
	for (auto i : li) {
		draw_node(i);
	}
}