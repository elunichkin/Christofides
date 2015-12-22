#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Vertex {
	double x, y;
	size_t ind;

	Vertex() {}
	
	Vertex(double x, double y, size_t ind)
		: x(x), y(y), ind(ind)
	{}
};

struct Edge {
	Vertex u, v;
	double cost;

	Edge() {}

	Edge(Vertex u, Vertex v)
		: u(u), v(v)
	{
		cost = dist(u, v);
	}

	bool operator<(const Edge & other) {
		return cost < other.cost;
	}

private:
	double dist(Vertex u, Vertex v) {
		return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
	}
};

class Graph {
	vector<Vertex> v;
	vector<Edge> e;
	size_t n, m;

public:
	Graph(size_t size)
		: v(size), e(0), n(size), m(0)
	{}

	Graph(vector<Vertex> vert)
		: v(vert)
	{
		n = vert.size();
		m = n * (n - 1) / 2;
		e.reserve(m);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < m; ++j)
				e.emplace_back(v[i], v[j]);
	}

	size_t get_V() {
		return n;
	}

	size_t get_E() {
		return m;
	}

	void sort_e() {
		sort(e.begin(), e.end());
	}

	Vertex get_vertex(size_t ind) {
		return v[ind];
	}

	Edge get_edge(size_t ind) {
		return e[ind];
	}

	void add_Edge(Edge edg) {
		e.push_back(edg);
	}
};