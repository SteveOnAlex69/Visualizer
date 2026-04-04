#include <Drawing/DrawingUnit.hpp>
#include <Helper.hpp>

DrawingUnit::DrawingUnit() {

}
DrawingUnit::DrawingUnit(sf::RenderWindow *window, sf::Font f) {
	appwindow = window;
	font = f;
}

void DrawingUnit::draw_node(Node* i) {
	sf::Color border_color = FIRST_COLOR;
	if (i->is_special()) border_color = sf::Color::Yellow;
	if (i -> get_shape() == NO) {
	}
	else if (i -> get_shape() == CIRCLE) {
		sf::CircleShape cyka(6 * 7);
		cyka.setPosition(i -> get_pos());
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(border_color);
		cyka.setFillColor(BACKGROUND);
		appwindow -> draw(cyka);
	}
	else if (i -> get_shape() == SQUARE || i -> get_shape() == DIAMOND) {
		sf::RectangleShape rect(sf::Vector2f(6 * 7 * 2, 6 * 7 * 2));
		if (i -> get_shape() == DIAMOND) {
			rect.setRotation(sf::Vector2f(1, 1).angle());
		}
		rect.setPosition(i -> get_pos());
		rect.setOrigin(sf::Vector2f(rect.getLocalBounds().size) * 0.5f);
		rect.setOutlineThickness(6);
		rect.setOutlineColor(border_color);
		rect.setFillColor(BACKGROUND);
		appwindow -> draw(rect);
	}
	else if (i -> get_shape() == TRIANGLE) {
		sf::CircleShape cyka(67, 3);
		cyka.setPosition(i -> get_pos());
		cyka.setOrigin(cyka.getLocalBounds().size * 0.5f + cyka.getLocalBounds().position
			+ sf::Vector2f(0, cyka.getLocalBounds().size.y * 0.1f));
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(border_color);
		cyka.setFillColor(BACKGROUND);
		appwindow -> draw(cyka);
	}

	sf::Text inner(font);
	inner.setString(i -> get_val());
	inner.setCharacterSize(36);
	inner.setFillColor(border_color);
	inner.setPosition(i -> get_pos());
	sf::FloatRect textRect = inner.getLocalBounds();
	inner.setOrigin(textRect.size * 0.5f + textRect.position);
	appwindow -> draw(inner);
}

void DrawingUnit::draw_graph(Graph& graph) {
	std::vector<Node*> li = graph.get_node_list();
	std::vector<Edge> relation = graph.get_edges_idx();

	for (auto i : relation) {
		Node *u = i.first, *v = i.second;
		sf::Vector2f fi = u->get_pos(), se = v->get_pos();
		sf::RectangleShape line;
		line.setSize(Point2((fi - se).length(), EDGE_WIDTH));
		line.setOrigin(Point2(0, EDGE_WIDTH / 2));
		line.setFillColor(FIRST_COLOR);
		line.setPosition(fi);
		line.setRotation((se - fi).angle());
		appwindow -> draw(line);

		// draw arrow
		sf::Vector2f arrow_pos = se + sf::Vector2f(50, 0).rotatedBy((fi - se).angle());
		sf::CircleShape arrow(18, 3);
		arrow.setRotation((se - fi).angle() + sf::Vector2f(0, 1).angle());
		arrow.setPosition(arrow_pos);
		arrow.setOrigin(sf::Vector2f(arrow.getLocalBounds().size) * 0.5f);
		arrow.setFillColor(FIRST_COLOR);

		appwindow->draw(arrow);

		if (i.val.size()) {
			sf::CircleShape cyka(18);
			cyka.setPosition((fi + se) * 0.5f);
			cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
			cyka.setFillColor(BACKGROUND);

			appwindow->draw(cyka);

			sf::Text inner(font);
			inner.setString(i.val);
			inner.setCharacterSize(30);
			inner.setFillColor(FIRST_COLOR);
			inner.setPosition((fi + se) * 0.5f);
			sf::FloatRect textRect = inner.getLocalBounds();
			inner.setOrigin(textRect.size * 0.5f + textRect.position);
			appwindow->draw(inner);
		}
	}
	for (auto i : li) draw_node(i);
}

