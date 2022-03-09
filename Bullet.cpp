#include "Bullet.h"

Bullet::Bullet(float promien)
	: movement(0.f, 0.f), speed(3.f)
{
	this->body.setRadius(promien);
	this->body.setFillColor(sf::Color::Black);
}
