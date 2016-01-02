#pragma once

#include <ctime>
#include "graph.h"

void randomize() {
	srand(time(0));
}

double random_double(double dMin, double dMax) {
	double d = (double)rand() / RAND_MAX;
	return dMin + d * (dMax - dMin);
}

Graph random() {
	int n = rand() % 1000 + 1;
	vector<Vertex> v(n);
	for (int i = 0; i < n; ++i) {
		v[i].x = random_double(-1e6, 1e6);
		v[i].y = random_double(-1e6, 1e6);
		v[i].ind = i;
	}
	Vertex start = v.at(rand() % n),
		finish = v.at(rand() % n);
	return Graph(v, start, finish);
}