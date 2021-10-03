#include "Linija.h"

Linija::Linija(std::string naziv) : naziv(naziv) {}

void Linija::addStajalisteB(Stajaliste* s) {
	this->stajalistaB.push_back(s);
}

int Linija::getIdNextA(int sifra) {
	for (int i = 0; i < this->stajalistaA.size() - 1; i++) {
		if (sifra == this->stajalistaA.at(i)->getSifra())
			return this->stajalistaA.at(++i)->getID();
	}

	return -1;
}

void Linija::addStajalisteA(Stajaliste* s) {
	this->stajalistaA.push_back(s);
}

int Linija::getIdNextB(int sifra) {
	for (int i = 0; i < this->stajalistaB.size() - 1; i++) {
		if (sifra == this->stajalistaB.at(i)->getSifra())
			return this->stajalistaB.at(++i)->getID();
	}

	return -1;
}

std::string Linija::ispis() {
	std::string str = this->naziv + " ";
	str += this->stajalistaA.at(0)->getNaziv() + "->" + this->stajalistaB.at(0)->getNaziv();
	for (int i = 0; i < this->stajalistaA.size(); i++)
		str += "\n" + std::to_string(this->stajalistaA.at(i)->getSifra()) + " " + this->stajalistaA.at(i)->getNaziv();
	for (int i = 0; i < this->stajalistaB.size(); i++)
		str += "\n" + std::to_string(this->stajalistaB.at(i)->getSifra()) + " " + this->stajalistaB.at(i)->getNaziv();
	return str;
}
