#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

struct DijkstraEdge {
	int u, v, w;
	DijkstraEdge(int u = -1, int v = -1, int w = -1) : u(u), v(v), w(w) {}
};


class Dijkstra {
public:
	Dijkstra();

	void add_edge(int u, int v, int w);
	bool del_edge(int u, int v, int w);
	std::vector<int> get_vertices();
	std::vector<DijkstraEdge> get_edges();
	std::vector<std::pair<int, int>> run_dijkstra(int u, int v);
	// get all the vertices in order of visited when finding the shortest path from u to v
	std::vector<int> get_shortest_path(int u, int v);
	// get the shortest path from u to v

	void clear();
private:
	std::vector<DijkstraEdge> edges;
};
#endif