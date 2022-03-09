#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <vector>

class BackGround
{
public:
	BackGround(sf::RenderWindow& window, sf::Vector2u imageCount, float switchTime, int render);
	~BackGround();

	void BGupdate(sf::View& view, float deltaTime);							//funkcja dodaj¹ca i odejmuj¹ca obiekty z wektora wodaS oraz aktualizuj¹ca animacje w czasie
	void draw(sf::RenderWindow& window);									//rysuj wektor wodaS w oknie

private:
	std::vector<sf::RectangleShape>wodaS;									//wektor zawierajacy prostokaty z tekstura wody
	float wodaX, wodaY;														//wymiary pojedynczego prostokatu z tekstura wody
	Animation* animacjaWody;												//animacja tekstury wody
	float w1PosLeft;														//pozycja aktualnie pierwszego X elementu wody w wektore wodaS
	float vPos;																//pozycja X œrodka widoku view

	sf::Sprite niebo;														//sprite nieba(t³a)
	sf::Texture wodaT;														//tekstura wody
	sf::Texture nieboT;														//tekstura nieba
	
	int render;																//iloœæ renderowanych w danej chwilii obiektow woda(prostok¹tów)
	sf::RenderWindow* window;												//wskaznik na okno, aby nie musiec dodawaæ go wszêdzie w kontruktorach funkcji, które go potrzebuj¹
};

