#pragma once
#include <SFML/Graphics.hpp>


/*
uproszczony wzór mechanizmu dzia³ania detekcji zderzeñ AABB:

tworzymy collidery(ang. zderzak) dla kazdego obiektu dla ktorego chcemy wykryc zderzenie z innym (kazdy obiekt, który
wchodzi w interakcjê musi go mieæ, nie tylko jeden z nich)czyli wymimaginowane przestrzenie niewidoczne na ekranie, tworzone na podstawie dlugosci
po³owy przek¹tnych danego obiektu(ta polowa stanie sie cala przekatna danego collidera - bedzie on mial ksztalt kwadratu, b¹dŸ prostok¹ta)
jeœli dany collider bedzie nachodzi³ na siebie z colliderem innego obiektu, nastepuje zderzenie


innymi s³owy:
sprawdzamy czy bezwzwgledna odleglosæ pomiedzy œrodkami dwóch obiektów jest mniejsza
ni¿ suma po³owy ich przek¹tnych, jeœli tak -znaczy, ¿e obiekty nachodza na siebie(nastêpuje kolizja),
jeœli bezwzglêdna odlegloœæ(delta) jest wiêksza od sumy po³ówek przek¹tnych ka¿dego
z obiektów, nie nastêpuje kolizja

w wypadku kolizji odpychamy od siebie dane obiekty wzd³u¿ wektorow, w których na siebie nachodz¹,
to czy obiekty bêd¹ odpychane z tak¹ sam¹ si³¹, b¹dŸ jeden z nich bêdzie "trudniejszy" do przepchniêcia,
b¹dŸ jeden z nich w ógole bêdzie nieruchomy definiowaæ bêdziemy na podstawie zmiennej "push", która
bêdzie mia³a wartoœæ od 1 do 0, gdzie 0. oznacza, ¿e dany obiekt mo¿na przesun¹æ innym bez problemu,
a 1, ¿e jest on nie do ruszenia. po prostu bedziemy przez niego mnozyc dlugosc wektora o ktory mamy
przesunac obiekt koliduj¹cy

wywolanie detekcji zdarzen bedzie polegalo na sprawdzeniu z perspektywy innego obiektu niz postac naszego gracza,
czy jego wyimaginowany collider w chodzi w interakcje z colliderem gracza, oraz bedziemy podawac wartosc
push, dzieki czemu latwo bedzie ustalac czy dany obiekt jest "przepychalny" dla gracza i z jak¹ si³¹

obiekty to prostokaty / kwadraty - dlatego potrzeba polowy przek¹tnej ka¿dego z nich

bêdzie nam do tego potrzebny zarówno wymiar jak i origin(zawsze ustawiony na srodek obiektu) obu obiektow
chodzacych w interakcje
*/



class Collider
{
public:
																							//tego kontruktora bêdziemy u¿ywaæ dla obiektów, ktore bêdziemy chcieli przesun¹c w wniku kolizji- potrzebujemy te¿ cia³a textury, aby móc je przesun¹æ równolegle z tym materialnym, dla ktorego kolizja bêdzie sprawdzana                              //konstruktor bedzie zwracal nam wymiary ciala obiektu dla ktorego go wywolamy
	Collider(sf::RectangleShape& body, sf::RectangleShape& textureBody);								//konstruktor dla obiektow klasy enemy
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); textureBody.move(dx, dy); }//funkcja odsuwaj¹ca obiekty jesli zajdzie zderzenie

	bool checkCollision(Collider& other, float push);					//funkcja sprawdzajaca czy nastapila kolizja i odpychajaca dany obiekt (jesli push=0, odrzuci playera, jesli 1-inny obiekt, jesli 0.5-inny obiekt z "trudem")
	sf::Vector2f GetBodyPosition() { return body.getPosition(); }		//zwraca pozycje materialnego cia³a  gracza
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }		//zwraca polowe przekatnej body gracza czyli prostokata
	
	
	

private:
	sf::RectangleShape& body;											//wskaznik na cialo obiektu dla ktorego wywolujemy funkcje (prostokat obiektu)
	sf::RectangleShape& textureBody;									//adres zmiennej przechowuj¹cej prostok¹t z textur¹ obiektum który bedziemy chcieli przesun¹c za pomoc¹ check collision o dokladnie tyle co sam collider( cia³o dla ktorego sprawdzmy kolizje)
};

