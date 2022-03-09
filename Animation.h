#pragma once
#include <SFML/Graphics.hpp>

/*
Uproszczony schemat dzialania animacji:

dzia�amy na jednym pliku png zlozonym z wszystkich mozliwych klatek w ktorych dany obiekt(postac) bedzie sie znajdowac,
uporz�tkowanych w formie tabeli (kolumny oraz wiersze w r�wnych odst�pach od siebie)
ka�dy rz�d w pliku bedzie zawiera� zestaw klatek( sk�adowych animacji) bedacy wywolywany w odpowiednich okolicznosciach
innymi slowy rzad = kategoria np rzad 1 - postac w bez ruchu, rzad 2 postac idaca w prawo itd

podajac ilosc kolumn i ilosc rzedow(wierszy) uzyskujemy ilosc klatek jakimi mozemy dysponowac w danej teksturze(ilosc kom�rek w tabeli)
tworzymy wyimaginowany prostokat "uvRect" wielkosci jednej klatki(jednej komorki w tabeli) i ustawiamy na pierwsza klatke,
jesli nast�pi po��dana zmiana w czasie "przeskakujemy" tym prostok�tem na nastepn� klatke(kom�rk�) w danym wierszu,
dzieki czemu postac bedzie sprawiala wrazenie jakby zmienila ulozenie

Zmiany poszczeg�lnych kolumn w danym wierszu b�d� sterowane zmienn� przechowuj�c� czas,
po up�ywie kt�rego nale�y przesun�� nasz prostok�t na nast�pn� kolumn�, jesli dotrze do ostatniej
- ustawiamy go spowrotem na pierwsza kolumne

zmiany rz�dow beda wywolywane przez zewnetrzne funkje np funkcje ruchu obiektu gracz, jesli porusza sie w lewo,
przeskakujemy prostok�tem uvRECT na pierwsz� kolumn� rz�du w kt�rym znajduj� si� zestaw odpowiednich animacji pokazujacych
gracza poruszajacego sie w tym kierunku i skaczemy po odpowiednich komorkach w danym rz�zie tak d�ugo,
jak dany warunek jest spe�niany

wszystkie animacje sa domyslnie zwrocone w jedna strone- nie ma oddzielnych rzedow na poruszanie sie w lewo
i na poruszanie w prawo - to strata czasu, pracy i miejsca w pami�ci, tak wiec animacja ruchu,
pomimo �e przyk�adowo porusza�a by nogami postaci nie b�dzie zwr�cona w odpowiedni� stron�,
dlatego ustawiamy zmienna czyWprawo typu bool, kt�ra bedzie przechowywala informacje ,
w ktora strone jest zwrocona posta�, je�li tektura ma domyslnie tylko klatki postaci zwroconej
w prawo a poruszymy si� w lewo wystarczy wy�wietlic jej lustrzane odbicie

*/

class Animation																	//klasa odpowiedzialna za animacje windsrfera kiedy stoi w miejscu(dryfowanie, mruganie) czyli 3 animacje w 1 rzedzie w kolejnosci: 1->2->3->1->2->3->itd
{
public:																		    // funkcje publiczne
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); //1.wskaznik na wczytana wczesniej texture(w konstruktorze danego obiektu), 2 ilosc tekstur(dzielimy macierzysta teksture na ilosc kolumn w rzedzie x i wierszy w y), 3 czas pomiedzy zmianami klatek w danej animacji
	~Animation();

	void Update(int row, float deltaTime, bool czyWprawo);						//row - ktory rzad chcemy wybrac, deltaTime przechowuje czas pomiedzy poprzednia KLATK� a aktualn�(ile to zajelo)- oduzaleznienie od hardwaru,ktrory w zaleznosci od tego czy jest dobry, bazujac na sekundach moglby duzo dluzej przeprowadzac dana animacje w porownaniu do operowania na klatkach

public:																			//zmienne publiczne
	sf::IntRect uvRect;															// zmienna przechowujaca wymiary obszaru tekstury(prostokat z odpowiedni� klatka surfera)bedacej czescia textury macierzystej
	sf::IntRect next_uvRect;														//zmienna przechowuj�ca nast�pn� klatk�( na potrzebe np. jednoczesnego wyswietlania dwoch sprite'ow wody obok siebie, z czym ze jeden b�dzie wygl�da� nanast�pstwo drugiego)
private:																		//zmienne prywatne
	sf::Vector2u imageCount;													//zmienna unsigned_int(bo nie moze byc zerowa) zawierajaca ilosc klatek danej animacji, jesli nasz macierzysty plik tekstury sklada sie z 3 kolumn i 4 rzedow, ilosc kolumn to zmienna x a rzedow y(w ten sposob dzielimy rowno macierzysta teksture i uzyskujemy ilosc klatek(zakladajac ze tekstura ma regularna budowe)
	sf::Vector2u currentImage;													//zmienna przechowujaca polozenie obecnej textury(klatki) wg podzialu na komorki; x-kolumna,y-rzad; inkrementujac cala jednostke przechodzimy jedna komorke w prawo i jedna w dol czyli zmieniamy obrazek
	sf::Vector2u nextImage;

	float totalTime;															//czas od ostatniej zmiany animacji
	float switchTime;															// czas ktory ma minac pomiedzy zmiana poszczegolnej animacji

};

