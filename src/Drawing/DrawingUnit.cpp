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
	sf::Color border_color = FIRST_COLOR;
	if (i.is_special()) border_color = sf::Color::Yellow;

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

float sigmoid(float epoch) {
	epoch -= 0.5f;
	epoch *= 10;
	return (float)1 / (1 + std::exp(-epoch));
}

int get_diff_state(Graph& graph1, Graph& graph2) {
	// bit 0 will be true if we have to delete something from graph 1
	// bit 1 will be true if we have to relocate something that is common across graph 1 and graph 2
	// bit 2 will be true if we have to add something from graph 2
	int mask = 0;
	std::vector<Node> li1 = graph1.get_node_list();
	std::vector<Node> li2 = graph2.get_node_list();
	std::vector<Edge> e1 = graph1.get_edges_idx();
	std::vector<Edge> e2 = graph2.get_edges_idx();

	for (Node i : li1) {
		bool found = false;
		for (Node j : li2) {
			if (i.get_hash_val() == j.get_hash_val()) {
				found = true;
				if (i.get_pos() != j.get_pos()) mask |= 2;
			}
		}
		if (found == false) mask |= 1;
	}
	for (Node i : li2) {
		bool found = false;
		for (Node j : li1) 
			if (i.get_hash_val() == j.get_hash_val())
				found = true;
		if (found == false) mask |= 4;
	}

	for (Edge i : e1) {
		bool found = false;
		for (Edge j : e2)
			if (i.first == j.first && i.second == j.second && i.val == j.val)
				found = true;
		if (found == false) mask |= 1;
	}
	for (Edge i : e2) {
		bool found = false;
		for (Edge j : e1)
			if (i.first == j.first && i.second == j.second && i.val == j.val)
				found = true;
		if (found == false) mask |= 4;
	}

	return mask;
}

void DrawingUnit::draw_graph_stage1(Graph& graph1, Graph& graph2, float epoch) {
	Graph graph;
	std::vector<Node> li1 = graph1.get_node_list();
	std::vector<Node> li2 = graph2.get_node_list();
	std::vector<Edge> e1 = graph1.get_edges_idx();
	std::vector<Edge> e2 = graph2.get_edges_idx();

	for (Node i : li1) {
		sf::Vector2f pos_start = i.get_pos();
		bool found = false;
		for (Node j : li2)
			if (i.get_hash_val() == j.get_hash_val()) {
				found = true;
			}

		sf::Vector2f pos = pos_start;
		i.set_pos(pos);
		if (found == false) i.set_opacity(1-sigmoid(epoch));
		graph.add_node(i);
	}
	for (Edge e : e1) {
		bool found = false;
		for (Edge g : e2) {
			if (e.first == g.first && e.second == g.second && e.val == g.val)
				found = true;
		}
		if (found)
			graph.add_edge(e.first, e.second, e.val, 1);
		else graph.add_edge(e.first, e.second, e.val, 1 - sigmoid(epoch));
	}
	draw_graph(graph);

}
void DrawingUnit::draw_graph_stage2(Graph& graph1, Graph& graph2, float epoch) {
	Graph graph;
	std::vector<Node> li1 = graph1.get_node_list();
	std::vector<Node> li2 = graph2.get_node_list();
	std::vector<Edge> e1 = graph1.get_edges_idx();
	std::vector<Edge> e2 = graph2.get_edges_idx();

	for (Node i : li1) {
		sf::Vector2f pos_start = i.get_pos(), pos_end = i.get_pos();
		bool found = false;
		for (Node j : li2)
			if (i.get_hash_val() == j.get_hash_val()) {
				pos_end = j.get_pos();
				found = true;
			}
		if (found) {
			sf::Vector2f pos = pos_start + (pos_end - pos_start) * sigmoid(epoch);
			i.set_pos(pos);
			graph.add_node(i);
		}
	}
	for (Edge e : e1) {
		bool found = false;
		for (Edge g : e2) {
			if (e.first == g.first && e.second == g.second && e.val == g.val)
				found = true;
		}
		if (found)
			graph.add_edge(e.first, e.second, e.val);
	}
	draw_graph(graph);
}
void DrawingUnit::draw_graph_stage3(Graph& graph1, Graph& graph2, float epoch) {
	Graph graph;
	std::vector<Node> li1 = graph1.get_node_list();
	std::vector<Node> li2 = graph2.get_node_list();
	std::vector<Edge> e1 = graph1.get_edges_idx();
	std::vector<Edge> e2 = graph2.get_edges_idx();

	for (Node i : li2) {
		sf::Vector2f pos_start = i.get_pos();
		bool found = false;
		for (Node j : li1)
			if (i.get_hash_val() == j.get_hash_val()) 
				found = true;
		sf::Vector2f pos = pos_start;
		i.set_pos(pos);
		if (found == false) i.set_opacity(sigmoid(epoch));
		graph.add_node(i);
	}
	for (Edge e : e2) {
		bool found = false;
		for (Edge g : e1) {
			if (e.first == g.first && e.second == g.second && e.val == g.val)
				found = true;
		}
		if (found)
			graph.add_edge(e.first, e.second, e.val, 1);
		else graph.add_edge(e.first, e.second, e.val, sigmoid(epoch));
	}
	draw_graph(graph);
}


