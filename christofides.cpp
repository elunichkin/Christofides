#include "dsu.h"
#include "graph.h"

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
	size_t n = G.get_V(),
		m = G.get_E();
	vector<vector<double>> a(n, vector<double>(n));
	vector<Vertex> vs = G.get_vertexes();
	vector<Vertex> inds(n);
	unordered_map<size_t, size_t> p_inds;
	for (size_t i = 0; i < n; ++i) {
		inds[i] = vs[i];
		p_inds[inds[i].ind] = i;
	}
	for (size_t i = 0; i < m; ++i) {
		Edge e = G.get_edge(i);
		size_t u_i = p_inds[e.u.ind],
			v_i = p_inds[e.v.ind];
		a[u_i][v_i] = a[v_i][u_i] = e.cost;
	}
	vector<double> pu(n + 1), pv(n + 1);
	vector<size_t> pr(n + 1), way(n + 1);
	for (size_t i = 1; i <= n; ++i) {
		pr[0] = i;
		size_t j0 = 0;
		vector<double> minv(n + 1, DBL_MAX);
		vector<bool> used(n + 1, false);
		do {
			size_t i0 = pr[j0], j1;
			double delta = DBL_MAX;
			for (size_t j = 1; j <= n; ++j)
				if (!used[j]) {
					double cur = a[i0][j] - pu[i0] - pv[j];
					if (cur < minv[j])
						minv[j] = cur, way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j], j1 = j;
				}
			for (size_t j = 0; j <= n; ++j)
				if (used[j])
					pu[pr[j]] += delta, pv[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while (pr[j0] != 0);
		do {
			size_t j1 = way[j0];
			pr[j0] = pr[j1];
			j0 = j1;
		} while (j0);
	}
	vector<size_t> ans(n + 1);
	for (size_t j = 1; j <= n; ++j)
		ans[pr[j]] = j;
	Graph PM(G.get_vertexes());
	for (size_t i = 1; i <= n; ++i) {
		Vertex u = inds[i - 1],
			v = inds[ans[i] - 1];
		PM.add_Edge(*(new Edge(u, v)));
	}
	return PM;
}



void main() {

}