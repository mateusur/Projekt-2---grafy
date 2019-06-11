#include <iostream>
#include "generator.h"
#include "algorytm.h"
#include <string>

using namespace std;
using tp = chrono::time_point<std::chrono::system_clock>;
using duration = chrono::duration<float>;

int main()
{
	tp start;
	duration d;

	obslugapliku odczyt;
	int rozmiar=1;
	string sciezka;

	generowanie(10, 1, rozmiar);
	sciezka.clear();
	sciezka += to_string(rozmiar) + ".txt"; //utowrzenie pliku o nazwie 1.txt

	cout << "PRZYKLADOWE DZIALANIE PROGRAMU" << endl;
	cout << "PELNY GRAF O 10 WIERZCHOLKACH" << endl << endl;
	
	int ** macierz = odczyt.wczytaj(rozmiar, sciezka); //wczytanie grafu z pliku
	start = chrono::system_clock::now();
	dane* tab = Dijkstra(macierz, rozmiar, 0);
	d = chrono::system_clock::now() - start;
	odczyt.zapiszczas_macierz(d);

	cout << "Rozwiazanie dla reprezentacji w postaci macierzy sasiedztwa: " << endl;
	cout << "Pocz.\tDroga\tDystans" << endl;
	wypiszdane(tab, rozmiar);

	lista* graf = konwertuj(macierz, rozmiar); //kontwersja
	start = chrono::system_clock::now();
	tab = Dijkstra_lista(graf, rozmiar, 0);
	d = chrono::system_clock::now() - start;
	odczyt.zapiszczas_lista(d);

	cout << "Rozwiazanie dla reprezentacji w postaci listy sasiedztwa: " << endl;
	cout << "Pocz.\tDroga\tDystans" << endl;
	wypiszdane(tab, rozmiar);

	
	//Poni¿ej zakomentowany fragment programu sluzacy do testow programu i zapisu wynikow

	/*double wypelnienie[] = { 1, 0.75, 0.5, 0.25 };
	int rozmiary[] = { 10, 50, 100, 500, 1000};
	int numer = 0;
	
	for (int i = 0; i < 5; i++) //petla rozmiarow
	{
		for (int j = 0; j < 4; j++) //petla wypelnienia
		{
			for (int k = 0; k < 100; k++) //ilosc grafow do wygenerowania
			{
				generowanie(rozmiary[i], wypelnienie[j], numer);
				numer++;
			}
		}
	}*/
	
	/*for (int i = 0; i < 500; i++)
	{
		sciezka.clear();
		sciezka += to_string(i) + ".txt";
		
		int ** macierz = odczyt.wczytaj(rozmiar, sciezka);
		start = chrono::system_clock::now();
		dane* tab = Dijkstra(macierz, rozmiar, 0);
		d = chrono::system_clock::now() - start;
		odczyt.zapiszczas_macierz(d);
		
		cout << "Wezel\tPoprz.\tDystans" << endl;
		wypiszdane(tab, rozmiar);
		
		lista* graf = konwertuj(macierz, rozmiar);
		start = chrono::system_clock::now();
		tab = Dijkstra_lista(graf, rozmiar, 0);
		d = chrono::system_clock::now() - start;
		odczyt.zapiszczas_lista(d);
		
		cout << "Wezel\tPoprz.\tDystans" << endl;
		wypiszdane(tab, rozmiar);		
	}*/


	system("pause");
	return 0;
}