#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <sstream>
#include <filesystem>
#include "Vozilo.h"
#include "Automobil.h"
#include "Kamion.h"
using namespace std;

int Vozilo::brojProizvedenihVozila = 0;
/*ostream& operator<<(ostream& out, const Vozilo vozilo) {
	out << vozilo.informacijeVozila();
	return out;
}*/
template <typename T>
void upisiVektorUDatoteku(vector<T> vektor, const string& imeFajla) {
	ofstream outFile(imeFajla, ios::app);
	if (!outFile) {
		cerr << "Greska u otvaranju datoteke " << imeFajla << endl;
		return;
	}
	for (const auto& vozila : vektor) {
		outFile << *vozila << endl;
	}
}
template <typename T>
void upisiObjekatUDatoteku(const T& objekat, const string& imeFajla) {
	ofstream outFile(imeFajla, ios::app);
	if (!outFile) {
		cout << "Greska u otvaranju datoteke(" << imeFajla << ")" << endl;
		return;
	}
	//cout << "UPISANO :: " << objekat << endl;
	outFile << objekat << endl;
	if (outFile.fail()) {
		std::cerr << "Greska u upisu(" << imeFajla << ")" << endl;
	}
	else {
		std::cout << "Uspesno upisano u fajl(" << imeFajla << ")" << endl;
	}
	outFile.close();
}

void ucitajVozila(const std::string& imeFajla, vector<Vozilo*>& fabrikaVozila) {
	ifstream fajl(imeFajla);
	if (!fajl) {
		cerr << "Greska u otvaranju fajla " << imeFajla << endl;
		return;
	}

	string linija;
	while (getline(fajl, linija)) {
		istringstream iss(linija);
		string tip;
		iss >> tip;
		if (tip == "Automobil") {
			string marka, model, pogon, tip;
			int godina, brojVrata;
			iss >> marka >> model >> godina >> tip >> pogon >> brojVrata;
			fabrikaVozila.push_back(new Automobil(marka, model, godina, tip, pogon, brojVrata));
		}
		else if (tip == "Kamion") {
			string marka, model;
			int godina, nosivost;
			iss >> marka >> model >> godina >> nosivost;
			fabrikaVozila.push_back(new Kamion(marka, model, godina, nosivost));
		}
		else {
			cerr << "Nepoznat tip vozila: " << tip << endl;
		}
	}

	fajl.close();
}
int porediVozila(const void* a, const void* b) {
	const Vozilo* voziloA = *reinterpret_cast<const Vozilo* const*>(a);
	const Vozilo* voziloB = *reinterpret_cast<const Vozilo* const*>(b);

	if (!voziloA || !voziloB) {
		return 0;
	}

	// Uporedimo po marki
	return voziloA->marka.compare(voziloB->marka);
}


