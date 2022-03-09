#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Shark.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Player.h"

/*
klasa map:
tworzy niewidzialna siec kafelkow 100.f x 100.f
odpowiada za tworzenie i umiejscowienie przeciwnikow na podstawie pozycji tych kafelkow
sprawdza kolizcje z graczem
*/

class Map
{
public:
	typedef struct {
		sf::RectangleShape tile;												//kafelek typu rectangleshape
		sf::Vector2f tilePos;													//pozycja kafelka
		bool placeEnemy;														//czy ten kafelek  to spawn przeciwnika
		bool isShark;															//czy ten przeciwnik to rekin? (jesli nie to statek)
		bool isPlaced;															//czy zosta³ juz postawiony?
	}tile;

	Map(unsigned int poziomT, sf::RenderWindow& window);
	~Map();
	void Update(float deltaTime, sf::View& view, Player* player, bool isHELPscreen);												//funkcja aktualizujaca informacje ktora czesc mapy rysowac na podstawie inf z widoku
	void Draw(sf::RenderWindow& window);										//funkcja rysujaca
	float getMapEndX() { return gameEndX; }									//zwroc granice mapy po ktorej nastepuje koniec rozgrywki
	float getViewMovementBorder() { return stopViewMove; }						//zwroc granice po ktorej nie nalezy poruszac widokiem
	float getUpperMapBorder() { return upperBorderY; }							//zwroc gorna granice mapy
	
	std::vector<Ship>ships;														//wektor aktualnie istniejacych statkow
	std::vector<Shark>sharks;													//wektor aktualnie istniejacych rekinow
	
private:
	tile** tileMap;																//wsakznik na wskaznik tablicy typu tile w celu uzyskania tablicy dwuwymiarowej
	float tileSizeF= 100.f;														//dlugosc sciany poszczegolnego kafelka
	unsigned int tileSizeU = static_cast<unsigned>(tileSizeF);					//wersja unsigned int zmiennej tileSizeF
	int mapSizeY= 5;															//ilosc mapy w kafelkach w osi X
	int mapSizeX= 150;															//ilosc mapy w kafelkach w osi X
	int fromX = 0, toX = 0;														//od k¹d, do k¹d renderowana bêdzi zawartoœæ mapy
	int pomoczaY;																//zmienna pomocnicza, aby przeciwnicy nie pojawiali sie w tym samym rzedzie
	int ruchRekina;																//losowo  wygenerowna zmienna okreslajaca wektor ruchu rekinaint ruchRekina;
	float gameEndX;																//wspolrzedna x, do której musi dotrzec gracz aby zakonczyc rozgrywke(wygrac)
	sf::RectangleShape mapend;													//obiekt przechowujacy teksture zakonczenia mapy
	bool drawEnd;																//zmienna, na ktorej nalezy rysowac "mapend"
	float stopViewMove;															//zmienna od ktorej nie nalezy poruszac widokiem view
	float upperBorderY;															//zmienna przechowujaca informacje gdzie znajduje sie gorna krawedz mapy

	sf::Texture shipTexture;													//tektura statku
	sf::Texture sharkTexture;													//tekstura rekina
	sf::Texture endingMap;														//tekstura mety

	unsigned int enemyCount;													//co ile kafelkow nalezy postawic przeciwnika(zaleznie od poziomu trudnosci)
	unsigned int placeShip;														//co ile kafelkow przeciwnikiem ma byc statek

	sf::RenderWindow* window;
};

