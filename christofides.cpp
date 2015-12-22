#include "dsu.h"
#include "graph.h"
#include "random_graph.h"

Graph MST(Graph G) {
	G.sort_e();
	size_t n = G.get_V(),
		m = G.get_E();
	DSU dsu(n);
	Graph MST(G.get_vertexes());
	for (size_t i = 0; i < m; ++i) {
		Edge cur = G.get_edge(i);
		size_t u = cur.u.ind,
			v = cur.v.ind;
		if (dsu.get(u) != dsu.get(v)) {
			dsu.unite(u, v);
			MST.add_Edge(cur);
		}
	}
	return MST;
}

Graph odd(Graph G) {
	size_t n = G.get_V();
	Graph O;
	for (size_t i = 0; i < n; ++i) {
		Vertex v = G.get_vertex(i);
		size_t deg = G.get_adj_size(v);
		if (deg % 2)
			O.add_Vertex(v);
	}
	O.induce();
	return O;
}

Graph findPM(Graph G) {
	Graph PM;
	vector<Vertex> V = G.get_vertexes();
	vector<Vertex> W(V);
	size_t n = G.get_V();
	size_t k = 50 + sqrt(n);
	double eps = (1 + 1.0 / k) * (1 + 1.0 / k);
	for (size_t i = 0; i < k && W.size(); ++i) {
		Vertex v = W.at(rand() % W.size());
		Vertex u = Vertex::nearest(v, W);
		Vertex vv = Vertex::nearest(v, V);
		Vertex uu = Vertex::nearest(u, V);
		if (Vertex::adm(v, u, vv, uu, eps)) {
			PM.add_Edge(*(new Edge(u, v)));
			W.erase(find(W.begin(), W.end(), u));
			W.erase(find(W.begin(), W.end(), v));
		}
	}
	while (W.size()) {
		Vertex v = W.at(rand() % W.size());
		Vertex u = Vertex::nearest(v, W);
		PM.add_Edge(*(new Edge(u, v)));
		W.erase(find(W.begin(), W.end(), u));
		W.erase(find(W.begin(), W.end(), v));
	}
	return PM;
}

void main() {
	randomize();
}