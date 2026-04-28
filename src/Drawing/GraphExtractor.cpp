#include <Drawing/GraphExtractor.hpp>


template <class T>
int count_occurence(std::vector<T>& a, T b) {
	return std::upper_bound(a.begin(), a.end(), b) -
		std::lower_bound(a.begin(), a.end(), b);
}


Node loadingBST(AVLNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET,
	std::vector<void*> highlighted) {
	if (root == nullptr) return Node();

	int color = 0;
	int cnt = count_occurence(highlighted, (void*)root);
	if (cnt == 1) color = 2;
	else if (cnt >= 2) color = 3;
	Node cur(std::to_string(root->val), ROOT, (unsigned long long) root,
		CIRCLE, color
	);
	cur.set_weight(std::to_string(root -> depth));
	graph.add_node(cur);
	if (root->childL) {
		int sz = 1;
		if (root->childL->childR) sz += root->childL->childR->get_tree_size();
		Node left_child =
			loadingBST(root->childL, graph, ROOT + sf::Vector2f(-OFFSET.x * sz, OFFSET.y), OFFSET,
				highlighted);
		graph.add_edge(cur, left_child);
	}
	if (root->childR) {
		int sz = 1;
		if (root->childR->childL) sz += root->childR->childL->get_tree_size();
		Node right_child =
			loadingBST(root->childR, graph, ROOT + sf::Vector2f(OFFSET.x * sz, OFFSET.y), OFFSET,
				highlighted);
		graph.add_edge(cur, right_child);
	}
	return cur;
}


Node loadingTrie(TrieNode* root, Graph& graph, sf::Vector2f ROOT, sf::Vector2f OFFSET,
	std::vector<void*> highlighted) {
	if (root == nullptr) return Node();
	
	float x = ROOT.x - (root->get_leaf_count()) * OFFSET.x * 0.5f;

	int color = 0;	
	int cnt = count_occurence(highlighted, (void*)root);
	if (cnt == 1) color = 2;
	else if (cnt >= 2) color = 3;
	Node cur = graph.add_node(Node(std::to_string(root->cnt), ROOT, (unsigned long long)root,
		CIRCLE, color
	));
	int child_cnt = 0;
	for (int i = 0; i < ALPHA; ++i) if (root->child[i]) child_cnt++;
	if (child_cnt == 0) return cur;

	for (int i = 0; i < ALPHA; ++i) if (root->child[i]) {
		x += (root->child[i]->get_leaf_count()) * OFFSET.x * 0.5f;

		Node child = loadingTrie(root->child[i], graph, sf::Vector2f(x, ROOT.y + OFFSET.y), OFFSET, highlighted);
		graph.add_edge(cur, child, std::string(1, '0' + i));

		x += (root->child[i]->get_leaf_count()) * OFFSET.x * 0.5f;
	}

	return cur;
}

namespace GraphExtractor {


	Graph get_linked_list_graph(LinkedList* linked_list, sf::Vector2f ROOT,
		std::vector<void*> highlighted, int mod) {
		std::sort(highlighted.begin(), highlighted.end());


		std::vector<LLNode*> arr = linked_list->get_array();
		sf::Vector2f OFFSETX(200, 0);
		sf::Vector2f OFFSETY(0, 150);
		Graph vcl;

		Node prev = Node("", ROOT, (unsigned long long)arr[0], SQUARE, 1);
		prev.set_weight("Head");
		vcl.add_node(prev);

		for (int i = 1; i < (int)arr.size(); ++i) {
			int y = (i - 1) / mod;
			int x = (i - 1) % mod;
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
			vcl.add_node(Node(std::to_string(i), ROOT, 0, NO));
			Graph single_line = get_linked_list_graph(&(hash_map->buckets[i]),
				ROOT + OFFSETX, highlighted);

			std::vector<Node> vertices = single_line.get_node_list();
			std::vector<Edge> edges = single_line.get_edges_idx();

			for (Node j : vertices) {
				vcl.add_node(j);
				ROOT.y = std::max(ROOT.y, j.get_pos().y);
			}
			ROOT += OFFSETY;
			for (Edge e : edges)
				vcl.add_edge(e.first, e.second, e.val);
		}
		return vcl;
	}

	Graph get_BST_graph(AVL* bst, sf::Vector2f ROOT, std::vector<void*> highlighted) {
		sf::Vector2f OFFSET(100, 136);
		std::sort(highlighted.begin(), highlighted.end());
		Graph vcl;
		loadingBST(bst->root, vcl, ROOT, OFFSET, highlighted);
		return vcl;
	}


	Graph get_trie_graph(Trie* tri, sf::Vector2f ROOT, std::vector<void*> highlighted) {
		sf::Vector2f OFFSET(167, 167); 
		std::sort(highlighted.begin(), highlighted.end());

		Graph vcl;
		loadingTrie(tri->root, vcl, ROOT, OFFSET, highlighted);
		return vcl;
	}

