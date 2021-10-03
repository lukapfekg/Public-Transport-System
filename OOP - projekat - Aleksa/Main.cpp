#include <iostream>
#include <fstream>
#include "Stajaliste.h"
#include "Linija.h"
#include "Funkcije.h"
#include "Graph.h"
#include "Strategija.h"
#include "Main.h"


int main() {
	int i;
	vector<Stajaliste*> vS;
	vector<Linija*> vL;
	int odabir;
	std::ofstream outFile;
	string s;

	while (1) {
		cout << "Dobrodosi u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju :" << endl;
		cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl << "0. Kraj rada" << endl << endl;
		cin >> i;
		cout << endl;
		if (i == 1) {
			while (1) {
				try {
					cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl << endl;
					cin >> s;
					cout << endl;

					Funkcije::readFileStajalista(&vS, s);
					if (vS.size() == 0) throw GUniversal("Informacije o stajalistima nisu procitane!!!");

					cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl << endl;
					cin >> s;
					cout << endl;

					Funkcije::readFileLinije(&vL, &vS, s);
					if (vL.size() == 0) throw GUniversal("Informacije o linijama nisu procitane!!!");

					break;
				}
				catch (std::exception* e) {
					cout << endl << e->what() << endl;
					continue;
				}
			}
			Graph* g = new Graph(vS.size(), &vS);
			Strategija* strat = nullptr;
			while (1) {
				cout << "Mreza gradskog prevoza je uspesno ucitana. Molimo Vas, odaberite opciju:" << endl;
				cout << "1. Prikaz informacija o stajalistu" << endl;
				cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
				cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
				cout << "4. Pronalazak putanje izmedju dva stajalista" << endl;
				cout << "0. Kraj rada" << endl << endl;

				cin >> i;

				cout << endl;

				if (i == 1) {
					cout << "Molimo Vas, unesite sifru stajalista cije osnovne informacije zelite da prikazete." << endl;
					cout << endl;
					int sifra;
					cin >> sifra;
					cout << endl;

					if (Funkcije::printStajalisteFromSifra(vS, sifra) == "") throw GUniversal("Uneto stajaliste ne postoji!!!");

					outFile.open("stajaliste_" + std::to_string(sifra) + ".txt");

					outFile << Funkcije::printStajalisteFromSifra(vS, sifra);

					outFile.close();
					cout << endl;
				}
				else if (i == 2) {
					cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
					cout << endl;
					cin >> s;
					cout << endl;

					if (Funkcije::printLinijaFromSifra(vL, s) == "") throw GUniversal("Uneta linija ne postoji!!!");

					outFile.open("linija_" + s + ".txt");
					cout << Funkcije::printLinijaFromSifra(vL, s) << endl;
					outFile << Funkcije::printLinijaFromSifra(vL, s);
					outFile.close();

					cout << endl;
				}
				else if (i == 3) {
					cout << "Molimo Vas, unesite oznaku linije ciju statistiku zelite da prikazete." << endl;
					cout << endl;
					cin >> s;
					cout << endl;

					std::string statistika = Funkcije::statistika(s, &vL);

					if (statistika == "") throw GUniversal("Uneta linija nije pronadjena!!!");

					outFile.open("statistika_" + s + ".txt");
					cout << statistika << endl;
					outFile << statistika;
					outFile.close();

				}
				else if (i == 4) {
					int a, b;
					while (1) {
						try {

							cout << "Molimo vas unesite linije za koje zelite naci putanju:" << endl << endl;
							cout << "Prva linija: ";
							cin >> a;
							cout << endl;
							cout << "Druga linija: ";
							cin >> b;
							cout << endl;

							outFile.open("putanja_" + std::to_string(a) + "_" + std::to_string(b) + ".txt");
							Funkcije::findStajalisteIndex(vS, a, b);
							
							break;
							
						}
						catch (std::exception* e) {

							std::cout << endl << e->what() << endl;
							continue;
						}
					}
					while (1) {
						cout << "Molimo vas odaberite opciju za pronalazak putanje:" << endl;
						cout << "1. Prnalazak bilo koje putanje" << endl;
						cout << "2. Pronadji putanju sa najmanje stanica" << endl;
						cout << "3. Pronadji putanju sa najmanje presedanja" << endl;
						cout << endl;
						cin >> i;
						cout << endl;
						if (i == 1) {
							strat = new Strategija();
						}
						else if (i == 2) {
							strat = new NaprednaStrategijaA();
						}
						else if (i == 3) {
							strat = new NaprednaStrategijaB();
						}
						else {
							continue;
						}
						g->setStrategija(strat);

						outFile << g->execute(a, b);
						outFile.close();
						cout << endl;

						break;
					}
				}
				else if (i == 0) {
					break;
				}
				else {
					std::cout << "Ne postoji opcija sa datim brojem!" << std::endl << std::endl;
				}


			}


		}
		if (i == 0) {
			break;
		}

		cout << "Ne postoji izbor!" << endl;





	}

}




