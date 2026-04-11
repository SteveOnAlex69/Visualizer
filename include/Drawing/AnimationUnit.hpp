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
#include <Drawing/DrawingUnit.hpp>
#include <Helper.hpp>

class AnimationUnit{
public:
	AnimationUnit();
	
	void add_graph(Graph graph, bool force_update = 1);
	void update_timer(float delta);

	void clear_graph();
	bool is_empty();
	bool done_animating();

	void force_latest();

	Graph get_graph();
private:
	std::vector<Graph> history;
	float animation_time;

	Graph get_graph_stage1(Graph& graph1, Graph& graph2, float epoch);
	Graph get_graph_stage2(Graph& graph1, Graph& graph2, float epoch);
	Graph get_graph_stage3(Graph& graph1, Graph& graph2, float epoch);
};

#endif