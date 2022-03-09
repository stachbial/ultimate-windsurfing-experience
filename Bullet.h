#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	sf::CircleShape body;											//cia³o - kula armatnia
	sf::Vector2f movement;											//ruch kuli armatniej
	float speed;													//predkosc kuli
	
	Bullet(float promien = 10.f);
};

