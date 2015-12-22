#include <stack>
#include "dsu.h"
#include "graph.h"
#include "random_graph.h"

Graph MST(Graph G) {
	G.sort_e();
	size_t n = G.get_V(),
		m = G.get_E();
	DSU dsu(n);
	Graph MST(G);
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
			PM.add_Edge(u, v);
			W.erase(find(W.begin(), W.end(), u));
			W.erase(find(W.begin(), W.end(), v));
		}
	}
	while (W.size()) {
		Vertex v = W.at(rand() % W.size());
		Vertex u = Vertex::nearest(v, W);
		PM.add_Edge(u, v);
		W.erase(find(W.begin(), W.end(), u));
		W.erase(find(W.begin(), W.end(), v));
	}
	return PM;
}

Graph EP(Graph G) {
	Graph EP(G);
	unordered_map<size_t, vector<size_t>> adj = G.get_adjacent_list();
	vector<size_t> ep;
	stack<size_t> st;
	size_t u = adj.begin()->first;
	while (!st.empty()) {
		size_t v = st.top();
		if (!adj[v].size()) {
			ep.push_back(v);
			st.pop();
		}
		else {
			size_t w = adj[v].back();
			adj[v].pop_back();
			st.push(w);
		}
	}
	EP.set_path(ep);
	for (size_t i = 0; i < ep.size() - 1; ++i) {
		Vertex u = G.get_vertex_by_ind(ep[i]),
			v = G.get_vertex_by_ind(ep[i + 1]);
		EP.add_Edge(u, v);
	}
	return EP;
}

Graph HP(Graph EP) {
	Graph HP(EP);
	vector<size_t> ep = EP.get_path();
	size_t n = ep.size();
	vector<bool> used(n, false);
	reverse(ep.begin(), ep.end());
	vector<size_t> hp;
	for (size_t i = 0; i < n; ++i) {
		if (!used[ep[i]] && ep[i] != HP.get_finish().ind)
			hp.push_back(ep[i]);
		used[ep[i]] = true;
	}
	hp.push_back(HP.get_finish().ind);
	HP.set_path(hp);
	for (size_t i = 0; i < hp.size() - 1; ++i) {
		Vertex u = HP.get_vertex_by_ind(hp[i]),
			v = HP.get_vertex_by_ind(hp[i + 1]);
		HP.add_Edge(u, v);
	}
	return HP;
}

void main() {
	randomize();
	Graph G = random();
	Graph mst = MST(G);
	Graph M = findPM(odd(mst));
	Graph H = mst;
	H.combine_edges(M);
	Graph euler = EP(H);
	Graph hamiltonian = HP(euler);
	hamiltonian.print_path();
}