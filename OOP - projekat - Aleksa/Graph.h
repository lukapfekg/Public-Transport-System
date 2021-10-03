#pragma once
#include "Stajaliste.h"
#include "Linija.h"
#include "Strategija.h"
#include "Izuzeci.h"
#include <vector>
#include <iostream>
using namespace std;

class Graph {
	int V;
	int numPaths;
	int examineParameter;///////
	bool hasFirst;////////
	vector<Stajaliste*>* vS;
	vector<pair<int, Linija*>>* adj;
	vector<vector<pair<Stajaliste*, Linija*>>> izlaz;

	Strategija* strategija;

	void printAllPathsUtil(int, int, bool[], pair<int, Linija*>[], int&);
	void printAllPaths(int s, int d);

public:
	Graph(int V, vector<Stajaliste*>* vs);
	void addEdges();
	void printPaths();
	inline void setStrategija(Strategija* stra) { strategija = stra; }
	std::string execute(int a, int b);
};
