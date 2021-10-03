#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Linija.h"
#include "Izuzeci.h"
#include "Stajaliste.h"


namespace Funkcije {

	void readFileStajalista(std::vector<Stajaliste*>* v, std::string filename) {
		try {
			v->clear();
			std::ifstream infile(filename);
			if (!infile) throw GUniversal("nije otvoren fajl!");
			std::string line;
			int i = 0;
			while (std::getline(infile, line)) {
				std::istringstream iss(line);

				int a;
				std::string b, c;

				if (!(iss >> a >> b)) { break; }
				while (iss >> c)
					b += " " + c;

				Stajaliste* s = new Stajaliste(a, b, i);
				v->push_back(s);
				s = nullptr;
				delete s;
				i++;
			}
		}
		catch (std::exception const& e) {
			return;
		}


	}

	void readFileLinije(std::vector<Linija*>* vL, std::vector<Stajaliste*>* vS, std::string filename) {
		try {
			vL->clear();
			std::ifstream infile(filename);
			if (!infile) throw GUniversal("Nije otvoren fajl!!!");
			std::string line;
			while (std::getline(infile, line)) {
				std::istringstream iss(line);
				std::string token;

				std::string a;
				int b;
				iss >> a;
				Linija* l = new Linija(a);

				std::getline(iss, token, '#');
				std::istringstream ss(token);
				while (ss >> b) {
					for (int i = 0; i < vS->size(); i++) {
						if (vS->at(i)->getSifra() == b) {
							l->addStajalisteA(vS->at(i));
							vS->at(i)->addLinija(l);
							break;
						}
					}
				}
				std::getline(iss, token, '#');
				std::istringstream ss1(token);
				while (ss1 >> b) {
					for (int i = 0; i < vS->size(); i++) {
						if (vS->at(i)->getSifra() == b) {
							l->addStajalisteB(vS->at(i));
							vS->at(i)->addLinija(l);
							break;
						}
					}
				}
				vL->push_back(l);
				l = nullptr;
				delete l;
			}
		}
		catch (std::exception* e) {
			return;
		}
	}

	bool isInVect(std::vector<std::pair<std::string, int>>* s, std::string naziv) {
		for (int i = 0; i < s->size(); i++) {
			if (s->at(i).first == naziv) {
				s->at(i).second++;
				return true;
			}
		}
		return false;
	}

	std::string statistika(std::string naziv, std::vector<Linija*>* v) {
		std::string output = naziv + "\n";
		std::vector<std::pair<std::string, int>> vect;
		Linija* l = nullptr;

		for (int i = 0; i < v->size(); i++)
			if (v->at(i)->getNaziv() == naziv) {
				l = v->at(i);
				break;
			}
		if (l != nullptr) {

			for (int i = 0; i < l->stajalistaA.size(); i++) {
				for (int j = 0; j < l->stajalistaA.at(i)->getLinije()->size(); j++) {
					if (naziv != l->stajalistaA.at(i)->getLinije()->at(j)->getNaziv())
						if (!isInVect(&vect, l->stajalistaA.at(i)->getLinije()->at(j)->getNaziv())) {
							vect.emplace_back(l->stajalistaA.at(i)->getLinije()->at(j)->getNaziv(), 0);
						}
				}
			}

			int k = -1, pos = 0;

			sort(vect.begin(), vect.end());
			for (int i = 0; i < vect.size(); i++) {
				output += vect.at(i).first + " ";
				if (vect.at(i).second > k) {
					k = vect.at(i).second;
					pos = i;
				}
			}

			output += "\n" + vect.at(pos).first;

			return output;
		}
		else return "";
	}

	void findStajalisteIndex(std::vector<Stajaliste*>& vS, int& a, int& b) {
		int r = -1, q = -1;
		for (int i = 0; i < vS.size(); i++) {
			if (vS.at(i)->getSifra() == a)
				r = vS.at(i)->getID();
			else if (vS.at(i)->getSifra() == b)
				q = vS.at(i)->getID();
		}

		if (r == -1 && q == -1) throw GUniversal("Odabrane stanice ne postoje!!!");
		if (r == -1) throw GUniversal("Prva stanica ne postoji!!!");
		if (q == -1) throw GUniversal("Druga stanica ne postoji!!!");

		a = r;
		b = q;


	}

	std::string printStajalisteFromSifra(std::vector<Stajaliste*>& vS, int sifra) {
		std::string out = "";
		for (int i = 0; i < vS.size(); i++) {
			if (vS.at(i)->getSifra() == sifra) {
				out += vS.at(i)->ispis();
				break;
			}
		}
		return out;
	}

	std::string printLinijaFromSifra(std::vector<Linija*>& vS, std::string oznaka) {
		std::string out = "";
		for (int i = 0; i < vS.size(); i++) {
			if (vS.at(i)->getNaziv() == oznaka) {
				out += vS.at(i)->ispis();
				break;
			}
		}
		return out;
	}

}