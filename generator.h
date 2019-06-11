#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "algorytm.h"
#include "lista.h"

using namespace std;
using tp = chrono::time_point<std::chrono::system_clock>;
using duration = chrono::duration<float>;


class obslugapliku
{
	fstream plik;
	
public:
	void zapis(int** tablica, int rozmiar, int numer) // zapisywanie tablicy do pliku
	{
		string sciezka = /*"data//" +*/ to_string(numer) + ".txt"; // towrzenie pliku .txt
		plik.open(sciezka, fstream::out | fstream::app);
		int liczba_krawedzi = 0;
		for (int i = 0; i < rozmiar; i++)
			for (int j = 0; j < rozmiar; j++)
			{
				if (tablica[i][j] > 0)
				{
					liczba_krawedzi++;
				}
			}				
		plik << liczba_krawedzi << " " << rozmiar << " " << "0" << endl;

		for (int i = 0; i < rozmiar; i++) //zapis do pliku
		{
			for (int j = 0; j < rozmiar; j++) 
			{
				if(tablica[i][j]>0)
				plik << i << " " << j << " " << tablica[i][j] << endl; 
			}
		}
		plik << endl;
		plik.close();
	}

	int** wczytaj(int &rozmiar, string sciezka) 
	{
		plik.open(sciezka, fstream::in);
		int liczba_krawedzi, wierzcholek_startowy, wierzcholek_poczatkowy, wierzcholek_koncowy, waga;
		plik >> liczba_krawedzi;
		plik >> rozmiar;
		plik >> wierzcholek_startowy;
		int **tablica = new int *[rozmiar]; //alokacja pamieci
		for (int i = 0; i < rozmiar; ++i)
		{
			tablica[i] = new int[rozmiar]; //alokacja pamieci
			for (int j = 0; j < rozmiar; ++j) //wype³nienie macierzy zerami
				tablica[i][j] = 0;
		}
		for (int j = 0; j < liczba_krawedzi; j++) //wype³nienie zadanym szeregiem danych
		{
			plik >> wierzcholek_poczatkowy >> wierzcholek_koncowy >> waga;
			tablica[wierzcholek_poczatkowy][wierzcholek_koncowy] = waga;
		}
		//w celu sprawdzenia czy dobrze wczytuje z pliku odkomentowac ta funckje
		/*cout << "TABLICA WCZYTANA Z PLIKU" << endl;
		for (int i = 0; i < rozmiar; ++i, cout << endl)
			for (int j = 0; j < rozmiar; ++j)
				cout << tablica[i][j] << '\t';*/
		cout << endl;
		plik.close();
		return tablica;
	}
	void zapiszczas_macierz(duration d) // zapisz czasu do pliku
	{
		string sciezka = "zapisczasu_macierz.txt";
		plik.open(sciezka, fstream::out | fstream::app);
		if (plik.is_open())
		{
			plik << d.count();
			plik << endl;
		}
		else
			cout << "Nie udalo sie zapisac do pliku";

		plik.close();
	}
	void zapiszczas_lista(duration d) // zapisz czasu do pliku
	{
		string sciezka = "zapisczasu_lista.txt";
		plik.open(sciezka, fstream::out | fstream::app);
		if (plik.is_open())
		{
			plik << d.count();
			plik << endl;
		}
		else
			cout << "Nie udalo sie zapisac do pliku";

		plik.close();
	}

};

lista* konwertuj(int** macierz, int liczba_elementow)
{
	lista* graf = new lista[liczba_elementow];
	for (int i = 0; i < liczba_elementow; i++)
	{
		for (int j = 0; j < liczba_elementow; j++)
		{
			if (macierz[i][j] > 0)
				graf[i].dodaj_element(j, macierz[i][j]);

		}
	}
	//for (int i = 0; i < liczba_elementow; i++) {
	//	cout << i << ": " << endl;
	//	//graf[i].wyswietl();

	//}
	return graf;
}

void generowanie(int rozmiar, double wypelnienie, int numer)
{
	int  procent = (1 - wypelnienie)*(rozmiar*(rozmiar - 1));
	int l_zer = 0;
	int **tab2 = new int *[rozmiar]; //alokacja pamieci
	for (int i = 0; i < rozmiar; ++i)
	{
		tab2[i] = new int[rozmiar]; //alokacja pamieci
		for (int j = 0; j < rozmiar; ++j)
			//wpisanie randomowych wartosci do tablicy
		{
				tab2[i][j] = (rand() % 10 + 1);
		}
	}

	for (int p = 0; p < rozmiar; p++)
	{
		tab2[p][p] = 0;
	}

	while (l_zer != procent)
	{
		int kolumna = rand() % rozmiar;
		int wiersz = rand() % rozmiar;
		if (tab2[wiersz][kolumna] != 0)
		{
			tab2[wiersz][kolumna] = 0;
			l_zer++;
		}

	}

	obslugapliku plik;
	/*cout << "TABLICA" << endl;
	for (int i = 0; i < rozmiar; ++i, cout << endl)
		for (int j = 0; j < rozmiar; ++j)
			cout << tab2[i][j] << '\t';
	cout << endl;*/
	plik.zapis(tab2, rozmiar, numer);

	//zniszcz tab2
	for (int i = 0; i < rozmiar; ++i)
		delete[] tab2[i]; //uwolnienie pamieci
	delete[] tab2;
}

#endif GENERATOR_H