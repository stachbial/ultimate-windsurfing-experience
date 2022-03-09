#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <vector>

class BackGround
{
public:
	BackGround(sf::RenderWindow& window, sf::Vector2u imageCount, float switchTime, int render);
	~BackGround();

	void BGupdate(sf::View& view, float deltaTime);							//funkcja dodaj�ca i odejmuj�ca obiekty z wektora wodaS oraz aktualizuj�ca animacje w czasie
	void draw(sf::RenderWindow& window);									//rysuj wektor wodaS w oknie

private:
	std::vector<sf::RectangleShape>wodaS;									//wektor zawierajacy prostokaty z tekstura wody
	float wodaX, wodaY;														//wymiary pojedynczego prostokatu z tekstura wody
	Animation* animacjaWody;												//animacja tekstury wody
	float w1PosLeft;														//pozycja aktualnie pierwszego X elementu wody w wektore wodaS
	float vPos;																//pozycja X �rodka widoku view

	sf::Sprite niebo;														//sprite nieba(t�a)
	sf::Texture wodaT;														//tekstura wody
	sf::Texture nieboT;														//tekstura nieba
	
	int render;																//ilo�� renderowanych w danej chwilii obiektow woda(prostok�t�w)
	sf::RenderWindow* window;												//wskaznik na okno, aby nie musiec dodawa� go wsz�dzie w kontruktorach funkcji, kt�re go potrzebuj�
};

