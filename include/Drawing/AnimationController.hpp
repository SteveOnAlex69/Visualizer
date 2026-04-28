#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>
#include <Drawing/Node.hpp>
#include <Drawing/Graph.hpp>
#include <Drawing/DrawingUnit.hpp>
#include <Drawing/AnimationUnit.hpp>
#include <Drawing/VisualizerState.hpp>
#include <DataStructures/General.hpp>
#include <Helper.hpp>

class AnimationController {
public:
	AnimationController(AnimationUnit* a = nullptr, GeneralData* d = nullptr);
	void update_timer(float delta);
	void update_graph(int stage = -1);
	void load_kruskal();
	void load_dijkstra(std::string x, std::string y);
	void handle_insertion(std::string s);
	void handle_deletion(std::string s);
	void handle_search(std::string s);
	void handle_update(std::string x, std::string y);

	void clear_current_ds();
	void handle_init(std::string s);

	void clear_graph();
	VisualizerState get_state();
	bool is_empty();

	void jump_to_back();
	void jump_to_front();
	void jump_back();
	void jump_front();
	void toggle_flow();

	int get_flow();

	float get_current_time();
	float get_max_time();
private:
	AnimationUnit* anim;
	GeneralData* ds;
	int flow;
	int current_command;

	void execute_graph_search(std::vector<void*> searched_nodes);
};

#endif