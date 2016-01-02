#pragma once

#include <iostream>
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
	Vertex start, finish;
	vector<Vertex> v;
	vector<Edge> e;
	unordered_map<size_t, vector<size_t>> adj;
	size_t n, m;
	
	vector<size_t> path;

public:
	Graph()
		: v(0), e(0), n(0), m(0)
	{}

	Graph(const Graph & other, bool only_v)
	{
		v = other.get_vertexes();
		n = v.size();
		start = other.get_start();
		finish = other.get_finish();
	}

	Graph(vector<Vertex> vert, Vertex start, Vertex finish)
		: v(vert), n(vert.size()), start(start), finish(finish)
	{
		induce();
	}

	size_t get_V() const {
		return n;
	}

	size_t get_E() const {
		return m;
	}

	Vertex get_start() const {
		return start;
	}

	Vertex get_finish() const {
		return finish;
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
		adj[u.ind].push_back(v.ind);
		adj[v.ind].push_back(u.ind);
	}

	void add_Edge(Vertex u, Vertex v) {
		e.emplace_back(u, v);
		adj[u.ind].push_back(v.ind);
		adj[v.ind].push_back(u.ind);
	}

	void add_Vertex(Vertex vert) {
		v.push_back(vert);
		++n;
	}

	int get_adj_size(Vertex v) {
		return adj[v.ind].size();
	}

	unordered_map<size_t, vector<size_t>> get_adjacent_list() const {
		return adj;
	}

	Vertex get_vertex_by_ind(size_t ind) const {
		for (size_t i = 0; i < n; ++i)
			if (v[i].ind == ind)
				return v[i];
	}

	void set_path(vector<size_t> p) {
		path = p;
	}

	vector<size_t> get_path() const {
		return path;
	}

	void induce() {
		m = n * (n - 1) / 2;
		e.reserve(n);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = i + 1; j < n; ++j) {
				adj[v[i].ind].push_back(v[j].ind);
				adj[v[j].ind].push_back(v[i].ind);
				e.emplace_back(v[i], v[j]);
			}
	}

	void combine_edges(const Graph & other) {
		vector<Edge> other_edges = other.get_edges();
		size_t sz = other_edges.size();
		for (size_t i = 0; i < sz; ++i) {
			if (find(e.begin(), e.end(), other_edges[i]) == e.end())
				add_Edge(other_edges[i]);
		}
	}

	void print_graph() const {
		cout << "Vertexes:" << endl;
		for (int i = 0; i < n; ++i)
			cout << v[i].ind + 1 << " " << v[i].x << " " << v[i].y << endl;
		cout << endl << "Start:" << endl << start.ind + 1 << endl << "Finish:" << endl << finish.ind + 1<< endl << endl;
	}

	void print_path() const {
		for (int i = 0; i < path.size(); ++i) {
			Vertex cur = get_vertex_by_ind(path[i]);
			cout << cur.ind + 1 << " " << cur.x << " " << cur.y << endl;
		}
	}
};