#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"


class Enemy
{
public:
	sf::Vector2f texSize;									//rozmiar prostok¹tu z textur¹ obiektu, inicjowana przez programiste
	sf::Vector2f bodySize;									//rozmiar rzeczywistego cia³a dla którego sprawdzana bêdzie kolizja (musi byæ mniejsze ze wzglêdu na puste miejsca textury)/ obliczana na podstawie texSize
	sf::Vector2f position;									//pozycja obiektu 
	sf::Vector2f windowHeightPoints;						//górna i dolna granica planszy: X = górna, Y = dolna
	float windowWidth;										//szerokosc planszy

	sf::RectangleShape body;								//cia³o obiektu dla którego sprawdzana bêdzie kolizja
	sf::RectangleShape textureBody;							//prostok¹t pe³ni¹cy funkcje "naczynia" na texture obiektu

	Animation animation;									//animacja textury obiektu
	bool isHit = false;

	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f texSize, sf::RenderWindow* window);
	Collider GetCollider() { return Collider(body, textureBody); }//zwraca obszar (czesc body) dla któego sprawdzana bedzie kolizja
	void Update();
	void Draw(sf::RenderWindow& window);
	bool gotHit() { return isHit; }
};

