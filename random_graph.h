#include <ctime>
#include "graph.h"

double random_double(double dMin, double dMax) {
	double d = (double)rand() / RAND_MAX;
	return dMin + d * (dMax - dMin);
}

Graph random() {
	srand(time(0));
	int n = rand() % 100 + 1;
	vector<Vertex> v(n);
	for (int i = 0; i < n; ++i) {
		v[i].x = random_double(-1e6, 1e6);
		v[i].y = random_double(-1e6, 1e6);
		v[i].ind = i;
	}
	return Graph(v, true);
}