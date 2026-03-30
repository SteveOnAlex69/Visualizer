#include <Drawing/DrawingUnit.hpp>
#include <Helper.hpp>

DrawingUnit::DrawingUnit() {

}
DrawingUnit::DrawingUnit(sf::RenderWindow *window, sf::Font f) {
	appwindow = window;
	font = f;
}

void DrawingUnit::draw_node(Node* i) {
	if (i -> get_shape() == NO) {
	}
	else if (i -> get_shape() == CIRCLE) {
		sf::CircleShape cyka(6 * 7);
		cyka.setPosition(i -> get_pos());
		cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(FORESKIN);
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
		rect.setOutlineColor(FORESKIN);
		rect.setFillColor(BACKGROUND);
		appwindow -> draw(rect);
	}
	else if (i -> get_shape() == TRIANGLE) {
		sf::CircleShape cyka(67, 3);
		cyka.setPosition(i -> get_pos());
		cyka.setOrigin(cyka.getLocalBounds().size * 0.5f + cyka.getLocalBounds().position
			+ sf::Vector2f(0, cyka.getLocalBounds().size.y * 0.1f));
		cyka.setOutlineThickness(6);
		cyka.setOutlineColor(FORESKIN);
		cyka.setFillColor(BACKGROUND);
		appwindow -> draw(cyka);
	}

	sf::Text inner(font);
	inner.setString(i -> get_val());
	inner.setCharacterSize(36);
	inner.setFillColor(FORESKIN);
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
		line.setFillColor(FORESKIN);
		line.setPosition(fi);
		line.setRotation((se - fi).angle());
		appwindow -> draw(line);

		

		if (i.val.size()) {
			sf::CircleShape cyka(15);
			cyka.setPosition((fi + se) * 0.5f);
			cyka.setOrigin(sf::Vector2f(cyka.getLocalBounds().size) * 0.5f);
			cyka.setFillColor(BACKGROUND);

			appwindow->draw(cyka);

			sf::Text inner(font);
			inner.setString(i.val);
			inner.setCharacterSize(24);
			inner.setFillColor(FORESKIN);
			inner.setPosition((fi + se) * 0.5f);
			sf::FloatRect textRect = inner.getLocalBounds();
			inner.setOrigin(textRect.size * 0.5f + textRect.position);
			appwindow->draw(inner);
		}
	}
	for (auto i : li) draw_node(i);
}

void DrawingUnit::draw_linked_list(LinkedList& linked_list, sf::Vector2f ROOT) {
	std::vector<int> arr = linked_list.get_array();
	sf::Vector2f OFFSET(200, 0);
	Graph vcl;
	Node* prev = nullptr;
	for (int i = 0; i < (int)arr.size(); ++i) {
		Node* cur = vcl.add_node(new Node(std::to_string(arr[i]), ROOT + OFFSET * (1.0f * i), SQUARE));
		if (i > 0) vcl.add_edge(prev, cur);
		prev = cur;
	}
	draw_graph(vcl);
}


void DrawingUnit::draw_hash_map(HashMapChaining& hash_map, sf::Vector2f ROOT) {
	sf::Vector2f OFFSETX(0, 150);
	sf::Vector2f OFFSETY(150, 0);

	Graph vcl;
	for (int i = 0; i < hash_map.get_size(); ++i) {
		vcl.add_node(new Node(std::to_string(i), ROOT + OFFSETX * (1.0f * i), NO));
		draw_linked_list(hash_map.buckets[i], ROOT + OFFSETX * (1.0f * i) + OFFSETY);
	}
	draw_graph(vcl);
}


void DrawingUnit::draw_hash_map(HashMapLinearProbing& hash_map, sf::Vector2f ROOT) {
	sf::Vector2f OFFSETX(0, 150);
	sf::Vector2f OFFSETY(150, 0);

	Graph vcl;
	for (int i = 0; i < hash_map.get_size(); ++i) {
		vcl.add_node(new Node(std::to_string(i), ROOT + OFFSETY, NO));

		if (hash_map.slots[i] != -1) {
			vcl.add_node(new Node(std::to_string(hash_map.slots[i]), ROOT, SQUARE));
		}
		ROOT += OFFSETX;
	}
	draw_graph(vcl);
}


template <class BSTNode>
Node* loadingBST(BSTNode*root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET) {
	if (root == nullptr) return nullptr;
	Node* cur = graph.add_node(new Node(std::to_string(root -> val), ROOT, CIRCLE));
	OFFSET.x *= 0.4f;
	if (root->childL) {
		Node* left_child = loadingBST(root->childL, graph, ROOT + sf::Vector2f(-OFFSET.x, OFFSET.y), OFFSET);
		graph.add_edge(cur, left_child);
	}
	if (root->childR) {
		Node* right_child = loadingBST(root->childR, graph, ROOT + sf::Vector2f(OFFSET.x, OFFSET.y), OFFSET);
		graph.add_edge(cur, right_child);
	}
	return cur;
}

template <class Tree> 
void DrawingUnit::draw_BST(Tree& bst, sf::Vector2f ROOT) {
	sf::Vector2f OFFSET(1000, 150);

	Graph vcl;
	loadingBST(bst.root, vcl, ROOT, OFFSET);
	draw_graph(vcl);
}

template void DrawingUnit::draw_BST<BST>(BST& bst, sf::Vector2f ROOT);
template void DrawingUnit::draw_BST<AVL>(AVL& bst, sf::Vector2f ROOT);


Node* loadingTrie(TrieNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET) {
	if (root == nullptr) return nullptr;
	Node* cur = graph.add_node(new Node(std::to_string(root -> cnt), ROOT, CIRCLE));
	int child_cnt = 0;
	for (int i = 0; i < 26; ++i) if (root->child[i]) child_cnt++;
	if (child_cnt == 0) return cur;

	int cur_child = 0;
	sf::Vector2f nOFFSET = sf::Vector2f(OFFSET.x / child_cnt, OFFSET.y);
	for (int i = 0; i < 26; ++i) if (root->child[i]) {
		cur_child++;
		sf::Vector2f nROOT = ROOT;
		nROOT.y += OFFSET.y;
		nROOT.x += OFFSET.x * (-0.5f + (cur_child - 0.5f) / child_cnt);

		Node* child = loadingTrie(root->child[i], graph, nROOT, nOFFSET);
		graph.add_edge(cur, child, std::string(1, 'a' + i));
	}
	
	return cur;
}

void DrawingUnit::draw_trie(Trie& tri, sf::Vector2f ROOT) {
	sf::Vector2f OFFSET(1800, 150);

	Graph vcl;
	loadingTrie(tri.root, vcl, ROOT, OFFSET);
	draw_graph(vcl);
}