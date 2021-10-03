#include "Stajaliste.h"
#include "Linija.h"
#include <algorithm>

Stajaliste::Stajaliste(int sifra, std::string naziv, int id) : sifra(sifra), naziv(naziv), id(id) {}

void Stajaliste::addLinija(Linija* l) {
	for (int i = 0; i < this->linije.size(); i++)
		if (l->getNaziv() == this->linije.at(i)->getNaziv()) return;
	this->linije.push_back(l);
}

std::string Stajaliste::ispis() {
	std::vector<std::string> vect;
	std::string str = std::to_string(this->sifra);
	str += " ";
	str += this->naziv;
	str += "[";

	for (int i = 0; i < this->linije.size(); i++) {
		vect.push_back(this->linije.at(i)->getNaziv());
	}

	sort(vect.begin(), vect.end());

	for (int i = 0; i < this->linije.size(); i++) {
		if (i != 0) str += " ";
		str += vect.at(i);
	}

	str += "]";
	return str;
}
