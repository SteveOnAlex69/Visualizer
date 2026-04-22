#include <DataStructures/Dijkstra.hpp>
#include <queue>
#include <iostream>

Dijkstra::Dijkstra() {
}

void Dijkstra::add_edge(int u, int v, int w) {
	edges.push_back(DijkstraEdge(u, v, w));
}
bool Dijkstra::del_edge(int u, int v, int w) {
	for (int i = 0; i < (int)edges.size(); ++i) {
		if (edges[i].u == u && edges[i].v == v && edges[i].w == w) {
			edges.erase(edges.begin() + i);
			return true;
		}
	}
	return false;
}
std::vector<int> Dijkstra::get_vertices() {
	std::vector<int> vertices;
	for (auto i : edges) {
		vertices.push_back(i.u);
		vertices.push_back(i.v);
	}
	std::sort(vertices.begin(), vertices.end());
	vertices.resize(std::unique(vertices.begin(), vertices.end()) - vertices.begin());
	return vertices;
}
std::vector<DijkstraEdge> Dijkstra::get_edges() {
	return edges;
}

struct P {
	int i;
	long long w;
	P(int i, long long w): i(i), w(w) {}
};

struct compare {
	bool operator () (P a, P b) { return a.w > b.w; }
};

// perform flood fill
std::vector<GraphState> Dijkstra::run_dijkstra(int u, int v) {
	std::vector<int> vertices = get_vertices();
	vertices.push_back(1e9);
	std::vector<GraphState> ans;
	int n = vertices.size();
	std::vector<std::vector<P>> graph(n);

	u = std::lower_bound(vertices.begin(), vertices.end(), u) - vertices.begin();
	v = std::lower_bound(vertices.begin(), vertices.end(), v) - vertices.begin();
	for (auto i : edges) {
		i.u = std::lower_bound(vertices.begin(), vertices.end(), i.u) - vertices.begin();
		i.v = std::lower_bound(vertices.begin(), vertices.end(), i.v) - vertices.begin();
		graph[i.u].push_back(P(i.v, i.w));
	}

	std::vector<long long> dis(n, 1e18);
	dis[u] = 0;
	std::priority_queue < P, std::vector<P>, compare> pq;
	pq.push(P(u, 0));

	std::vector<bool> visited(n);
	std::vector<int> parent(n, vertices.size() - 1);

	int cnt = 0;
	while (pq.size()) {
		P u = pq.top(); pq.pop();
		if (!visited[u.i]) {
			GraphState gs;
			gs.type = 1;
			if (cnt == 0) {
				cnt++;
				gs.vertices.push_back(vertices[u.i]);
			}
			gs.vertices.push_back(vertices[u.i]);
			gs.edges.push_back(std::make_pair(vertices[parent[u.i]], vertices[u.i]));
			ans.push_back(gs);
		}
		else continue;
		visited[u.i] = true;
		if (u.i == v) break;

		GraphState gs;
		gs.type = 2;
		for (P v : graph[u.i]) {
			gs.edges.push_back(std::make_pair(vertices[u.i], vertices[v.i]));
			if (dis[v.i] == 1e18) gs.vertices.push_back(vertices[v.i]);
			if (dis[v.i] > dis[u.i] + v.w) {
				dis[v.i] = dis[u.i] + v.w;
				parent[v.i] = u.i;
				pq.push(P(v.i, dis[v.i]));
			}
		}
		ans.push_back(gs);
	}
	return ans;
}


// trace the correct path.
std::vector<int> Dijkstra::get_shortest_path(int u, int v) {
	std::vector<int> vertices = get_vertices();
	int n = vertices.size();
	std::vector<std::vector<P>> graph(n);

	u = std::lower_bound(vertices.begin(), vertices.end(), u) - vertices.begin();
	v = std::lower_bound(vertices.begin(), vertices.end(), v) - vertices.begin();
	for (auto i : edges) {
		i.u = std::lower_bound(vertices.begin(), vertices.end(), i.u) - vertices.begin();
		i.v = std::lower_bound(vertices.begin(), vertices.end(), i.v) - vertices.begin();
		graph[i.u].push_back(P(i.v, i.w));
	}

	std::vector<long long> dis(n, 1e18);
	dis[u] = 0;
	std::priority_queue < P, std::vector<P>, compare> pq;
	pq.push(P(u, 0));

	std::vector<bool> visited(n);
	std::vector<int> parent(n, -1);
	while (pq.size()) {
		P u = pq.top(); pq.pop();
		if (!visited[u.i]);
		else continue;
		visited[u.i] = true;
		if (u.i == v) break;
		for (P v : graph[u.i]) {
			if (dis[v.i] > dis[u.i] + v.w) {
				dis[v.i] = dis[u.i] + v.w;
				parent[v.i] = u.i;
				pq.push(P(v.i, dis[v.i]));
			}
		}
	}
	std::vector<int> ans;
	if (visited[v]) {
		while (v != u) {
			ans.push_back(vertices[v]);
			v = parent[v];
		}
		ans.push_back(vertices[u]);
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
	return ans;
}

void Dijkstra::clear() {
	edges.clear();
}