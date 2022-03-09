#include "Player.h"
#include"Collider.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerPos, unsigned int playerHp) : //konstruktor
	animation(texture, imageCount, switchTime)									//torzymy obiekt animacje zeby moc go uzyc w ponizszej funkcji przyjmuj¹cy parametry pocz¹tkowe bezpoœrednio z konstruktora klasy player
{
	this->speed = speed;														//zapodajemy zimenna speed do parametru funkcji, uzywamy speed po jest to instancja tej wlasnie klasy
	row = 0;																	//ustawiamy wartosc poczatkowa animacji na pierwszy rzad -> w nim znajduje sie animacja dryfowania czyli "w bezruchu" - wyswietlana gdy obiekt nie porusza sie
	czyWprawo = true;															//moja textura gracza jest domyslnie zwrocona w lewo, wieæ ¿eby by³a ustawiona w prawo, "czyWLEWO" musi miec wartosc poczatkowa falsz
	hp = playerHp;

	body.setSize(sf::Vector2f(124.94f, 31.5f));									//tworzymy prostok¹t, dla którego bêdziemy sprawdzaæ kolizjê
	body.setOrigin(body.getSize() / 2.0f);										//ustawiamy origin na srodek obiektu czyli polowa wysokosci i szerokosci
	body.setPosition(playerPos.x + 15.75f, playerPos.y + 79.8f);											//ustawiamy pozycje materialnego ciala gracza tak, aby obejmowala deskê i nogi znajduj¹ce siê na animacji

	textureBody.setSize(sf::Vector2f(168.0f, 200.0f));							//(wymiar)ustawiamy parametry cia³a gracza czyli prostokatu obiektu gracz
	textureBody.setOrigin(textureBody.getSize() / 2.0f);						//ustawiamy origin na srodek obiektu czyli polowa wysokosci i szerokosci
	textureBody.setPosition(playerPos);									//pozycja poczatkowa gracza
	textureBody.setTexture(texture);											//ustaw tekture prostokata body gracza

	harm = false;
}

Player::~Player()																//dekonstruktor
{}

void Player::Update(float deltaTime, sf::View& view, sf::RenderWindow& window, float MapUpperBorder, float stopViewMove, bool isHELPscreen)											//funkcja odpowiedzialna za zmiane klatki w ruchu i ruch sam w sobie
{
	sf::Vector2f movement(0.0f, 0.0f);											//ustaw domyslna wartosc movement na 0
//obsluga ruchu
	if (!isHELPscreen)//jesli rozgrywka nie jest wstrzymana
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))							//jezeli wcisnieto a
			movement.x -= speed * deltaTime;										//zapodaj do zmiennej movement w osi x ujemna wartosc (zeby patrzyl w lewo)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))							//jesli d wcisniete
			movement.x += speed * deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))							//jezeli wcisnieto a
			movement.y -= speed * deltaTime;										//zapodaj do zmiennej movement w osi x ujemna wartosc (zeby patrzyl w lewo)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))							//jesli d wcisniete
			movement.y += speed * deltaTime;										//zapodaj dodatnia wartosc (zeby patrzyl w lewo)
	}
//obsluga animacji
	if (harm == true)															//jeœli otrzymano obra¿enia
	{
		row = 3;																//wyœwietlaj rz¹d z animacj¹ obra¿eñ
		speed = 80.f;															//zmniejsz prêdkoœæ gracza do 80.f
		harmTime += deltaTime;													//do zmiennej przechowujacej calkowity czas od inicjacji obrazen dodawaj dlugosci nastepnych klatek
		if (harmTime >= 3.9f)													//jesli calkowity czas od momentu otrzymania obrazen jest mniejszy niz 3.9
		{
			speed = 180.f;														//przywróæ prêdkoœæ gracza
			harmTime = 0.f;													//zeruj calkowity czas od otrzymania obrazen
			harm = false;														//zeruj informacje o zadanych obrazeniach
		}
	}
	else																		//jesli nie otrzymano obrazeñ
	{
		if (movement.y == 0.0f)													//jesli nie odnotowano ruchu
		{
			row = 0;															//ustaw na rzad w ktorym jest animacja "idle" -> stojaca w miejsu
		}
		else
		{
			if (movement.y < 0.0f)												//jesli zmienna movement w osi y dodatnia
				row = 1;														//ustaw na rz¹d z animacja ukazuj¹c¹ ruch w do³ ekranu(zgodnie z osia y)
			else
				row = 2;														//ustaw na rz¹d z animacj¹ odpowiedzialn¹ za ruch w góre ekranu(przeciwnie do osi y)
		}
		if (movement.x == 0.0f) {}												//puste miejsce, poniewaz zmiana kierunku animacji postaci ma nastapic dopiero po zmianie w ruchu(jezeli dalbym tylko ifa ponizej, odwracalby moja postac w lewo gdy tylko movement.x przestanie byc>0, a tak postac zostaje zwrocona w ta strone w ktora wykona³a ostatni ruch)
		else
		{
			if (movement.x > 0.0f)												//jesli gracz porusza sie zgdnie z osia x (w kierunku dodatnim czyli prawo)
				czyWprawo = true;												//ustaw wartosc czyWLEWO na falsz zeby obrocic go w prawo
			else																// jesli porusza sie przeciwnie do osi x czyli w lewo
				czyWprawo = false;												//ustaw go tak, by byl skierowany w lewo
		}
	}
	if (textureBody.getPosition().x <= view.getCenter().x - (window.getSize().x/2) + 80.f && movement.x < 0)//lewa granica ekranu
	{
		movement.x = 0;
	}
	if (textureBody.getPosition().y >= window.getSize().y  -100.f && movement.y > 0)//dolna granica ekranu
	{
		movement.y = 0;
	}
	if (textureBody.getPosition().y <= MapUpperBorder - 50.f && movement.y < 0)//dolna granica mapy
	{
		movement.y = 0;
	}
//uzupelnienie funkcji skladowych o wyzej ustalone parametry
	animation.Update(row, deltaTime, czyWprawo);								//aktualizuj animacje o odpowiednie parametry
	textureBody.setTextureRect(animation.uvRect);								//aktualizuj obszar wyswietlanej textury
	textureBody.move(movement);													//rusz cia³em zawierajacym texture gracza
	body.move(movement);														//rusz cia³em materialnym gracza
//obsluga ruchu kamer¹
	if(view.getCenter().x <= stopViewMove - ((view.getSize().x)/2.f))//jesli nie jest to koniec mapy
		if(movement.x >= 0.f && textureBody.getPosition().x >= view.getCenter().x)//jesli zawodnik znajduje siê na œrodku ekranu lub w prawo od niego
			view.move(movement.x, 0.f);//rusz kamera
}

void Player::Draw(sf::RenderWindow& window)										//funkcja rysujaca gracza w oknie, do ktorego wskaznik podajemy w parametrze
{
	window.draw(textureBody);
	//window.draw(body);
}

bool Player::isHurt(bool check)
{
	if (check == true)
	{	
		hp--;
		harm = true;
		return true;
	}
	else
	{
		return false;
	}
}
