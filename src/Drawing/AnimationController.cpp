#include <Drawing/AnimationController.hpp>
#include <Drawing/GraphExtractor.hpp>

AnimationController::AnimationController(AnimationUnit* a, GeneralData* d) {
	anim = a;
	ds = d;
	flow = 1;
	current_command = 0;
}
void AnimationController::update_timer(float delta) { 
	anim->update_timer(delta * flow);
}

void AnimationController::update_graph(int state) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, state);
	anim -> add_state(VisualizerState(GraphExtractor::get_graph(*ds), current_sudo));
}

void AnimationController::load_kruskal() {
	current_command = 3;
	anim -> force_latest();
	void* current_ds = ds -> get_current_structure();
	anim -> clear_graph();
	for (int i = 0; ; ++i) {
		int idx = 1;
		if (i % 2 == 0 && i > 0) {
			std::vector<KruskalEdge> e = ((Kruskal*)current_ds)->run_kruskal();
			if (e[i / 2 - 1].flag) idx = 3;
			else idx = 2;
		}
		Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, idx);
		Graph cur = GraphExtractor::get_kruskal_graph(
			(Kruskal*)current_ds, GRAPH_ROOT, i
		);
		if (cur.get_node_list().size() == 0) break;
		anim -> add_state(VisualizerState(cur, current_sudo));
	}
}
void AnimationController::execute_graph_search(std::vector<void*> searched_nodes) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 1);
	anim->force_latest();
	void* current_ds = ds->get_current_structure();
	for (auto i : searched_nodes) {
		anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), current_sudo));
	}
	if (searched_nodes.size() && searched_nodes.back() != nullptr) {
		Pseudocode karen_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 2);
		anim->add_state(VisualizerState(
			GraphExtractor::get_graph(*ds, searched_nodes.back(), 2), karen_sudo));
	}
}
void AnimationController::load_dijkstra(std::string x, std::string y) {
	current_command = 3;

	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command);
	int u = std::stoi(x), v = std::stoi(y);

	Dijkstra* dih = (Dijkstra*)ds -> get_current_structure();
	std::vector<int> vertices = dih->get_vertices();
	if (std::binary_search(vertices.begin(), vertices.end(), u) &&
		std::binary_search(vertices.begin(), vertices.end(), v)) {
		anim -> force_latest();

		std::vector<GraphState> spread_adventure =
			dih->run_dijkstra(u, v);

		std::vector<int> lmao;
		std::vector<std::pair<int, int>> edges1;

		std::vector<long long> charlie_kirk_dikdik(vertices.size(), 1e18);
		Pseudocode sudo = Pseudocode((int)ds->get_current_type() + 1, current_command);
		Graph cur = GraphExtractor::get_dijkstra_graph(
			dih, GRAPH_ROOT, lmao, edges1, charlie_kirk_dikdik
		);
		anim->add_state(VisualizerState(cur, sudo));

		for (auto i : spread_adventure) {
			for (auto v : i.vertices) lmao.push_back(v);
			for (auto e : i.edges) edges1.push_back(e);

			int val = 1; 
			if (i.type != 1) val = 3;
			Pseudocode sudo1 = Pseudocode((int)ds->get_current_type() + 1, current_command, val);
			Graph cur = GraphExtractor::get_dijkstra_graph(
				dih, GRAPH_ROOT, lmao, edges1, i.dih
			);
			anim->add_state(VisualizerState(cur, sudo1));

			if (i.type == 1) {
				for (auto v : i.vertices) {
					lmao.push_back(v);
					lmao.push_back(v);
				}

				Pseudocode sudo1 = Pseudocode((int)ds->get_current_type() + 1, current_command, 1);
				Graph cur = GraphExtractor::get_dijkstra_graph(
					dih, GRAPH_ROOT, lmao, edges1, i.dih
				);
				anim->add_state(VisualizerState(cur, sudo1));

				for (auto v : i.vertices) {
					lmao.pop_back();
					lmao.pop_back();
				}

			}
		}

		Pseudocode sudo4 = Pseudocode((int)ds->get_current_type() + 1, current_command, 2);
		std::vector<int> matter = dih->get_shortest_path(u, v);

		charlie_kirk_dikdik = spread_adventure.back().dih;

		for (int i = 0; i < (int)matter.size(); ++i) {
			lmao.push_back(matter[i]);
			lmao.push_back(matter[i]);
			if (i > 0) {
				edges1.push_back(std::make_pair(matter[i - 1], matter[i]));
				edges1.push_back(std::make_pair(matter[i - 1], matter[i]));
			}
			Graph cur = GraphExtractor::get_dijkstra_graph(
				dih, GRAPH_ROOT, lmao, edges1, charlie_kirk_dikdik
			);
			anim->add_state(VisualizerState(cur, sudo4));
		}
	}
}
void AnimationController::handle_insertion(std::string s) {
	current_command = 1;
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command);

	anim->force_latest();
	void* current_ds = ds -> get_current_structure();
	switch (ds -> get_current_type()) {
	case LINKED_LIST:
	case HASHMAP_CHAIN:
	{
		ds->insert(s); update_graph(1);
		break;
	}
	case AVL_TREE:
	{
		std::vector<void*> searched_nodes = ((AVL*)current_ds)->search_before_insert(std::stoi(s));
		std::vector<bool> sec = ((AVL*)current_ds)->search_before_insert_direction(std::stoi(s));
		int idx = 0;
		for (auto i : searched_nodes) {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 1 + sec[idx++]);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), sudosudo));
		}
		if (searched_nodes.size() && searched_nodes.back() != nullptr) {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 3);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched_nodes.back(), 2), sudosudo));
		}

		ds -> insert(s); update_graph(4);

		searched_nodes = ((AVL*)current_ds)->search_before_insert(std::stoi(s));
		std::reverse(searched_nodes.begin(), searched_nodes.end());
		for (auto i : searched_nodes) {
			((AVL*)current_ds)->check_correct_depth();
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 5);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), sudosudo));

			if (((AVLNode*)i)->check_unbalanced()) {
				((AVL*)current_ds)->balance_deepest_node();
				((AVL*)current_ds)->check_correct_depth();
				update_graph(6);
			}
		}

		update_graph();
		break;
	}
	case TRIE:
	{
		std::vector<void*> searched_nodes = ds -> search(s);
		if (searched_nodes.back() == nullptr) searched_nodes.pop_back();
		for (auto i : searched_nodes) {
			Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 1);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), current_sudo));
		}
		while (true) {
			int val = ds -> insert(s);

			if (val == 2)
				update_graph(2);

			int type = 1;
			if (val == 1) type = 3;
			Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, type);
			std::vector<void*> searched_nodes = ds -> search(s);
			if (searched_nodes.back() == nullptr) searched_nodes.pop_back();
			anim ->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched_nodes.back(), 3 - val), current_sudo));
			if (val == 1) break;
		}


		break;
	}
	case KRUSKAL:
	case DIJKSTRA:
	{
		ds -> insert(s); update_graph(1);
		break;
	}
	}
}
void AnimationController::handle_deletion(std::string s) {
	current_command = 2;
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command);

	anim->force_latest();
	void* current_ds = ds -> get_current_structure();
	switch (ds -> get_current_type()) {
	case LINKED_LIST:
	case HASHMAP_CHAIN:
	{
		std::vector<void*> searched = ds -> search(s);
		execute_graph_search(searched);
		int val = ds -> erase(s);
		update_graph(3);
		break;
	}
	case TRIE:
	{
		std::vector<void*> searched = ds -> search(s);
		for (auto i : searched) {
			int val = 1;
			if (i == 0) val = 2;
			Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, val);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), current_sudo));
		}
		if (searched.back()) {
			ds->erase(s);
			Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 3);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back()), current_sudo));

			if (((Trie*)current_ds)->get_count(s) > 0) {
				Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 4);
				anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds), current_sudo));
			}
			else {
				while (true) {
					std::vector<void*> searched = ds->search(s);
					while (searched.size() && searched.back() == nullptr) searched.pop_back();

					Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 5);
					anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back(), 1), current_sudo));

					TrieNode* nud = (TrieNode*)searched.back();
					if ((nud -> cnt > 0) || (nud -> no_bitch() == false)) {
						Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 6);
						anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds), current_sudo));
						return;
					}
					else {
						Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 7);
						anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back(), 2), current_sudo));

						((Trie*)current_ds)->erase(s);

						Pseudocode karen_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 7);
						anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds), karen_sudo));
					}

				}
			}

		}
		break;
	}
	case AVL_TREE:
	{
		std::vector<void*> searched = ds->search(s);
		std::vector<bool> direction = ((AVL*)ds->get_current_structure())->search_direction(std::stoi(s));
		int idx = 0;
		for (int i = 0; i < (int)searched.size(); ++i) {
			int type = -1;
			if (i > 0) type = direction[i - 1] + 1;
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, type);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched[i]), sudosudo));
		}

		int mode, pima;
		if (searched.back() != nullptr) {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 4);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back(), 2), sudosudo));

			AVLNode* shit = (AVLNode*)searched.back();
			if (shit->right_child_depth()) {
				mode = 7;
				pima = shit->childR->get_min();
			}
			else {
				mode = 8;
				searched.pop_back();
			}
		}

		if (ds->erase(s)) {
			((AVL*)ds->get_current_structure())->check_correct_depth();
			update_graph(mode);
			if (mode == 7) {
				searched = ((AVL*)ds->get_current_structure())->search_before_insert(pima);
			}

			std::reverse(searched.begin(), searched.end());
			for (auto i : searched) {
				Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 5);
				anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), sudosudo));
				

				if (((AVLNode*)i)->check_unbalanced()) {
					((AVL*)current_ds)->balance_deepest_node();			
					((AVL*)current_ds)->check_correct_depth();

					update_graph(6);
				}
			}
			update_graph();
		}
		else {
			update_graph(3);
		}
		break;
	}
	case KRUSKAL:
	case DIJKSTRA:
	{
		if (ds -> erase(s)) update_graph(1);
		break;
	}
	}
}

