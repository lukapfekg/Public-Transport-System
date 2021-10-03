#pragma once

#include <vector>
#include "Linija.h"
#include "Stajaliste.h"


class Strategija {
public:
	Strategija() {}

	virtual std::string execute(std::vector<std::vector<std::pair<Stajaliste*, Linija*>>>* v);
	virtual int condition(std::pair<int, Linija*> path[], int path_index);
	std::string ispis(std::vector<std::pair<Stajaliste*, Linija*>>* v);


};

class NaprednaStrategijaA : public Strategija {
public:
	NaprednaStrategijaA() :Strategija() {}

	std::string execute(std::vector<std::vector<std::pair<Stajaliste*, Linija*>>>* v) override;
	int condition(std::pair<int, Linija*> path[], int path_index) override;

};

class NaprednaStrategijaB : public Strategija {
public:
	NaprednaStrategijaB() :Strategija() {}

	std::string execute(std::vector<std::vector<std::pair<Stajaliste*, Linija*>>>* v) override;

	int condition(std::pair<int, Linija*> path[], int path_index) override;
};