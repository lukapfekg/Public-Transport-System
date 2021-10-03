#include "Strategija.h"
#include <iostream>

std::string Strategija::execute(std::vector<std::vector<std::pair<Stajaliste*, Linija*>>>* v) {
	return  this->ispis(&v->at(0));
}

int Strategija::condition(std::pair<int, Linija*> path[], int path_index) {
	return 0;
}


std::string Strategija::ispis(std::vector<std::pair<Stajaliste*, Linija*>>* v) {
	std::string output = "->" + v->at(1).second->getNaziv() + "\n" + std::to_string(v->at(0).first->getSifra()) + " ";
	Linija* l = v->at(1).second;
	for (int i = 1; i < v->size(); i++) {
		if (l->getNaziv() != v->at(i).second->getNaziv()) {
			output += '\n';
			output += l->getNaziv() + "->";
			l = v->at(i).second;
			output += l->getNaziv() + "\n";
			output += std::to_string(v->at(i - 1).first->getSifra()) + " ";
		}
		output += std::to_string(v->at(i).first->getSifra()) + " ";
	}
	output += '\n';
	return output;
}



std::string NaprednaStrategijaA::execute(std::vector<std::vector<std::pair<Stajaliste*, Linija*>>>* v) {
	return this->ispis(&v->back());
}

int NaprednaStrategijaA::condition(std::pair<int, Linija*> path[], int path_index) {
	return path_index-1;
}


std::string NaprednaStrategijaB::execute(std::vector<std::vector<std::pair<Stajaliste*, Linija*>>>* v) {
	return this->ispis(&v->back());
}

int NaprednaStrategijaB::condition(std::pair<int, Linija*> path[], int path_index) {
	int k = 0;
	Linija* l = nullptr;

	for (int i = 0; i < path_index; i++) {
		if (l != path[i].second) {
			k++;
			l = path[i].second;
		}
	}

	return k;
}