void AnimationController::handle_search(std::string s) {
	current_command = 3;
	switch (ds->get_current_type()) {
	case AVL_TREE:
	{
		std::vector<void*> searched = ds->search(s);
		std::vector<bool> direction = ((AVL*)ds->get_current_structure())->search_direction(std::stoi(s));

		for (int i = 0; i < (int)searched.size(); ++i) {
			int type = -1;
			if (i > 0) type = direction[i - 1] + 1;
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, type);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched[i]), sudosudo));
		}

		if (searched.back() == nullptr) {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 3);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds), sudosudo));
		}
		else {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 4);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back(), 2), sudosudo));
		}
		return;
	}
	case TRIE:
	{
		std::vector<void*> searched = ds->search(s);

		for (int i = 0; i < (int)searched.size(); ++i) {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 1);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched[i]), sudosudo));
		}

		if (searched.back() == nullptr) {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 2);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds), sudosudo));
		}
		else {
			Pseudocode sudosudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 3);
			anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back(), 2), sudosudo));
		}
		return;
	}
	default:
	{
		std::vector<void*> searched = ds->search(s);
		execute_graph_search(searched);
		return;
	}
	}
}


void AnimationController::handle_update(std::string x, std::string y) {
	current_command = 4;
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command);

	void* current_ds = ds->get_current_structure();
	switch (ds->get_current_type()) {
	case LINKED_LIST:
	{
		std::vector<void*> searched = ds->search(x);
		execute_graph_search(searched);

		if (ds->update(x, y)) {
			Pseudocode karen_sudo = Pseudocode((int)ds->get_current_type() + 1, current_command, 3);
			anim->add_state(VisualizerState(
				GraphExtractor::get_graph(*ds, searched.back(), 2), karen_sudo));
		}
		break;
	}
	case HASHMAP_CHAIN:
	case TRIE:
	case AVL_TREE:
	case KRUSKAL:
	case DIJKSTRA:
		debug_error("called UPDATE when the data structure was not LINKED LIST");
		break;
	}
}

void AnimationController::clear_current_ds() {
	current_command = 0;
	anim->force_latest();
	ds->clear();
	update_graph();
}

void AnimationController::handle_init(std::string s) {
	current_command = 0;
	anim->force_latest();
	ds->clear();
	update_graph();

	ds->init(s);
	update_graph();
}


bool AnimationController::is_empty() { return anim->is_empty(); }
void AnimationController::clear_graph() { anim->clear_graph(); }
VisualizerState AnimationController::get_state() { return anim->get_state(); }


void AnimationController::jump_to_back() {
	anim->jump_to_back();
}
void AnimationController::jump_to_front() {
	anim->jump_to_front();
}
void AnimationController::jump_back() {
	anim->jump_back();
}
void AnimationController::jump_front() {
	anim->jump_front();

}
void AnimationController::toggle_flow() {
	flow = 1 - flow;
}

int AnimationController::get_flow() { return flow; }