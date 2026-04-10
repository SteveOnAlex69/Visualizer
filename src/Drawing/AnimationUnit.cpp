#include <Drawing/AnimationUnit.hpp>


AnimationUnit::AnimationUnit() {
	animation_time = 0;
}


void AnimationUnit::add_graph(Graph graph, bool force_update) {
	if (force_update) {
		if (is_empty()) animation_time = 0;
		else animation_time = (history.size() - 1) * ANIMATION_TIME;
	}
	history.push_back(graph);
}
void AnimationUnit::update_timer(float delta) {
	if (is_empty()) animation_time = 0;
	animation_time += delta;
	if (animation_time >= (history.size()-1) * ANIMATION_TIME)
		animation_time = (history.size()-1) * ANIMATION_TIME;
}

void AnimationUnit::clear_graph() {
	history.clear();
	animation_time = 0;
}
bool AnimationUnit::is_empty() {
	return history.empty();
}

float sigmoid(float epoch) {
	epoch -= ANIMATION_TIME * 0.5F;
	epoch *= 10 / ANIMATION_TIME;
	return (float)1 / (1 + std::exp(-epoch));
}

Graph AnimationUnit::get_graph_stage1(Graph& graph1, Graph& graph2, float epoch) {
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
		if (found == false) i.set_opacity(1 - sigmoid(epoch));
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
	return graph;

}
Graph AnimationUnit::get_graph_stage2(Graph& graph1, Graph& graph2, float epoch) {
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
	return graph;
}
Graph AnimationUnit::get_graph_stage3(Graph& graph1, Graph& graph2, float epoch) {
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
	return graph;
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

Graph AnimationUnit::get_graph() {
	if (history.size() == 0) assert(false);

	int idx = animation_time / ANIMATION_TIME;
	if (idx + 1 == history.size()) return history.back();

	Graph graph1 = history[idx], graph2 = history[idx + 1];
	float tmp = animation_time - idx * ANIMATION_TIME;
	int mask = get_diff_state(graph1, graph2);
	if (pop_cnt(mask) == 0) return graph2;

	const float STEP = ANIMATION_TIME / pop_cnt(mask);
	for (int i = 0; i < 3; ++i) if (GETBIT(mask, i)) {
		if (tmp <= STEP) {
			float t = tmp * pop_cnt(mask);
			if (i == 0) return get_graph_stage1(graph1, graph2, t);
			if (i == 1) return get_graph_stage2(graph1, graph2, t);
			if (i == 2) return get_graph_stage3(graph1, graph2, t);
		}
		tmp -= STEP;
	}
	
	Graph empty_graph;
	return empty_graph;
}

bool AnimationUnit::done_animating() {
	if (is_empty()) return true;
	return (animation_time >= (history.size() - 1) * ANIMATION_TIME);
}