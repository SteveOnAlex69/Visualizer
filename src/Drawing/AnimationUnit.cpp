#include <Drawing/AnimationUnit.hpp>


AnimationUnit::AnimationUnit() {
	animation_time = 0;
}

void AnimationUnit::force_latest() {
	if (is_empty()) animation_time = 0;
	else animation_time = (history.size() - 1) * ANIMATION_TIME;
}

void AnimationUnit::add_state(VisualizerState state) {
	history.push_back(state);
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
			graph.add_edge(e.first, e.second, e.val, 1, e.color);
		else graph.add_edge(e.first, e.second, e.val, 1 - sigmoid(epoch), e.color);
	}
	return graph;

}
Graph AnimationUnit::get_graph_stage2(Graph& graph1, Graph& graph2, float epoch) {
	Graph graph;
	std::vector<Node> li1 = graph1.get_node_list();
	std::vector<Node> li2 = graph2.get_node_list();
	std::vector<Edge> e1 = graph1.get_edges_idx();
	std::vector<Edge> e2 = graph2.get_edges_idx();

	float scaling = sigmoid(epoch);

	for (Node i : li1) {
		sf::Vector2f pos_start = i.get_pos(), pos_end = i.get_pos();
		sf::Color color_start = i.get_color(), color_end = i.get_color();
		bool found = false;
		for (Node j : li2)
			if (i.get_hash_val() == j.get_hash_val()) {
				pos_end = j.get_pos();
				color_end = j.get_color();
				found = true;
			}
		if (found) {
			sf::Vector2f pos = pos_start + (pos_end - pos_start) * scaling;
			float r = color_end.r - color_start.r, g = color_end.g - color_start.g,
				b = color_end.b - color_start.b;
			r *= scaling; g *= scaling; b *= scaling;
			i.set_pos(pos);
			i.set_color(sf::Color(color_start.r + r, color_start.g + g, color_start.b + b));

			graph.add_node(i);
		}
	}
	for (Edge e : e1) {
		bool found = false;
		sf::Color start_c = e.color, end_c = e.color;
		for (Edge g : e2) {
			if (e.first == g.first && e.second == g.second && e.val == g.val) {
				found = true;
				end_c = g.color;
			}
		}

		float r = end_c.r - start_c.r, g = end_c.g - start_c.g, b = end_c.b - start_c.b;
		start_c.r += r * scaling;
		start_c.g += g * scaling;
		start_c.b += b * scaling;
		if (found)
			graph.add_edge(e.first, e.second, e.val, 1, start_c);
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
			graph.add_edge(e.first, e.second, e.val, 1, e.color);
		else graph.add_edge(e.first, e.second, e.val, sigmoid(epoch), e.color);
	}
	return graph;
}



VisualizerState AnimationUnit::get_viz_stage1(VisualizerState& viz1, VisualizerState& viz2, float epoch) {
	Pseudocode sudo_code = viz2.get_pseudo_code();
	sudo_code.get_stage(1);
	return VisualizerState(get_graph_stage1(viz1.get_graph(), viz2.get_graph(), epoch), 
		sudo_code);
}
VisualizerState AnimationUnit::get_viz_stage2(VisualizerState& viz1, VisualizerState& viz2, float epoch) {
	Pseudocode sudo_code = viz2.get_pseudo_code();
	sudo_code.get_stage(2);
	return VisualizerState(get_graph_stage2(viz1.get_graph(), viz2.get_graph(), epoch),
		sudo_code);
}
VisualizerState AnimationUnit::get_viz_stage3(VisualizerState& viz1, VisualizerState& viz2, float epoch) {
	Pseudocode sudo_code = viz2.get_pseudo_code();
	sudo_code.get_stage(3);
	return VisualizerState(get_graph_stage3(viz1.get_graph(), viz2.get_graph(), epoch),
		sudo_code);
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
				if (i.is_special() != j.is_special()) mask |= 2;
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
			if (i.first == j.first && i.second == j.second && i.val == j.val) {
				found = true;
				if (i.color != j.color) mask |= 2;
			}
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

VisualizerState AnimationUnit::get_state() {
	if (history.size() == 0) assert(false);

	int idx = animation_time / ANIMATION_TIME;
	if (idx + 1 == history.size()) return get_viz_stage3(history.back(), history.back(), ANIMATION_TIME);

	VisualizerState state1 = history[idx], state2 = history[idx + 1];
	float tmp = animation_time - idx * ANIMATION_TIME;

	Graph graph1 = state1.get_graph(), graph2 = state2.get_graph();
	int mask = get_diff_state(graph1, graph2);
	if (pop_cnt(mask) == 0) return get_viz_stage3(state2, state2, ANIMATION_TIME);

	float PAUSE = ANIMATION_TIME * 0.0;
	float ACTUAL_TIME = ANIMATION_TIME - PAUSE * (pop_cnt(mask) - 1);
	const float STEP = ACTUAL_TIME / pop_cnt(mask);
	for (int i = 0; i < 3; ++i) if (GETBIT(mask, i)) {
		if (tmp <= STEP + PAUSE) {
			float t = std::min(ANIMATION_TIME, tmp / STEP);
			if (i == 0) return get_viz_stage1(state1, state2, t);
			if (i == 1) return get_viz_stage2(state1, state2, t);
			if (i == 2) return get_viz_stage3(state1, state2, t);
		}
		tmp -= STEP + PAUSE;
	}
	
	debug_error("Animation went wrong. Function: get_state()");
}

bool AnimationUnit::done_animating() {
	if (is_empty()) return true;
	return (animation_time >= (history.size() - 1) * ANIMATION_TIME);
}

void AnimationUnit::jump_to_back() {
	animation_time = 0;
}
void AnimationUnit::jump_to_front() {
	force_latest();
}
void AnimationUnit::jump_back() {
	int current_frame = (animation_time / ANIMATION_TIME) - 1;
	if (current_frame < 0) current_frame = 0;
	animation_time = current_frame * ANIMATION_TIME;
}
void AnimationUnit::jump_front() {
	int current_frame = (animation_time / ANIMATION_TIME) + 1;
	if (current_frame >= history.size()) jump_to_front();
	else animation_time = current_frame * ANIMATION_TIME;
}