#pragma once
#include <SFML/Graphics.hpp>


/*
uproszczony wz�r mechanizmu dzia�ania detekcji zderze� AABB:

tworzymy collidery(ang. zderzak) dla kazdego obiektu dla ktorego chcemy wykryc zderzenie z innym (kazdy obiekt, kt�ry
wchodzi w interakcj� musi go mie�, nie tylko jeden z nich)czyli wymimaginowane przestrzenie niewidoczne na ekranie, tworzone na podstawie dlugosci
po�owy przek�tnych danego obiektu(ta polowa stanie sie cala przekatna danego collidera - bedzie on mial ksztalt kwadratu, b�d� prostok�ta)
je�li dany collider bedzie nachodzi� na siebie z colliderem innego obiektu, nastepuje zderzenie


innymi s�owy:
sprawdzamy czy bezwzwgledna odleglos� pomiedzy �rodkami dw�ch obiekt�w jest mniejsza
ni� suma po�owy ich przek�tnych, je�li tak -znaczy, �e obiekty nachodza na siebie(nast�puje kolizja),
je�li bezwzgl�dna odleglo��(delta) jest wi�ksza od sumy po��wek przek�tnych ka�dego
z obiekt�w, nie nast�puje kolizja

w wypadku kolizji odpychamy od siebie dane obiekty wzd�u� wektorow, w kt�rych na siebie nachodz�,
to czy obiekty b�d� odpychane z tak� sam� si��, b�d� jeden z nich b�dzie "trudniejszy" do przepchni�cia,
b�d� jeden z nich w �gole b�dzie nieruchomy definiowa� b�dziemy na podstawie zmiennej "push", kt�ra
b�dzie mia�a warto�� od 1 do 0, gdzie 0. oznacza, �e dany obiekt mo�na przesun�� innym bez problemu,
a 1, �e jest on nie do ruszenia. po prostu bedziemy przez niego mnozyc dlugosc wektora o ktory mamy
przesunac obiekt koliduj�cy

wywolanie detekcji zdarzen bedzie polegalo na sprawdzeniu z perspektywy innego obiektu niz postac naszego gracza,
czy jego wyimaginowany collider w chodzi w interakcje z colliderem gracza, oraz bedziemy podawac wartosc
push, dzieki czemu latwo bedzie ustalac czy dany obiekt jest "przepychalny" dla gracza i z jak� si��

obiekty to prostokaty / kwadraty - dlatego potrzeba polowy przek�tnej ka�dego z nich

b�dzie nam do tego potrzebny zar�wno wymiar jak i origin(zawsze ustawiony na srodek obiektu) obu obiektow
chodzacych w interakcje
*/



class Collider
{
public:
																							//tego kontruktora b�dziemy u�ywa� dla obiekt�w, ktore b�dziemy chcieli przesun�c w wniku kolizji- potrzebujemy te� cia�a textury, aby m�c je przesun�� r�wnolegle z tym materialnym, dla ktorego kolizja b�dzie sprawdzana                              //konstruktor bedzie zwracal nam wymiary ciala obiektu dla ktorego go wywolamy
	Collider(sf::RectangleShape& body, sf::RectangleShape& textureBody);								//konstruktor dla obiektow klasy enemy
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); textureBody.move(dx, dy); }//funkcja odsuwaj�ca obiekty jesli zajdzie zderzenie

	bool checkCollision(Collider& other, float push);					//funkcja sprawdzajaca czy nastapila kolizja i odpychajaca dany obiekt (jesli push=0, odrzuci playera, jesli 1-inny obiekt, jesli 0.5-inny obiekt z "trudem")
	sf::Vector2f GetBodyPosition() { return body.getPosition(); }		//zwraca pozycje materialnego cia�a  gracza
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }		//zwraca polowe przekatnej body gracza czyli prostokata
	
	
	

private:
	sf::RectangleShape& body;											//wskaznik na cialo obiektu dla ktorego wywolujemy funkcje (prostokat obiektu)
	sf::RectangleShape& textureBody;									//adres zmiennej przechowuj�cej prostok�t z textur� obiektum kt�ry bedziemy chcieli przesun�c za pomoc� check collision o dokladnie tyle co sam collider( cia�o dla ktorego sprawdzmy kolizje)
};

