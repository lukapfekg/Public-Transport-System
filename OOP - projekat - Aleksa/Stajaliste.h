#ifndef STAJALISTE
#define STAJALISTE
#include <string>
#include <vector>


class Linija;

class Stajaliste {
	int id;
	int sifra;
	std::string naziv;
	std::vector<Linija*> linije;

public:
	Stajaliste(int sifra, std::string naziv, int id);

	inline int getSifra() const { return sifra; }
	inline std::string getNaziv() const { return naziv; }
	inline int getID() const { return id; }

	void addLinija(Linija* l);

	inline const std::vector<Linija*>* getLinije() const { return &linije; }

	std::string ispis();
};
#endif // !STAJALISTE
