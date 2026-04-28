#ifndef ANIMATIONUNIT_HPP
#define ANIMATIONUNIT_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <Drawing/VisualizerState.hpp>
#include <Helper.hpp>

class AnimationUnit{
public:
	AnimationUnit();
	
	void add_state(VisualizerState graph);
	void update_timer(float delta);

	void clear_graph();
	bool is_empty();
	bool done_animating();

	void force_latest();

	VisualizerState get_state();


	void jump_to_back();
	void jump_to_front();
	void jump_back();
	void jump_front();


	float get_current_time();
	float get_max_time();
private:
	std::vector<VisualizerState> history;
	float animation_time;

	Graph get_graph_stage1(Graph& graph1, Graph& graph2, float epoch);
	Graph get_graph_stage2(Graph& graph1, Graph& graph2, float epoch);
	Graph get_graph_stage3(Graph& graph1, Graph& graph2, float epoch);


	VisualizerState get_viz_stage1(VisualizerState& graph1, VisualizerState& graph2, float epoch);
	VisualizerState get_viz_stage2(VisualizerState& graph1, VisualizerState& graph2, float epoch);
	VisualizerState get_viz_stage3(VisualizerState& graph1, VisualizerState& graph2, float epoch);
};

#endif