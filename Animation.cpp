#include "Animation.h"


Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;								  //inicjacja prywatnej zmiennej o nazwie imageCount, bêd¹cej instancj¹ tej klasy bezpoœrednio z parametru funkcji o tej samej nazwie
	this->switchTime = switchTime;								  // --||-- 
	totalTime = 0.0f;											  //wartosc poczatkowa czasu jaki minal od ostatniej animacji
	currentImage.x = 0;											  //poczatkowa klatka(pierwsza od lewej, dlatego x, a 0 bo vs indexuje od 0
	nextImage.x = 1;

	uvRect.width = texture->getSize().x / (float)(imageCount.x);  // ustawiamy szerokosc danego obrazu obliczajac ja dzielac szerokosc calej tekstuy(tabeli) na ilosc pingwinow w rzedzie(x) zmieniona na float zeby warningi nie wkurwialy
	uvRect.height = texture->getSize().y / (float)(imageCount.y); // ustawiamy wysokosc danego obrazu obliczajac ja dzielac wysokosc calej tekstuy(tabeli) na ilosc pingwinow w kolumnie(y) zmieniona na float zeby warningi nie wkurwialy
	next_uvRect.width = texture->getSize().x / (float)(imageCount.x); //dla nastepnej klatki
	next_uvRect.height = texture->getSize().y / (float)(imageCount.y); //dla nastepnej klatki
}

Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime, bool czyWprawo)
{
	currentImage.y = row;										 //przypisujemy, na ktorym rzedzie obecnie znajduje sie aktualna klatka animacji 
	nextImage.y = row;
	totalTime += deltaTime;										 //do czasu ogolnego dodajemy oststnia zmiane klatki

	if (totalTime >= switchTime)								 //jesli czas od ostatniej animacji jest wiekszy/rowny czasowi jaki chcemy zeby byl to tutaj zwalniamy tempo zeby chociaz animacje z opoznieniem sie wyswietlaly
	{
		totalTime -= switchTime;
		currentImage.x++;										// zmiana kolumny z windsurferem na nastepna( w lewo)
		nextImage.x++;

		if (currentImage.x >= imageCount.x)						//jezeli jestesmy juz przy ostatniej animacji w rzedzie(3)
			currentImage.x = 0;									//zmien spowrotem na pierwszego z lewej(index od 0)
		if (nextImage.x >= imageCount.x)
			nextImage.x = 0;
	
	}

	uvRect.top = currentImage.y * uvRect.height;				//
	next_uvRect.top = nextImage.y * next_uvRect.height;

	if (czyWprawo)													// jesli patzy w prawo, przejdz tylko do nastepnego prostokata
	{
		uvRect.left = currentImage.x * uvRect.width;				//offset ustawiamy na lewy gorny rog danego prostokata 
		uvRect.width = abs(uvRect.width);							//jezeli w prawo to zawsze ma byc dodatnia, a mozliwe ze chwile wczesniej bylismy skierowani w lewo(odkrecamy po prostu spowrotem)
	}
	else															//jesli juz nie patrzy w prawo, musimy zrobic lustrzane odbicie animacji zmieniajac offset na ujemny
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);		//ustawiamy offset w prawym gornym rogu prostokata z pingwinem, nie lewym; dajemy absolutna w szerokosci bo moze byc ujemna badz nie, a nie chcemu mnozyc przez minus tu
		uvRect.width = -abs(uvRect.width);							//zmieniamy wartosc absolutna szerokosci na ujemna zeby nam go obrocilo lustrzanie
	}
	//nastepna klatka
	next_uvRect.left = nextImage.x * next_uvRect.width;				//offset ustawiamy na lewy gorny rog danego prostokata
}