	Graph get_kruskal_graph(Kruskal* kurst, sf::Vector2f ROOT, int it) {
		Graph ans;
		std::vector<int> vertices = kurst->get_vertices();
		std::vector<KruskalEdge> e = kurst->run_kruskal();

		if (it >= 0 && it > e.size() * 2) return ans;
		DSU mst(vertices.size());
		for (int i = 0; i < it / 2; ++i) {
			int u = e[i].u, v = e[i].v;
			u = std::lower_bound(vertices.begin(), vertices.end(), u) - vertices.begin();
			v = std::lower_bound(vertices.begin(), vertices.end(), v) - vertices.begin();
			mst.join_set(u, v);
		}

		sf::Vector2f CIRCLE_CENTER = screen_center;
		sf::Vector2f ARM = sf::Vector2f(300.0f, 0);			
		sf::Angle bruh = sf::radians(67), one_rotation = sf::degrees(360.0f / vertices.size());
		float eccentric = 1.5;
		
		for (int i = 0; i < (int)vertices.size(); ++i) {
			sf::Vector2f DIH = ARM.rotatedBy(bruh + one_rotation * i);
			DIH.x *= eccentric;

			sf::Vector2f jitter = sf::Vector2f((vertices[i] * 67 + 18) % 36 - 18, 
				(vertices[i] * 69 + 9) % 36 - 18);

			int u = mst.find_set(i);
			int sp = 0;
			if (mst.get_size(i) > 1) sp = 3;

			Node cur = Node(std::to_string(vertices[i]), CIRCLE_CENTER + DIH + jitter,
				(unsigned long long)vertices[i],
				CIRCLE, false);
			cur.set_special(sp);

			ans.add_node(cur);
		}
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
					if (it == 1) {
						ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w),
							1);
						ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w),
							1);
					}
					else {
						ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w),
							1, FIFTH_COLOR);
						ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w),
							1, FIFTH_COLOR);
					}
				}
				else {
					if (it == 1) {
						ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w),
							1);
						ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w),
							1);
					}
					else {
						ans.add_edge(std::to_string(i.u), std::to_string(i.v), std::to_string(i.w),
							1, FOURTH_COLOR);
						ans.add_edge(std::to_string(i.v), std::to_string(i.u), std::to_string(i.w),
							1, FOURTH_COLOR);
					}
				}
				it -= 2;
			}
		}

		return ans;
	}


	Graph get_dijkstra_graph(Dijkstra* dik, sf::Vector2f ROOT,
		std::vector<int> highlight1, std::vector<std::pair<int, int>> edges1, std::vector<long long> dih) {

		std::sort(highlight1.begin(), highlight1.end());
		std::sort(edges1.begin(), edges1.end());

		Graph ans;
		std::vector<int> vertices = dik->get_vertices();

		while (dih.size() < vertices.size()) dih.push_back(1e18);

		sf::Vector2f CIRCLE_CENTER = screen_center;
		sf::Vector2f ARM = sf::Vector2f(300.0f, 0);
		sf::Angle bruh = sf::radians(67), one_rotation = sf::degrees(360.0f / vertices.size());
		float eccentric = 1.5;

		for (int i = 0; i < (int)vertices.size(); ++i) {
			sf::Vector2f DIH = ARM.rotatedBy(bruh + one_rotation * i);
			DIH.x *= eccentric;


			int node_color = 0;
			if (count_occurence(highlight1, vertices[i]) == 1) node_color = 2;
			if (count_occurence(highlight1, vertices[i]) == 2) node_color = 3;
			if (count_occurence(highlight1, vertices[i]) > 2) node_color = 1;

			sf::Vector2f jitter = sf::Vector2f((vertices[i] * 67 + 18) % 36 - 18,
				(vertices[i] * 69 + 9) % 36 - 18);

			Node cur(std::to_string(vertices[i]), CIRCLE_CENTER + DIH + jitter,
				(unsigned long long)vertices[i],
				CIRCLE, node_color);
			if (dih[i] == 1e18) cur.set_weight("oo");
			else cur.set_weight(std::to_string(dih[i]));
			ans.add_node(cur);
		}

		std::vector<DijkstraEdge> e = dik->get_edges();
		for (auto i : e) {
			sf::Color color = FIRST_COLOR;

			if (count_occurence(edges1, std::make_pair(i.u, i.v)) == 1) color = FOURTH_COLOR;
			if (count_occurence(edges1, std::make_pair(i.u, i.v)) == 2) color = FIFTH_COLOR;
			if (count_occurence(edges1, std::make_pair(i.u, i.v)) > 2) color = THIRD_COLOR;
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
			std::vector<long long> empty_dih;
			return get_dijkstra_graph(
				(Dijkstra*)current_ds, GRAPH_ROOT, empty_list, empty_edges, empty_dih
			);
			break;
		}
		Graph empty_graph;
		return empty_graph;
	}
}