void DrawingUnit::draw_graph(Graph& graph1, Graph& graph2, float epoch) {
	int mask = get_diff_state(graph1, graph2);
	if (epoch > ANIMATION_TIME || pop_cnt(mask) == 0) {
		draw_graph(graph2);
		return;
	}
	const float STEP = ANIMATION_TIME / pop_cnt(mask);
	for (int i = 0; i < 3; ++i) if (GETBIT(mask, i)) {
		if (epoch <= STEP) {
			if (i == 0) draw_graph_stage1(graph1, graph2, epoch * pop_cnt(mask));
			if (i == 1) draw_graph_stage2(graph1, graph2, epoch * pop_cnt(mask));
			if (i == 2) draw_graph_stage3(graph1, graph2, epoch * pop_cnt(mask));
			break;
		}
		epoch -= STEP;
	}
}

Graph DrawingUnit::get_linked_list_graph(LinkedList* linked_list, sf::Vector2f ROOT, LLNode* highlighted_node) {
	std::vector<LLNode*> arr = linked_list->get_array();
	sf::Vector2f OFFSETX(200, 0);
	sf::Vector2f OFFSETY(0, 150);
	Graph vcl;

	Node prev = vcl.add_node(Node("", ROOT, (unsigned long long)arr[0], SQUARE, true));

	for (int i = 1; i < (int)arr.size(); ++i) {
		int y = (i-1) / 7;
		int x = (i-1) % 7;
		if (y % 2) x = 6 - x;
		x++;

		Node cur = vcl.add_node(Node(arr[i]->val, ROOT + OFFSETX * (1.0f * x) + OFFSETY * (1.0f * y),
			(unsigned long long) arr[i], SQUARE, arr[i] == highlighted_node));
		vcl.add_edge(prev, cur);
		prev = cur;
	}
	return vcl;
}
void DrawingUnit::draw_linked_list(LinkedList *linked_list, sf::Vector2f ROOT, LLNode *highlighted_node) {
	draw_graph(get_linked_list_graph(linked_list, ROOT, highlighted_node));
}

Graph DrawingUnit::get_hash_map_graph(HashMapChaining* hash_map, sf::Vector2f ROOT, LLNode* highlighted_node) {
	sf::Vector2f OFFSETY(0, 120);
	sf::Vector2f OFFSETX(150, 0);

	Graph vcl;
	for (int i = 0; i < hash_map->get_size(); ++i) {
		vcl.add_node(Node(std::to_string(i), ROOT + OFFSETY * (1.0f * i), 0, NO));
		Graph single_line = get_linked_list_graph(&(hash_map->buckets[i]), ROOT + OFFSETY * (1.0f * i) + OFFSETX, highlighted_node);
		
		std::vector<Node> vertices = single_line.get_node_list();
		std::vector<Edge> edges = single_line.get_edges_idx();
		
		for (Node j : vertices) vcl.add_node(j);
		for (Edge e : edges)
			vcl.add_edge(e.first, e.second, e.val);
	}
	return vcl;
}
void DrawingUnit::draw_hash_map(HashMapChaining *hash_map, sf::Vector2f ROOT, LLNode* highlighted_node) {
	draw_graph(get_hash_map_graph(hash_map, ROOT, highlighted_node));
}

Node loadingBST(AVLNode *root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET, AVLNode *highlighted_node) {
	if (root == nullptr) return Node();
	Node cur = graph.add_node(Node(std::to_string(root -> val), ROOT, (unsigned long long) root,
		CIRCLE, root == highlighted_node));
	OFFSET.x *= 0.4f;
	if (root->childL) {
		Node left_child = 
			loadingBST(root->childL, graph, ROOT + sf::Vector2f(-OFFSET.x, OFFSET.y), OFFSET, highlighted_node);
		graph.add_edge(cur, left_child);
	}
	if (root->childR) {
		Node right_child = 
			loadingBST(root->childR, graph, ROOT + sf::Vector2f(OFFSET.x, OFFSET.y), OFFSET, highlighted_node);
		graph.add_edge(cur, right_child);
	}
	return cur;
}

Graph DrawingUnit::get_BST_graph(AVL *bst, sf::Vector2f ROOT, AVLNode *highlighted_node) {
	sf::Vector2f OFFSET(1000, 150);

	Graph vcl;
	loadingBST(bst -> root, vcl, ROOT, OFFSET, highlighted_node);
	return vcl;
}
void DrawingUnit::draw_BST(AVL* bst, sf::Vector2f ROOT, AVLNode* highlighted_node) {
	draw_graph(get_BST_graph(bst, ROOT, highlighted_node));
}


Node loadingTrie(TrieNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET, TrieNode* highlighted_node) {
	if (root == nullptr) return Node();
	if (root == nullptr) return Node();
	Node cur = graph.add_node(Node(std::to_string(root -> cnt), ROOT, (unsigned long long)root,
		CIRCLE, root == highlighted_node));
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

		Node child = loadingTrie(root->child[i], graph, nROOT, nOFFSET, highlighted_node);
		graph.add_edge(cur, child, std::string(1, '0' + i));
	}
	
	return cur;
}

Graph DrawingUnit::get_trie_graph(Trie* tri, sf::Vector2f ROOT, TrieNode* highlighted_node) {
	sf::Vector2f OFFSET(1800, 180);

	Graph vcl;
	loadingTrie(tri->root, vcl, ROOT, OFFSET, highlighted_node);
	return vcl;
}
void DrawingUnit::draw_trie(Trie *tri, sf::Vector2f ROOT, TrieNode *highlighted_node) {
	draw_graph(get_trie_graph(tri, ROOT, highlighted_node));
}