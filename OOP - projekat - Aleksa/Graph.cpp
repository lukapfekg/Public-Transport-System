#include "Graph.h"
#include <iostream>

Graph::Graph(int V, vector<Stajaliste*>* vs) : numPaths(0), examineParameter(-1), hasFirst(false) {
	this->V = V;
	this->vS = vs;
	this->strategija = nullptr;
	adj = new vector<pair<int, Linija*>>[V];
	this->addEdges();
}

void Graph::addEdges() {

	for (int i = 0; i < this->vS->size(); i++) {
		for (int j = 0; j < this->vS->at(i)->getLinije()->size(); j++) {
			pair<int, Linija*> p;
			p.first = this->vS->at(i)->getLinije()->at(j)->getIdNextA(vS->at(i)->getSifra());
			p.second = this->vS->at(i)->getLinije()->at(j);
			if (p.first != -1)
				this->adj[i].push_back(p);
			p.first = this->vS->at(i)->getLinije()->at(j)->getIdNextB(vS->at(i)->getSifra());
			if (p.first != -1)
				this->adj[i].push_back(p);
		}
	}

}


void Graph::printAllPaths(int s, int d) {
	this->izlaz.clear();
	this->numPaths = 0;
	this->hasFirst = false;
	this->examineParameter = -1;

	bool* visited = new bool[V];

	pair<int, Linija*>* path = new pair<int, Linija*>[V];

	int path_index = 0;

	for (int i = 0; i < V; i++)
		visited[i] = false;

	printAllPathsUtil(s, d, visited, path, path_index);


	this->hasFirst = false;
	this->examineParameter = -1;

	if (this->izlaz.size() == 0) throw GUniversal("Ne postoji putanja izmedju date dve stanice!!!");
}

void Graph::printPaths() {
	for (int i = 0; i < this->izlaz.size(); i++) {
		for (int j = 0; j < this->izlaz.at(i).size(); j++) {
			cout << (this->izlaz.at(i).at(j).second != nullptr ? ("-" + this->izlaz.at(i).at(j).second->getNaziv() + "-") : "") << this->izlaz.at(i).at(j).first->getSifra();
		}
		cout << endl;

	}
}

std::string Graph::execute(int a, int b) {
	this->printAllPaths(a, b);

	return this->strategija->execute(&izlaz);
}


void Graph::printAllPathsUtil(int u, int d, bool visited[],
	pair<int, Linija*>path[], int& path_index) {

	visited[u] = true;
	path[path_index].first = u;
	path_index++;


	if (u == d) {
		vector<pair<Stajaliste*, Linija*>> v;

		this->examineParameter = this->strategija->condition(path, path_index);
		this->hasFirst = true;

		for (int i = 0; i < path_index; i++) {
			pair<Stajaliste*, Linija*> p;
			p.first = this->vS->at(path[i].first);
			p.second = path[i].second;
			v.push_back(p);
		}

		this->izlaz.push_back(v);

		this->numPaths++;
	}
	else if (!this->hasFirst || this->strategija->condition(path, path_index) < this->examineParameter) {
		for (int i = 0; i < this->adj[u].size(); i++) {

			if (!visited[this->adj[u].at(i).first]) {
				path[path_index].second = this->adj[u].at(i).second;
				printAllPathsUtil(this->adj[u].at(i).first, d, visited, path, path_index);
			}
		}
	}


	path_index--;
	visited[u] = false;
}