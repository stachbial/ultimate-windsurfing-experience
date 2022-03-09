
#include "BackGround.h"

BackGround::BackGround(sf::RenderWindow& window, sf::Vector2u imageCount, float switchTime, int render)
{
	this->render = render;
	this->window = &window;
	if (!wodaT.loadFromFile("resources\\ocean1.1.png"))
		return;
	wodaT.setSmooth(true);
	
	if (!nieboT.loadFromFile("resources\\niebo.png")) 
	return;

	wodaX =  window.getSize().x;
	wodaY = 0.665 * window.getSize().y;
	niebo.setPosition(0.f, 0.f);
	niebo.setTexture(nieboT);

	animacjaWody = new Animation(&wodaT, imageCount, switchTime);
	
	
	for (int i = 0; i < render; i++)
	{
		sf::RectangleShape n;
		n.setSize(sf::Vector2f(wodaX, wodaY));
		n.setPosition(i*window.getSize().x, window.getSize().y * 0.335f);
		n.setTexture(&wodaT);
		wodaS.push_back(n);
		
	}
	
}
BackGround::~BackGround(){}

void BackGround::BGupdate(sf::View& view, float deltaTime)
{
	 
	animacjaWody->Update(0, deltaTime, true);
	w1PosLeft = wodaS.at(0).getPosition().x;
	vPos = view.getCenter().x;
	if (vPos - w1PosLeft >= 1.5f*window->getSize().x)						//jesli pierwszy sprite wody znajduje sie poza zasiegiem widoku kamery
	{
		sf::RectangleShape n;
		n.setSize(sf::Vector2f(wodaX, wodaY));
		n.setPosition((wodaS.at(1).getPosition().x) + window->getSize().x, wodaS.at(1).getPosition().y);
		n.setTexture(&wodaT);
		wodaS.push_back(n);
		wodaS.erase(wodaS.begin());
	}
		wodaS.at(0).setTextureRect(animacjaWody->uvRect);
		wodaS.at(1).setTextureRect(animacjaWody->next_uvRect);
}

void BackGround::draw(sf::RenderWindow& window) 
{
	window.draw(niebo);
	for (int i = 0; i < render; i++) 
	{
		window.draw(wodaS.at(i));
	}
}

