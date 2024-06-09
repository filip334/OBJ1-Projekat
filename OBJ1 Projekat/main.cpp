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
void upisUDatoteku(vector<T> vektor, const string& imeFajla) {
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
void upisObjektaUDatoteku(const T& objekat, const string& imeFajla) {
	ofstream outFile(imeFajla, ios::app);
	if (!outFile) {
		cout << "Greska u otvaranju datoteke " << imeFajla << endl;
		return;
	}
	//cout << "UPISANO :: " << objekat << endl;
	outFile << objekat << endl;
	if (outFile.fail()) {
		std::cerr << "Error writing to file: " << imeFajla << endl;
	}
	else {
		std::cout << "Successfully wrote to file: " << imeFajla << endl;
	}
	outFile.close();

	filesystem::path filePath = std::filesystem::absolute(imeFajla);
	cout << "Absolute path of the file: " << filePath << std::endl;
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
void createTextFile(const std::vector<Vozilo*>& vozila, const std::string& filename) {
	std::ofstream outputFile(filename);
	if (outputFile.is_open()) {
		outputFile << "[\n";
		for (const auto& vozilo : vozila) {
			map<string, string> voziloMap = vozilo->toMap();
			outputFile << "{\n";
			for (const auto& pair : voziloMap) {
				outputFile << "\t\"" << pair.first << "\": \"" << pair.second << "\",\n";
			}
			outputFile << "},\n\n";
		}
		outputFile << "]";
		outputFile.close();

		std::cout << "Tekstualna datoteka '" << filename << "' je uspesno kreirana." << std::endl;
	}
	else {
		std::cerr << "Nije moguce otvoriti datoteku za pisanje." << std::endl;
	}
}

int main() {

	//vector<Vozilo*> fabrikaVozila;

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
				std::cout << "Stek je prazan." << std::endl;
			}
			else {
				std::stack<Vozilo*> tempStack = stackVozila;
				while (!tempStack.empty()) {
					tempStack.top()->informacijeVozila();
					tempStack.pop();
				}
			}
			break;
		case 4://ispis Queue
			if (queueVozila.empty()) {
				std::cout << "Queue je prazan." << std::endl;
			}
			else {
				std::queue<Vozilo*> tempQueue = queueVozila;
				while (!tempQueue.empty()) {
					tempQueue.front()->informacijeVozila();
					tempQueue.pop();
				}
			}
			break;
		case 5: //upis Stack
			if (vozilo) {
				stackVozila.push(vozilo);
				vozilo = nullptr;
				std::cout << "Vozilo je upisano u stek." << std::endl;
			}
			else {
				std::cout << "Nema trenutnog vozila za upis u stek." << std::endl;
			}
			break;
		case 6: //upis Queue
			if (vozilo) {
				queueVozila.push(vozilo);
				vozilo = nullptr;
				std::cout << "Vozilo je upisano u queue." << std::endl;
			}
			else {
				std::cout << "Nema trenutnog vozila za upis u queue." << std::endl;
			}
			break;
		case 7:
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
				<< "unosA - Unos Automobila\n"
				<< "unosK - Unos Kamiona\n"
				<< "prikaz - Prikazuje trenutni objekat\n"
				<< "pomoc - Pomoc\n"
				<< "ispisStek - Ispis steka\n"
				<< "ispisQueue - Ispis queue\n"
				<< "upisStek - Upisuje trenutni objekat u stek\n"
				<< "upisQueue - Upisuje trenutni objekat u queue\n"
				<< "brisanje - Brise trenutni objekat\n"
				<< "izlaz - Kraj programa\n";
			break;
		case 11:

			delete vozilo;
			return 0;

		default:
			cout << "Nepoznata komanda." << endl;
		}
	}

	return 0;
}



/*Automobil make_unique a("Audi", "A4", 2016, "Limuzina", "Prednji", 5);
>>>>>>> Stashed changes
	Kamion k("Mercedes", "Actros", 2010, 15000);
	fabrikaVozila.push_back(new Automobil("Audi", "A4", 2016, "Limuzina", "Prednji", 5));
	fabrikaVozila.push_back(new Kamion("Mercedes", "Actros", 2010, 15000));

	//cout << a.informacijeVozila() << endl;
	//fabrikaVozila.push_back(a);
	//cout << k.informacijeVozila() << endl;
	//fabrikaVozila.push_back(k);*/


