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
void upisUDatoteku(vector<T> vektor,const string& imeFajla) {
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
		std::cout << "Successfully wrote to file: "<< imeFajla << endl;
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
	vector<Vozilo*> fabrikaVozila;
	stack<Vozilo*> automobili;
	queue<Vozilo*> kamioni;
	/*Automobil make_unique a("Audi", "A4", 2016, "Limuzina", "Prednji", 5);
	Kamion k("Mercedes", "Actros", 2010, 15000);
	fabrikaVozila.push_back(new Automobil("Audi", "A4", 2016, "Limuzina", "Prednji", 5));
	fabrikaVozila.push_back(new Kamion("Mercedes", "Actros", 2010, 15000));

	//cout << a.informacijeVozila() << endl;
	//fabrikaVozila.push_back(a);
	//cout << k.informacijeVozila() << endl;
	//fabrikaVozila.push_back(k);*/

	cout << "\n\nBroj proizvedenih vozila je: " << Vozilo::GetBrojProizvedenihVozila() << "\n\n";

	ucitajVozila("voziloCitajVozila.txt", fabrikaVozila);
	cout << "===========================================================\n";
	for (const auto& vozila : fabrikaVozila) {
		cout << *vozila << endl;
		if (dynamic_cast<Automobil*>(vozila)) {
			automobili.push(vozila);
			cout << "1";
		}
		else if (dynamic_cast<Kamion*>(vozila)) {
			kamioni.push(vozila);
			cout << "2";
		}
		
	}
	cout << "===========================================================\n";
	cout << "\nBroj proizvedenih vozila je: " << Vozilo::GetBrojProizvedenihVozila() << "\n\n";

	if (!fabrikaVozila.empty()) {
		qsort(&fabrikaVozila[0], fabrikaVozila.size(), sizeof(Vozilo*), porediVozila);
	}
	cout << "====================Sortirano po modelu====================\n";
	for (const auto& vozila : fabrikaVozila) {
		cout << *vozila << endl;
	}
	cout << "===========================================================\n";
	createTextFile(fabrikaVozila, "json.txt");
	cout << "Stack contents:" << endl;
	
	while (!automobili.empty()) {
		Vozilo* v = automobili.top();
		cout << *v << endl;
		automobili.pop();
	}

	// Demonstrating queue usage
	cout << "Queue contents:" << endl;
	while (!kamioni.empty()) {
		Vozilo* v = kamioni.front();
		cout << *v << endl;
		kamioni.pop();
	}

	for (auto v : fabrikaVozila) {
		delete v;
	}
	return 0;
}