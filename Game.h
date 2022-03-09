#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "GameState.h"
#include <vector>
#include <sstream>
#include "SegmentGUI.h"
class Game
{
public:
	Game(GameState& gs, sf::RenderWindow& window, sf::View& View, bool isGamePlayed); //konstruktor w przypadku tworzenia nowej gry
	~Game() {};

	void Update(float deltaTime);//aktualizacja animacji obiektow i zdarzen z nimi zwiazanych
	void Help_Esc_screenUpdate(sf::Event& keybordEvent);//obsluga elementow GUI np HELP/ESC  screen badz komunikat o wtgranej/przegranej
	
	void Draw(sf::RenderWindow& window);//funkcja rysujaca zawartosc rozgrywki
	
	bool isGamePlaying() { return isGamePlayed; }//czy zakonczono rozgrywke
	
private:
	//METODY
	void gramDalej();//funkcja obslugujaca wybor "gram dalej" w ESC screen 
	void saveANDquit();//funkcja obslugujaca wybor "zapisz i wyjdz" w ESC screen
	void justQuit();//funkcja obslugujaca "wyjdz bez zapisu" w ESC screen
	
	void getCUrrentTime(float czasShown);//zwraca dotychczasowy czas rozgrywki
	void resumeTime(float& czasToShow);//funkcja obslujaca zatrzymywanie czasu
	
	void gameLost();//funkcja wywolywania w momencie przegrania rozgrywki
	void gameWon();//funkcja wywolywana w momencie wygrania rozgrywki

	//ZMIENNE
	Player* player;																//tworz obiekt player 
	sf::Texture playerTexture;													//tesktura obiektu player
	Map* map;																	//wskaznik na mape (obiekt obslugujacy przeciwnikow)
	sf::RenderWindow* window;													//wskaznik na okno
	sf::View* View;
	GameState LoadState;														//struktura do ktorej zapisywane sa podtawowe parametry zwiazane z rozgrywka
//napisy i animacja serc
	//nick, aktualny czas i serca
	sf::Text nick, czas, help, esc;
	std::string nickString;
	sf::Font font;
	sf::RectangleShape heartS;
	sf::Texture heartT;
	std::vector<sf::RectangleShape>life;
	sf::FloatRect nickRect, czasRect, helpRect, escRect;
	sf::Vector2f nickPos, czasPos, heartPos;
	//obsluga zegara
	sf::Clock clock;
	sf::Time time;
	float czasF;						//czas wyswietlany na ekranie
	float currentTime = 0.f;					//czas zapisywany w wypadku zatrzymania rozgrywki


//pomoc i esc
	SegmentGUI* segmentGUI;													//wskaznik na segment ktory nalezy wyswietlic
	unsigned int visibleSegment;											//zmienna definujaca ktory segment interfejsu powinien byc teraz obs³ugiwany
	sf::Vector2f viewPos = sf::Vector2f(0.f, 0.f);							//pozycja widoku
																			
	//ekran po zakonczeniu rozgrywki
	bool isGamePlayed;										//czy rozgrywka siê ju¿ zakoñczy³a?
	bool isPaused;										//czy wstrzymac rozgrywkê?
	bool endSettingsDone;								//flaga na potrzeby funkcji gameWon() i gameLost(), aby instrukcje nie wykonywa³y siê w pêtli co skutkuje crash'em programu
	bool isF1pressed = false;
};

