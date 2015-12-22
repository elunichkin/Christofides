#include "dsu.h"
#include "graph.h"

Graph MST(Graph G) {
	G.sort_e();
	int n = G.get_V(),
		m = G.get_E();
	DSU dsu(n);
	Graph MST(n);
	for (int i = 0; i < m; ++i) {
		Edge cur = G.get_edge(i);
		int u = cur.u.ind,
			v = cur.v.ind;
		if (dsu.get(u) != dsu.get(v)) {
			dsu.unite(u, v);
			MST.add_Edge(cur);
		}
	}
	return MST;
}

Graph odd(Graph G) {
	int n = G.get_V();
	Graph O;
	for (int i = 0; i < n; ++i) {
		Vertex v = G.get_vertex(i);
		int deg = G.get_adj_size(v);
		if (deg % 2)
			O.add_Vertex(v);
	}
	O.induce();
	return O;
}

void main() {

}