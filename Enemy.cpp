#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f texSize, sf::RenderWindow* window)
	:animation(texture, imageCount, switchTime), position(position), texSize(texSize)
{
	windowHeightPoints.x = window->getSize().y - 70.f;				//dolna granica (70 to polowa dlugosci enemy zeby merzylo dla jego krancow a nie originu(srodka))
	windowHeightPoints.y = (window->getSize().y * 0.335f) + 90.f;	//gorna granica
	windowWidth = window->getSize().x;

	bodySize.x = 2.f * texSize.x / 3.f; //cia³o dla którego bedzie sprawdzana kolizja bêdzie minimalnie mniejsze od textury( zeby nie sprawdzac kolizji dla pustego pola)
	bodySize.y = 4.f * texSize.y / 5.f;

	textureBody.setPosition(position);
	textureBody.setSize(texSize);
	textureBody.setOrigin(texSize.x / 2, texSize.y / 2);
	body.setPosition(position);
	body.setSize(bodySize);
	body.setOrigin(bodySize.x / 2, bodySize.y / 2);
}

void Enemy::Update()
{}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(textureBody);
}

