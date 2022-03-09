#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"


/*
klasa player bedzie odpowiedzialna zarowno za zmiane animacji gracza jak i jego ruch

animacja gracza bedzie korzystala z jednego pliku png, w ktorym znajdowac sie beda wszystkie klatki,
w jakich postac gracza bedzie wystepowac w formie tabeli 3kol x 4wiersze(row):
	1-szy wiersz - animacja statyczna(dryfowanie) - kiedy gracz bedzie stal w miejscu badz poruszal sie tylko w osi x
	2-gi wiersz - aniacja kiedy gracz bedzie poruszal sie w d�l ekranu( zgodnie z osia y)- �agiel pochylony do rufy deski
	3-ci wiersz - animacja wywolywana kiedy gracz bedzie poruszal sie w g�re ekranu (przeciwnie do osi y) - zagiel pochylony do dziobu deski
	4-ty wiersz - animacja wywolywana przy otrzymaniu obra�e� przez gracza

ka�dy wiersz sk�ada si� z trzech skladowych klatek animacji(kolumn), tak wi�c zale�nie od okoliczno�ci,
w jakich znajdzie sie gracz zmieniany b�dzie rz�d z kategori� a kolumny b�da zmieniane w czasie w obr�bie danego rz�du

obra�enia gracza - odpowiednia animacja oraz odjecie punktow hp- beda inicjowane przez detekcje kolizji
z takimi obiektami jak rekin, statek piracki, kula armatnia
*/

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerPos, unsigned int playerHp);
	~Player();

	void Update(float deltaTime, sf::View& view, sf::RenderWindow& window, float MapUpperBorder, float stopViewMove, bool isHELPscreen);										// funkcja odpowiedzialna za ruch obiektu gracz oraz animacje z nim zwiazane; nie wsadzamy tu zmiennej row bo ja bedziemy zmieniac na podstawie naciskanych klawiszy(kierunku i rodzaju ruchu gracza)
	void Draw(sf::RenderWindow& window);								//funkcja dzieki ktorej rysowanie obiektu gracz bedzie zcescia jego klasy i dzieki ktorej "body" moze byc prywatn� zmienn�

	sf::Vector2f GetPosition() { return body.getPosition(); }	//funkcja zwracajaca pozycje gracza, by moc ja wykorzystac np. do widoku
	sf::FloatRect GetbodyGbounds() { return body.getGlobalBounds(); }

	Collider GetCollider() { return Collider(body, textureBody); }		//pozyskujemy obiekt klasy collider dla ciala playera czyli body
	int getHP() { return hp; }

	bool isHurt(bool check); 
	

private:																
	sf::RectangleShape body;											//prostok�t postaci gracza- "materialne cia�o, dla kt�rego b�dziemy sprawdzac kolizj�(b�dzie ono obejmowa�o jedynie przestrzen gdzie znajduje si� animowana deska oraz cz�c nog, gdy� niepo��dane jest wykrywanie zderzenia dla np. zagla , b�d� pustej przestrzeni obok niego, b�d�cej cz�ci� obiektu textureBody
	sf::RectangleShape textureBody;										//prostokat postaci gracza, na powierzchni kt�rego wy�wietlana b�dzie animowana textura
	Animation animation;												//obiekt o nazwie animacja klasy animacja b�d�cy cz�sci� ca�ego obiektu player
	unsigned int row;													//ktory wiersz(kategoria) z klatkami w pliku macierzystym, unsigned zeby nigdy nie byl mniejszy niz zero
	float speed;														//zmienna przechowujaca informacje z jaka predkoscia nasza postac bedzie sie poruszac-
	bool czyWprawo;														//zmienna przechowujaca informacje czy postac zwrocona jest twarza w praw� strone ekranu
	int hp;													//health points-zmienna przechowuj�ca poziom �ycia gracza w punktach
	bool harm;															//zmienna przechowuj�ca informacje czy otrzymano obrazenia
	float harmTime=0;													//zmienna pomocnicza do przechowywania sumy czasu uplywu klatek 
};

