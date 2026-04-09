#include <DataStructures/Dijkstra.hpp>
#include <queue>

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


std::vector<std::pair<int, long long>> Dijkstra::run_dijkstra(int u, int v) {
	std::vector<int> vertices = get_vertices();
	std::vector<std::pair<int, long long>> ans;
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
	while (pq.size()) {
		P u = pq.top(); pq.pop();
		if (!visited[u.i])
			ans.push_back(std::make_pair(u.i, u.w));
		else continue;
		visited[u.i] = true;
		if (u.i == v) break;
		for (P v : graph[u.i]) {
			if (dis[v.i] > dis[u.i] + v.w) {
				dis[v.i] = dis[u.i] + v.w;
				pq.push(P(v.i, dis[v.i]));
			}
		}
	}
	return ans;
}
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
	std::vector<int> parent(n);
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
			ans.push_back(v);
			v = parent[v];
		}
		ans.push_back(u);
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
	return ans;
}

void Dijkstra::clear() {
	edges.clear();
}