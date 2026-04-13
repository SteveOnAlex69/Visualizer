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
#include <DataStructures/General.hpp>
#include <Helper.hpp>

class AnimationController {
public:
	AnimationController(AnimationUnit* a = nullptr, GeneralData* d = nullptr);
	void update_timer(float delta);

	void update_graph(bool flag = 1);
	void load_kruskal();
	void execute_graph_search(std::vector<void*> searched_nodes);
	void load_dijkstra(std::string x, std::string y);
	void handle_insertion(std::string s);
	void handle_deletion(std::string s);

	void clear_graph();
	Graph get_graph();
	bool is_empty();
private:
	AnimationUnit* anim;
	GeneralData* ds;
};

#endif