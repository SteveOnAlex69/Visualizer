#include <Drawing/GraphExtractor.hpp>

Node loadingBST(AVLNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET,
	std::vector<void*> highlighted) {
	if (root == nullptr) return Node();


	int color = 0;
	int cnt = std::upper_bound(highlighted.begin(), highlighted.end(), root) -
		std::lower_bound(highlighted.begin(), highlighted.end(), root);
	if (cnt == 1) color = 2;
	else if (cnt >= 2) color = 3;
	Node cur = graph.add_node(Node(std::to_string(root->val), ROOT, (unsigned long long) root,
		CIRCLE, color
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


Node loadingTrie(TrieNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET,
	std::vector<void*> highlighted) {
	if (root == nullptr) return Node();
	if (root == nullptr) return Node();


	int color = 0;
	int cnt = std::upper_bound(highlighted.begin(), highlighted.end(), root) -
		std::lower_bound(highlighted.begin(), highlighted.end(), root);
	if (cnt == 1) color = 2;
	else if (cnt >= 2) color = 3;
	Node cur = graph.add_node(Node(std::to_string(root->cnt), ROOT, (unsigned long long)root,
		CIRCLE, color
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

namespace GraphExtractor {
	Graph get_linked_list_graph(LinkedList* linked_list, sf::Vector2f ROOT,
		std::vector<void*> highlighted) {
		std::sort(highlighted.begin(), highlighted.end());


		std::vector<LLNode*> arr = linked_list->get_array();
		sf::Vector2f OFFSETX(200, 0);
		sf::Vector2f OFFSETY(0, 150);
		Graph vcl;

		Node prev = vcl.add_node(Node("", ROOT, (unsigned long long)arr[0], SQUARE, 1));

		for (int i = 1; i < (int)arr.size(); ++i) {
			int y = (i - 1) / 7;
			int x = (i - 1) % 7;
			if (y % 2) x = 6 - x;
			x++;

			int color = 0;
			int cnt = std::upper_bound(highlighted.begin(), highlighted.end(), arr[i]) -
				std::lower_bound(highlighted.begin(), highlighted.end(), arr[i]);
			if (cnt == 1) color = 2;
			else if (cnt >= 2) color = 3;

			Node cur = vcl.add_node(Node(arr[i]->val, ROOT + OFFSETX * (1.0f * x) + OFFSETY * (1.0f * y),
				(unsigned long long) arr[i], SQUARE,
				color
			));
			vcl.add_edge(prev, cur);
			prev = cur;
		}
		return vcl;
	}

	Graph get_hash_map_graph(HashMapChaining* hash_map, sf::Vector2f ROOT,
		std::vector<void*> highlighted) {
		std::sort(highlighted.begin(), highlighted.end());

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

	Graph get_BST_graph(AVL* bst, sf::Vector2f ROOT, std::vector<void*> highlighted) {
		sf::Vector2f OFFSET(1000, 150);
		std::sort(highlighted.begin(), highlighted.end());

		Graph vcl;
		loadingBST(bst->root, vcl, ROOT, OFFSET, highlighted);
		return vcl;
	}


	Graph get_trie_graph(Trie* tri, sf::Vector2f ROOT, std::vector<void*> highlighted) {
		sf::Vector2f OFFSET(760, 167); // (1800, 800)
		std::sort(highlighted.begin(), highlighted.end());

		Graph vcl;
		loadingTrie(tri->root, vcl, ROOT, OFFSET, highlighted);
		return vcl;
	}

	Graph get_kruskal_graph(Kruskal* kurst, sf::Vector2f ROOT, int it) {
		Graph ans;
		std::vector<int> vertices = kurst->get_vertices();


		for (int i = 0; i < (int)vertices.size(); ++i) {
			int y = (i * 5) % 7;
			ans.add_node(Node(std::to_string(vertices[i]), ROOT + sf::Vector2f(i * 150.f, y * 100.0f),
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
						ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w),
							1, FOURTH_COLOR);
						ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w),
							1, FOURTH_COLOR);
					}
					it -= 2;
				}
			}
			if (it > 0) {
				Graph empty_graph;
				return empty_graph;
			}
		}

		std::vector<Edge> edging = ans.get_edges_idx();
		return ans;
	}


	Graph get_dijkstra_graph(Dijkstra* dik, sf::Vector2f ROOT,
		std::vector<int> highlight1, std::vector<int> highlight2,
		std::vector<std::pair<int, int>> edges1, std::vector<std::pair<int, int>> edges2) {
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
			ans.add_node(Node(std::to_string(vertices[i]), ROOT + sf::Vector2f(i * 150.f, y * 100.0f),
				(unsigned long long)vertices[i],
				CIRCLE, node_color));
		}
		std::vector<DijkstraEdge> e = dik->get_edges();
		for (auto i : e) {
			sf::Color color = FIRST_COLOR;
			if (std::find(edges1.begin(), edges1.end(), std::make_pair(i.u, i.v)) != edges1.end())
				color = FOURTH_COLOR;
			if (std::find(edges2.begin(), edges2.end(), std::make_pair(i.u, i.v)) != edges2.end())
				color = FIFTH_COLOR;
			ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w), 1, color);
		}
		return ans;
	}


	Graph get_graph(GeneralData& ds, void* highlighted, int cnt) {
		void* current_ds = ds.get_current_structure();
		std::vector<void*> search_nodes;
		if (highlighted) {
			while (cnt--)
				search_nodes.push_back(highlighted);
		}

		switch (ds.get_current_type()) {
		case LINKED_LIST:
			return get_linked_list_graph(
				(LinkedList*)current_ds, LINKED_LIST_POS, search_nodes);
		case HASHMAP_CHAIN:
			return get_hash_map_graph(
				(HashMapChaining*)current_ds, HASH_MAP_POS, search_nodes);
		case AVL_TREE:
			return get_BST_graph(
				(AVL*)current_ds, BST_POS, search_nodes);
		case TRIE:
			return get_trie_graph(
				(Trie*)current_ds, TRIE_POS, search_nodes);
		case KRUSKAL:
			return get_kruskal_graph(
				(Kruskal*)current_ds, GRAPH_ROOT
			);
		case DIJKSTRA:
			std::vector<int> empty_list;
			std::vector<std::pair<int, int>> empty_edges;
			return get_dijkstra_graph(
				(Dijkstra*)current_ds, GRAPH_ROOT, empty_list, empty_list, empty_edges, empty_edges
			);

			break;
		}
		Graph empty_graph;
		return empty_graph;
	}
}