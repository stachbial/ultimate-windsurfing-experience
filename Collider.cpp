#include "Collider.h"

Collider::Collider(sf::RectangleShape& body, sf::RectangleShape& textureBody) :
	body(body), textureBody(textureBody)
{}
Collider::~Collider()
{

}
bool Collider::checkCollision(Collider& other, float push)			//funkcja sprawdzajaca czy nastapila kolizja i odpychajaca obiekty jesli tak sie stalo
{
	sf::Vector2f otherPosition = other.GetBodyPosition();				//pobieramy pozycje innego(other) obiektu
	sf::Vector2f otherHalfSize = other.GetHalfSize();				//polowa przekatnej innego (other)obiektu
	sf::Vector2f thisPosition = GetBodyPosition();						//pobieramy pozycje naszego obiektu(this)
	sf::Vector2f thisHalfSize = GetHalfSize();		 				//polowa przekatniej naszego obiektu(this)

	float deltaX = otherPosition.x - thisPosition.x;				//odleglosc pomiedzy srodkami obu obiektow w osi x
	float deltaY = otherPosition.y - thisPosition.y;				//odleglosc pomiedzy srodkami obu obiektow w osi y

	float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x); //(intersect=skrzyzowac) obliczamy czy w osi x odleglosc pomiedzy srodkami obiektow jest mniejsza niz suma ich przekatnych ; roznica pomiedzy delta a suma skladowych x polowek przek¹tnych ( jesli kolizja == wartosc jest ujemna)
	float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y); //obliczamy czy w osi y odleglosc pomiedzy srodkami obiektow jest mniejsza niz suma skladowych ioch przekatnych w y; jesli nastêpuje kolizja == wartosæ ujemna

	if (intersectX < 0.0f && intersectY < 0.0f)						//jezeli odleglosc(zarowno w osi x i y) œrodków obu obiektów jest mniejsza od 0 (nachodza na siebie)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);				// "clamping"- ustawiamy wartosc maksymalna zmiennej push na <0.0f, 1.0f>, sama zmienna push to wpolczynnik z jakim maja sie odpychac przedmioty po kolizji

		if (intersectX > intersectY)								//jesli obiekty nachodz¹ na siebie bardziej w osi x nix y; skoro nastepuje kolizja to te zmienne maja wartosc ujemna
		{
			if (deltaX > 0.f)										//jesli deltaX pomiedzy obiektami jest ujemna			
			{
				Move((intersectX * (1.0 - push)), 0.0f);				//porusz obiekt body w strone przeciwna do delty o wartosc nachodzenia na siebie w tej osi pomnozona przez wspolczynnik opychania push
				other.Move((-intersectX+100.f), 0.0f);				//porusz inny obiekt w strone przeciwna do obiektu body(-intersect)
			}
			else													//jesli delta x jest dodatnia
			{
				Move((-intersectX * (1.0 - push)), 0.0f);				//porusz obiekt body w strone przeciwna do delty (-intersect)
				other.Move((intersectX-100.f), 0.0f);				//porusz inny obiekt w strone przeciwna do obiektu body

			}
		}
		else														//jesli obiekty nachodz¹ na siebie bardziej w osi y nix x; skoro nastepuje kolizja to te zmienne maja wartosc ujemna
		{
			if (deltaY > 0.f)										//jesli deltaX pomiedzy obiektami jest ujemna			
			{
				Move(0.0f, (intersectY * (1.0 - push)));				//porusz obiekt body w strone przeciwna do delty
				other.Move(0.0f, (-intersectY+100.f));				//porusz inny obiekt w strone przeciwna do obiektu body(-intersect)
			}
			else													//jesli delta x jest dodatnia
			{
				Move(0.0f, (-intersectY * (1.0 - push)));				//porusz obiekt body w strone przeciwna do delty (-intersect)
				other.Move(0.0f, (intersectY-100.f));				//porusz inny obiekt w strone przeciwna do obiektu body

			}
		}

		return true;												//obiekty koliduja ze soba i nalezy zwrocic true
	}

	return false;
}


