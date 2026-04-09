#include <DataStructures/Kruskal.hpp>
#include <iostream>


Kruskal::Kruskal(){


}

void Kruskal::add_edge(int u, int v, int w) {
	std::cout << u << " " << v << " " << w << std::endl;
	edges.push_back(KruskalEdge(u, v, w));
}
bool Kruskal::del_edge(int u, int v, int w) {
	for (int i = 0; i < (int)edges.size(); ++i) {
		if (edges[i].u == u && edges[i].v == v && edges[i].w == w) {
			edges.erase(edges.begin() + i);
			return true;
		}
	}
	return false;
}

std::vector<int> Kruskal::get_vertices() {
	std::vector<int> vertices;
	for (auto i : edges) {
		vertices.push_back(i.u);
		vertices.push_back(i.v);
	}
	std::sort(vertices.begin(), vertices.end());
	vertices.resize(std::unique(vertices.begin(), vertices.end()) - vertices.begin());
	return vertices;
}

std::vector<KruskalEdge> Kruskal::get_edges() {
	return edges;
}


std::vector<KruskalEdge> Kruskal::run_kruskal() {
	std::vector<int> vertices = get_vertices();
	std::sort(edges.begin(), edges.end(), [](KruskalEdge x, KruskalEdge y) {
		return x.w < y.w;
	});
	
	DSU mst(vertices.size());
	std::vector<KruskalEdge> ans;
	for (KruskalEdge i : edges) {
		int u = std::lower_bound(vertices.begin(), vertices.end(), i.u) - vertices.begin();
		int v = std::lower_bound(vertices.begin(), vertices.end(), i.v) - vertices.begin();
		KruskalEdge cur = i;
		cur.flag = mst.join_set(u, v);
		ans.push_back(cur);
	}
	return ans;
}

void Kruskal::clear() {
	edges.clear();
}