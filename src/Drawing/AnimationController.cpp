#include <Drawing/AnimationController.hpp>
#include <Drawing/GraphExtractor.hpp>

AnimationController::AnimationController(AnimationUnit* a, GeneralData* d) {
	anim = a;
	ds = d;
	flow = 1;
}
void AnimationController::update_timer(float delta) {
	anim->update_timer(delta * flow);
}

void AnimationController::update_graph(bool flag) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);
	anim -> add_state(VisualizerState(GraphExtractor::get_graph(*ds), current_sudo), 
		flag);
}

void AnimationController::load_kruskal() {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);
	anim -> force_latest();
	void* current_ds = ds -> get_current_structure();
	anim -> clear_graph();
	for (int i = 0; ; ++i) {
		Graph cur = GraphExtractor::get_kruskal_graph(
			(Kruskal*)current_ds, GRAPH_ROOT, i
		);
		if (cur.get_node_list().size() == 0) break;
		anim -> add_state(VisualizerState(cur, current_sudo), 0);
	}
}
void AnimationController::execute_graph_search(std::vector<void*> searched_nodes) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);
	anim->force_latest();
	void* current_ds = ds->get_current_structure();
	for (auto i : searched_nodes) {
		anim->add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), current_sudo), 
			0);
	}
	if (searched_nodes.size() && searched_nodes.back() != nullptr)
		anim->add_state(VisualizerState(
			GraphExtractor::get_graph(*ds, searched_nodes.back(), 2), current_sudo), 0);
}
void AnimationController::load_dijkstra(std::string x, std::string y) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);
	int u = std::stoi(x), v = std::stoi(y);

	Dijkstra* dih = (Dijkstra*)ds -> get_current_structure();
	std::vector<int> vertices = dih->get_vertices();
	if (std::binary_search(vertices.begin(), vertices.end(), u) &&
		std::binary_search(vertices.begin(), vertices.end(), v)) {
		anim -> force_latest();

		std::vector<std::pair<int, int>> spread_adventure =
			dih->run_dijkstra(u, v);

		std::vector<int> lmao;
		std::vector<int> matter;
		std::vector<std::pair<int, int>> edges1, edges2;
		for (auto i : spread_adventure) {
			lmao.push_back(i.first);
			edges1.push_back(std::make_pair(i.second, i.first));
			Graph cur = GraphExtractor::get_dijkstra_graph(
				dih, GRAPH_ROOT, lmao, matter, edges1, edges2
			);
			anim -> add_state(VisualizerState(cur, current_sudo), 0);
		}

		matter = dih->get_shortest_path(u, v);

		std::vector<int> shortest_path;
		for (int i = 0; i < (int)matter.size(); ++i) {
			shortest_path.push_back(matter[i]);
			if (i > 0)
				edges2.push_back(std::make_pair(matter[i - 1], matter[i]));
			Graph cur = GraphExtractor::get_dijkstra_graph(
				dih, GRAPH_ROOT, lmao, shortest_path, edges1, edges2
			);
			anim->add_state(VisualizerState(cur, current_sudo), 0);
		}
	}
}
void AnimationController::handle_insertion(std::string s) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);

	anim->force_latest();
	void* current_ds = ds -> get_current_structure();
	switch (ds -> get_current_type()) {
	case AVL_TREE:
	{
		std::vector<void*> searched_nodes = ds -> search_before_insert(s);
		for (auto i : searched_nodes)
			anim -> add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), current_sudo)
				, 0);
		if (searched_nodes.size() && searched_nodes.back() != nullptr)
			anim ->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched_nodes.back(), 2), current_sudo)
				, 0);

		ds -> insert(s); update_graph(0);
		if (ds -> balance_structure()) update_graph(0);
		break;
	}
	case TRIE:
	{
		std::vector<void*> searched_nodes = ds -> search(s);
		for (auto i : searched_nodes)
			anim -> add_state(VisualizerState(GraphExtractor::get_graph(*ds, i), current_sudo), 0);
		while (true) {
			int val = ds -> insert(s);
			std::vector<void*> searched_nodes = ds -> search(s);
			if (searched_nodes.back() == nullptr) searched_nodes.pop_back();
			anim ->add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched_nodes.back(), 3 - val), current_sudo), 
				0);
			if (val == 1) break;
		}
		break;
	}
	default:
	{
		ds -> insert(s); update_graph(0);
		break;
	}
	}
}
void AnimationController::handle_deletion(std::string s) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);

	anim->force_latest();
	void* current_ds = ds -> get_current_structure();
	switch (ds -> get_current_type()) {
	case LINKED_LIST:
	case HASHMAP_CHAIN:
	{
		std::vector<void*> searched = ds -> search(s);
		execute_graph_search(searched);
		int val = ds -> erase(s);
		update_graph(0);
		break;
	}
	case TRIE:
	{
		std::vector<void*> searched = ds -> search(s);
		execute_graph_search(searched);
		if (searched.back()) {
			while (true) {
				std::vector<void*> searched = ds -> search(s);
				while (searched.size() && searched.back() == nullptr) searched.pop_back();
				anim -> add_state(VisualizerState(GraphExtractor::get_graph(*ds, searched.back(), 2), current_sudo)
					, 0);

				int val = ds -> erase(s);
				update_graph(0);
				if (val == 0) return;
			}
		}

		break;
	}
	case AVL_TREE:
	{
		std::vector<void*> searched = ds -> search(s);
		execute_graph_search(searched);
		if (ds -> erase(s)) update_graph(0);
		if (ds -> balance_structure()) update_graph(0);
		break;
	}
	case KRUSKAL:
	case DIJKSTRA:
	{
		if (ds -> erase(s)) update_graph(0);
		break;
	}
	}
}

void AnimationController::handle_update(std::string x, std::string y) {
	Pseudocode current_sudo = Pseudocode((int)ds->get_current_type() + 1, 1);

	void* current_ds = ds->get_current_structure();
	switch (ds->get_current_type()) {
	case LINKED_LIST:
	{
		std::vector<void*> searched = ds->search(x);
		execute_graph_search(searched);

		if (ds->update(x, y)) 
			anim->add_state(VisualizerState(
				GraphExtractor::get_graph(*ds, searched.back(), 2), current_sudo)
				, 0);


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
	anim->force_latest();
	ds->clear();
	update_graph(0);
}

void AnimationController::handle_init(std::string s) {
	anim->force_latest();
	ds->clear();
	update_graph(0);

	ds->init(s);
	update_graph(0);
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