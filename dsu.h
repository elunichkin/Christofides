#pragma once

#include <vector>
using namespace std;

class DSU {
	vector<int> parent;
	vector<int> size;

public:
	DSU(size_t n)
		: parent(n), size(n)
	{
		for (size_t i = 0; i < n; ++i) {
			parent[i] = i;
			size[i] = i;
		}
	}

	size_t get(size_t v) {
		return (v == parent[v]) ? v : (parent[v] = get(parent[v]));
	}

	void unite(size_t u, size_t v) {
		u = get(u);
		v = get(v);
		if (u != v) {
			if (size[u] < size[v])
				swap(u, v);
			parent[v] = u;
			size[u] += size[v];
		}
	}
};