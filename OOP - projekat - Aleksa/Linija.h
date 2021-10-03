#ifndef LINIJA
#define LINIJA
#include <string>
#include <vector>
#include "Stajaliste.h"

class Linija {
	std::string naziv;

public:
	std::vector<Stajaliste* > stajalistaA, stajalistaB;

	Linija(std::string naziv);

	inline std::string getNaziv() const { return naziv; }

	void addStajalisteA(Stajaliste* s);
	void addStajalisteB(Stajaliste* s);

	int getIdNextA(int sifra);
	int getIdNextB(int sifra);

	std::string ispis();



};

#endif