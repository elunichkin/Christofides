#pragma once

#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Vertex {
	double x, y;
	size_t ind;
	double eps = 1e-6;

	static double dist(Vertex u, Vertex v) {
		return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
	}

	static Vertex nearest(Vertex v, const vector<Vertex> & vs) {
		int n = vs.size();
		Vertex nearest = vs[0];
		double dist = DBL_MAX;
		for (int i = 0; i < n; ++i) {
			Vertex cur = vs[i];
			if (v == cur)
				continue;
			double cur_dist = Vertex::dist(v, cur);
			if (cur_dist < dist) {
				nearest = cur;
				dist = cur_dist;
			}
		}
		return nearest;
	}

	static bool adm(Vertex v, Vertex u, Vertex vv, Vertex uu, double eps) {
		double dist = Vertex::dist(u, v);
		return dist <= eps * min(Vertex::dist(u, uu), Vertex::dist(v, vv));
	}

	Vertex() {}

	Vertex(double x, double y, size_t ind)
		: x(x), y(y), ind(ind)
	{}

	bool operator==(const Vertex & other) {
		return (abs(x - other.x) < eps) && (abs(y - other.y) < eps);
	}
};

struct Edge {
	Vertex u, v;
	double cost;

	Edge() {}

	Edge(Vertex u, Vertex v)
		: u(u), v(v)
	{
		cost = Vertex::dist(u, v);
	}

	bool operator<(const Edge & other) {
		return cost < other.cost;
	}

	bool operator==(const Edge & other) {
		return (u == other.u && v == other.v);
	}
};

class Graph {
	vector<Vertex> v;
	vector<Edge> e;
	unordered_map<size_t, vector<Vertex>> adj;
	size_t n, m;

public:
	Graph()
		: v(0), e(0), n(0), m(0)
	{}

	Graph(vector<Vertex> vert, bool ind = false)
		: v(vert)
	{
		n = vert.size();
		if (ind)
			induce();
	}

	size_t get_V() const {
		return n;
	}

	size_t get_E() const {
		return m;
	}

	void sort_e() {
		sort(e.begin(), e.end());
	}

	Vertex get_vertex(size_t ind) const {
		return v[ind];
	}

	Edge get_edge(size_t ind) const {
		return e[ind];
	}

	vector<Vertex> get_vertexes() const {
		return v;
	}

	vector<Edge> get_edges() const {
		return e;
	}

	void add_Edge(Edge edg) {
		e.push_back(edg);
		Vertex u = edg.u,
			v = edg.v;
		adj[u.ind].push_back(v);
		adj[v.ind].push_back(u);
	}

	void add_Vertex(Vertex vert) {
		v.push_back(vert);
		++n;
	}

	int get_adj_size(Vertex v) {
		return adj[v.ind].size();
	}

	void induce() {
		size_t m = n * (n - 1) / 2;
		e.reserve(n);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = i + 1; j < n; ++j) {
				adj[v[i].ind].push_back(v[j]);
				adj[v[j].ind].push_back(v[i]);
				e.emplace_back(v[i], v[j]);
			}
	}

	void combine_edges(const Graph & other) {
		vector<Edge> other_edges = other.get_edges();
		int sz = other_edges.size();
		for (size_t i = 0; i < sz; ++i) {
			if (find(e.begin(), e.end(), other_edges[i]) == e.end())
				add_Edge(other_edges[i]);
		}
	}
};