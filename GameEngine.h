#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SegmentGUI.h"
#include <string>
#include "GameState.h"
#include <cstdlib>
#include "FileWork.h"
#include "Game.h"
#include "BackGround.h"


class GameEngine
{
public:
	GameEngine(sf:: RenderWindow& window, sf::View& View);
	~GameEngine() {};

	void guiUpdate( sf::Event& event);											//funkcja obsluguj¹ca poruszanie sie po menu na podstawie danych wejsciowych z klawiatury
	void gamePlayUpdate(float deltaTime);
	void BGupdate(float deltaTime);

	void draw(sf::RenderWindow& window);									//rysuj menu w oknie

private:
//metody
	void selected0(unsigned int& visibleSegment);							//funkcja ob³uguj¹ca 1 przycisk
	void selected1(unsigned int& visibleSegment);							//funkcja ob³uguj¹ca 2 przycisk
	void selected2(unsigned int& visibleSegment);							//funkcja ob³uguj¹ca 3 przycisk
	void selected3(unsigned int& visibleSegment);							//funkcja ob³uguj¹ca 4 przycisk
	void selected4(unsigned int& visibleSegment);							//funkcja ob³uguj¹ca 5 przycisk

	unsigned int getVisibleSegment() { return visibleSegment; }
	std::string getNick() { return inputNick; }
	unsigned int getPoziomT() { return poziomT; }

	//NIEREGULARNY KSZTALT
	void initializeIRRshape();												//"konstruktor" ksztaltu
	void drawIRRshape(sf::RenderWindow& window) { window.draw(irregularShape); }//rysowanie ksztaltu
	void MoveIRRshape(float deltaTime);										//animacja ksztaltu

	//zmienne
	sf::RenderWindow* window;												//wskaznik na okno przekazane w kontruktorze aby ³atwo tworzyæ obiekty SegmentGUI
	sf::View* view;															//wskaznik na widok
	float width;															//szerokosc okna
	float height;															//wysokosc okna
	
	sf::Music theme;

	SegmentGUI* segmentGUI;									//wskaznik na dynamicznie tworzony obiekt klasy SegmentGUI
	Game* game;																//wskaznik na obiekt rozgrywki
	BackGround* bg;
	bool isGamePlayed;													//czy odbywa siê rozgrywka
	unsigned int visibleSegment;											//zmienna definujaca ktory segment interfejsu powinien byc teraz obs³ugiwany
	std::string inputNick;													//zmienna przechowuj¹ca nick gracza
	unsigned int poziomT;
	GameState gs, innitialGameState;
	sf::Vector2f viewPos = sf::Vector2f(0.f, 0.f);							//inicjacja pozycji widoku
	bool isViewReset;													// czy ustawiono spowrotem pozycje widoku?
	
	//nieregularny kszta³t
	sf::VertexArray irregularShape;										//na potrzeby zakresu projektu
	sf::Vector2f irrShapePos[7];										//tablica pozycji wierzcho³ków kszta³tu
	int IRRshapeMoves = 0;												//ilosc dotychczasowych przesuniec
	float totalTime;													//czas od ostatniego ruchu
	float irrOffset = 20.f;												//o ile poruszac
	bool moveRight;														//czy poruszac w prawo
	bool showIRRshape;													//czy pokazywac ksztalt
};

