#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <utility>

struct KruskalEdge {
	int u, v, w;
	bool flag;
	KruskalEdge(int u = -1, int v = -1, int w = -1) : u(u), v(v), w(w) { flag = 0; }
};

struct DSU {
	int n;
	std::vector<int> parent, sz;

	DSU(int _n) {
		n = _n;
		parent.resize(n); sz.resize(n, 1);
		for (int i = 0; i < n; ++i) parent[i] = i;
	}

	int find_set(int u) { return (u == parent[u]) ? u : (parent[u] = find_set(parent[u])); }
	bool same_set(int u, int v) { return find_set(u) == find_set(v); }
	bool join_set(int u, int v) {
		u = find_set(u), v = find_set(v);
		if (u != v) {
			if (sz[u] < sz[v]) std::swap(u, v);
			parent[v] = u;
			sz[u] += sz[v];
			return true;
		}
		return false;
	}

	int get_size(int u) { return sz[find_set(u)]; }
};

class Kruskal {
public:
	Kruskal();
	
	void add_edge(int u, int v, int w);
	bool del_edge(int u, int v, int w);
	std::vector<int> get_vertices();
	std::vector<KruskalEdge> get_edges();
	std::vector<KruskalEdge> run_kruskal(); 
	// return all edges in order, and whether they get selected for the MST or not

	void clear();
private: 
	std::vector<KruskalEdge> edges;
};
#endif