int main() {

	vector<Vozilo*> fabrikaVozila;

	string komanda;
	stack<Vozilo*> stackVozila;
	queue<Vozilo*> queueVozila;
	Vozilo* vozilo = nullptr;

	//KOMANDE
	map<std::string, int> komande = {
		{"unosA", 1},
		{"unosK", 2},
		{"ispisStek", 3},
		{ "ispisQueue", 4 },
		{ "upisStek", 5 },
		{ "upisQueue", 6 },
		{ "upisDatoteka", 7 },
		{ "ispisiVektor", 12},
		{ "sortirajVektor", 13},
		{ "prikaz", 8 },
		{ "brisanje", 9 },
		{ "pomoc", 10 },
		{ "izlaz", 11 }
	};

	while (true) {
		cout << "Komanda (unesi pomoc za pomoc): "; cin >> komanda;

		if (komande.find(komanda) == komande.end()) {
			cout << "Nepoznata komanda\n";
			continue;
		}

		int izbor = komande[komanda];

		switch (izbor)
		{
		case 1: {
			string marka, model, pogon, tip;
			int godina, brojVrata;
			cout << "--Unos automobila--\nMarka:"; cin >> marka;
			cout << "Model:"; cin >> model; fflush(stdin);
			cout << "Pogon:"; cin >> pogon; fflush(stdin);
			cout << "Tip(Limuzina,Hecbek,Karavan,...):"; cin >> tip; fflush(stdin);
			cout << "Godina:"; cin >> godina;
			cout << "Broj vrata"; cin >> brojVrata;
			Automobil* a = new Automobil(marka, model, godina, tip, pogon, brojVrata);
			cout << "\n--Uneto vozilo--\n";
			cout << a->informacijeVozila() << endl;
			vozilo = a;
			break;
		}
		case 2: {
			string marka, model;
			int godina, nosivost;
			cout << "--Unos kamiona--\nMarka:";
			cin >> marka; fflush(stdin);
			cout << "Model:"; cin >> model; fflush(stdin);
			cout << "Godina:"; cin >> godina;
			cout << "Nosivost:"; cin >> nosivost;
			Kamion* k = new Kamion(marka, model, godina, nosivost);
			cout << "\n--Uneto vozilo--\n";
			cout << k->informacijeVozila() << endl;
			vozilo = k;
			break;
		}
		case 3: //ispis Stack
			if (stackVozila.empty()) {
				cout << "Stek je prazan." << endl;
			}
			else {
				stack<Vozilo*> pomocniStek = stackVozila;
				while (!pomocniStek.empty()) {
					cout << pomocniStek.top()->informacijeVozila() << endl;
					pomocniStek.pop();
				}
			}
			break;
		case 4://ispis Queue
			if (queueVozila.empty()) {
				cout << "Queue je prazan." << endl;
			}
			else {
				queue<Vozilo*> pomocniQueue = queueVozila;
				while (!pomocniQueue.empty()) {
					cout << pomocniQueue.front()->informacijeVozila() << endl;
					pomocniQueue.pop();
				}
			}
			break;
		case 5: //upis Stack
			if (vozilo) {
				stackVozila.push(vozilo);
				cout << "Vozilo je upisano u stek." << endl;
			}
			else {
				cout << "Nema trenutnog vozila za upis u stek." << endl;
			}
			break;
		case 6: //upis Queue
			if (vozilo) {
				queueVozila.push(vozilo);
				cout << "Vozilo je upisano u queue." << endl;
			}
			else {
				cout << "Nema trenutnog vozila za upis u queue." << endl;
			}
			break;
		case 7:
			upisiObjekatUDatoteku(vozilo, "voziloCitajVozila.txt");
			break;
		case 8:
			cout << "--Trenutno vozilo--\n";
			if (vozilo) {
				cout << vozilo->informacijeVozila() << endl;
			}
			else {
				cout << "Nema trenutnog vozila" << endl;
			}
			break;
		case 9:
			delete vozilo;
			vozilo = nullptr;
			cout << "Trenutni objekat obrisan." << endl;
			break;
		case 10:
			cout << "Komande:\n"
				<< "1/unosA - Unos Automobila\n"
				<< "2/unosK - Unos Kamiona\n"
				<< "8/prikaz - Prikazuje trenutni objekat\n"
				<< "10/pomoc - Pomoc\n"
				<< "3/ispisStek - Ispis steka\n"
				<< "4/ispisQueue - Ispis queue\n"
				<< "5/upisStek - Upisuje trenutni objekat u stek\n"
				<< "6/upisQueue - Upisuje trenutni objekat u queue\n"
				<< "7/upisDatoteka - Upisuje trenutni objekat u datoteku\n"
				<< "12/ispisiVektor - Cita iz datoteke,smesta objekete u Vektor i ispisuje ih\n"
				<< "13/sortirajVektor - Sortira vektor ako je ucitan iz datoteke koristeci qsort i ispisuje sortiran vektor\n"
				<< "9/brisanje - Brise trenutni objekat\n"
				<< "11/izlaz - Kraj programa\n";
			break;
		case 11:
			delete vozilo;
			return 0;
		case 12:
			ucitajVozila("voziloCitajVozila.txt", fabrikaVozila);
			for (const auto& vozila : fabrikaVozila) {
				cout << *vozila << endl;
			}
			break;
		case 13:
			if (!fabrikaVozila.empty()) {
				qsort(&fabrikaVozila[0], fabrikaVozila.size(), sizeof(Vozilo*), porediVozila);
				cout << "--Sortirani vektor--" << endl;
				for (const auto& vozila : fabrikaVozila) {
					cout << *vozila << endl;
				}
			}
			else {
				cout << "Vektor je prazan iskoristite ispisiVektor da bi napunili vektor podacima" << endl;
			}
		default:
			cout << "Nepoznata komanda." << endl;
		}
	}

	return 0;
}



