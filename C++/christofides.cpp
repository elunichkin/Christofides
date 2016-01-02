#include <stack>
#include "dsu.h"
#include "graph.h"
#include "random_graph.h"

Graph MST(Graph G) {
	G.sort_e();
	size_t n = G.get_V(),
		m = G.get_E();
	DSU dsu(n);
	Graph MST(G, true);
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
	Graph PM(G, true);
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
	Graph EP(G, true);
	int n = G.get_V();
	unordered_map<size_t, vector<size_t>> adj = G.get_adjacent_list();
	vector<vector<bool>> a(n, vector<bool>(n));
	for (auto i = adj.begin(); i != adj.end(); ++i)
		for (size_t j = 0; j < (i->second).size(); ++j)
			a[i->first][i->second[j]] = a[i->second[j]][i->first] = true;
	vector<size_t> ep;
	stack<size_t> st;
	size_t u = EP.get_start().ind;
	st.push(u);
	while (!st.empty()) {
		size_t v = st.top();
		size_t i;
		for (i = 0; i < n; ++i)
			if (a[v][i])
				break;
		if (i == n) {
			ep.push_back(v);
			st.pop();
		}
		else {
			a[v][i] = false;
			a[i][v] = false;
			st.push(i);
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
	Graph HP(EP, true);
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
	clock_t tstart = clock();
	randomize();
	Graph G = random();
	clock_t trand = clock();
	Graph mst = MST(G);
	clock_t tmst = clock();
	Graph M = findPM(odd(mst));
	Graph H = mst;
	H.combine_edges(M);
	clock_t tpm = clock();
	Graph euler = EP(H);
	clock_t teuler = clock();
	Graph hamiltonian = HP(euler);
	clock_t tham = clock();
	hamiltonian.print_graph();
	hamiltonian.print_path();
	clock_t tprint = clock();
	cout << endl << "Time:" << endl;
	cout << "# of vertexes: " << G.get_V() << endl;
	cout << "Building random graph: " << (double)(trand - tstart) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Finding MST (Kruskal's algorithm): " << (double)(tmst - trand) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Finding perfect matching (randomized algorithm): " << (double)(tpm - tmst) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Finding euler path (non-recursive algorithm): " << (double)(teuler - tpm) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Finding hamiltonian path (shortcut-path algorithm): " << (double)(tham - teuler) / CLOCKS_PER_SEC << " s" << endl;
	cout << "Printing path: " << (double)(tprint - tham) / CLOCKS_PER_SEC << " s" << endl << endl;
	cout << "TOTAL algorithm" << (double)(tham - trand) / CLOCKS_PER_SEC << " s" << endl;
	cout << "TOTAL: " << (double)(tprint - tstart) / CLOCKS_PER_SEC << " s" << endl;
	system("pause");
}