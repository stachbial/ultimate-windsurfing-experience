
#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>


namespace FileWork
{
	void wczytaj_stan_gry(GameState& gs);//funkcja inicjalizuje pola struktury podanej w parametrze na bodstawie odczytu z pliku "ostatniZapis"
	void zapisz_stan_gry(GameState gs);//funkcja zapisuje aktualne wartoœci pól struktury do pliku "ostatniZapis"
	void zapisz_do_listyGraczy(GameState gs);//funkcja zapisuje strukturê do pliku "listaGraczy"
	void ustal_podium();//funkcja sortuje plik "listaGraczy" w kolejnosci malejacej pod wzgledem czasu ukonczenia rozgrywki
	std::string zwroc_zawodnika_podium(int nrMiejsca);//zwraca ³añcuch znaków z informacj¹ na temat zawodnika z numerem miejsca na podium podanego w parametrze
	void swapRecords(GameState& oddaj, GameState& przyjmij);//zamien wartosci rekordow w strukturach
	std::string convertToString(char* charArray);//zmien tablice typu char ze struktury na std::string
};