void DrawingUnit::draw_linked_list(LinkedList *linked_list, sf::Vector2f ROOT, LLNode *highlighted_node) {
	std::vector<LLNode*> arr = linked_list -> get_array();
	sf::Vector2f OFFSETX(200, 0);
	sf::Vector2f OFFSETY(0, 150);
	Graph vcl;

	Node* prev = vcl.add_node(new Node("", ROOT, SQUARE, true));

	for (int i = 0; i < (int)arr.size(); ++i) {
		int y = i / 7;
		int x = i % 7;
		if (y % 2) x = 6 - x;
		x++;

		Node* cur = vcl.add_node(new Node(arr[i]->val, ROOT + OFFSETX * (1.0f * x) + OFFSETY * (1.0f * y),
			SQUARE, arr[i] == highlighted_node));
		vcl.add_edge(prev, cur);
		prev = cur;
	}
	draw_graph(vcl);
}


void DrawingUnit::draw_hash_map(HashMapChaining *hash_map, sf::Vector2f ROOT, LLNode* highlighted_node) {
	sf::Vector2f OFFSETY(0, 120);
	sf::Vector2f OFFSETX(150, 0);

	Graph vcl;
	for (int i = 0; i < hash_map -> get_size(); ++i) {
		vcl.add_node(new Node(std::to_string(i), ROOT + OFFSETY * (1.0f * i), NO));
		draw_linked_list(&(hash_map -> buckets[i]), ROOT + OFFSETY * (1.0f * i) + OFFSETX, highlighted_node);
	}
	draw_graph(vcl);
}


void DrawingUnit::draw_hash_map(HashMapLinearProbing *hash_map, sf::Vector2f ROOT) {
	sf::Vector2f OFFSETX(0, 150);
	sf::Vector2f OFFSETY(120, 0);

	Graph vcl;
	for (int i = 0; i < hash_map -> get_size(); ++i) {
		vcl.add_node(new Node(std::to_string(i), ROOT + OFFSETY, NO));

		if (hash_map -> slots[i] != "") {
			vcl.add_node(new Node(hash_map -> slots[i], ROOT, SQUARE));
		}
		ROOT += OFFSETX;
	}
	draw_graph(vcl);
}


template <class BSTNode>
Node* loadingBST(BSTNode*root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET, BSTNode *highlighted_node) {
	if (root == nullptr) return nullptr;
	Node* cur = graph.add_node(new Node(std::to_string(root -> val), ROOT, CIRCLE, root == highlighted_node));
	OFFSET.x *= 0.4f;
	if (root->childL) {
		Node* left_child = 
			loadingBST(root->childL, graph, ROOT + sf::Vector2f(-OFFSET.x, OFFSET.y), OFFSET, highlighted_node);
		graph.add_edge(cur, left_child);
	}
	if (root->childR) {
		Node* right_child = 
			loadingBST(root->childR, graph, ROOT + sf::Vector2f(OFFSET.x, OFFSET.y), OFFSET, highlighted_node);
		graph.add_edge(cur, right_child);
	}
	return cur;
}

void DrawingUnit::draw_BST(AVL *bst, sf::Vector2f ROOT, AVLNode *highlighted_node) {
	sf::Vector2f OFFSET(1000, 150);

	Graph vcl;
	loadingBST(bst -> root, vcl, ROOT, OFFSET, highlighted_node);
	draw_graph(vcl);
}


Node* loadingTrie(TrieNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET, TrieNode* highlighted_node) {
	if (root == nullptr) return nullptr;
	Node* cur = graph.add_node(new Node(std::to_string(root -> cnt), ROOT, CIRCLE, root == highlighted_node));
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

		Node* child = loadingTrie(root->child[i], graph, nROOT, nOFFSET, highlighted_node);
		graph.add_edge(cur, child, std::string(1, '0' + i));
	}
	
	return cur;
}

void DrawingUnit::draw_trie(Trie *tri, sf::Vector2f ROOT, TrieNode *highlighted_node) {
	sf::Vector2f OFFSET(1800, 150);

	Graph vcl;
	loadingTrie(tri -> root, vcl, ROOT, OFFSET, highlighted_node);
	draw_graph(vcl);
}