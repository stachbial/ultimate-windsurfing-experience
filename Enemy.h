#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"


class Enemy
{
public:
	sf::Vector2f texSize;									//rozmiar prostok�tu z textur� obiektu, inicjowana przez programiste
	sf::Vector2f bodySize;									//rozmiar rzeczywistego cia�a dla kt�rego sprawdzana b�dzie kolizja (musi by� mniejsze ze wzgl�du na puste miejsca textury)/ obliczana na podstawie texSize
	sf::Vector2f position;									//pozycja obiektu 
	sf::Vector2f windowHeightPoints;						//g�rna i dolna granica planszy: X = g�rna, Y = dolna
	float windowWidth;										//szerokosc planszy

	sf::RectangleShape body;								//cia�o obiektu dla kt�rego sprawdzana b�dzie kolizja
	sf::RectangleShape textureBody;							//prostok�t pe�ni�cy funkcje "naczynia" na texture obiektu

	Animation animation;									//animacja textury obiektu
	bool isHit = false;

	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f texSize, sf::RenderWindow* window);
	Collider GetCollider() { return Collider(body, textureBody); }//zwraca obszar (czesc body) dla kt�ego sprawdzana bedzie kolizja
	void Update();
	void Draw(sf::RenderWindow& window);
	bool gotHit() { return isHit; }
};

