#pragma once
#include <SFML/Graphics.hpp>

/*
Uproszczony schemat dzialania animacji:

dzia³amy na jednym pliku png zlozonym z wszystkich mozliwych klatek w ktorych dany obiekt(postac) bedzie sie znajdowac,
uporz¹tkowanych w formie tabeli (kolumny oraz wiersze w równych odstêpach od siebie)
ka¿dy rz¹d w pliku bedzie zawiera³ zestaw klatek( sk³adowych animacji) bedacy wywolywany w odpowiednich okolicznosciach
innymi slowy rzad = kategoria np rzad 1 - postac w bez ruchu, rzad 2 postac idaca w prawo itd

podajac ilosc kolumn i ilosc rzedow(wierszy) uzyskujemy ilosc klatek jakimi mozemy dysponowac w danej teksturze(ilosc komórek w tabeli)
tworzymy wyimaginowany prostokat "uvRect" wielkosci jednej klatki(jednej komorki w tabeli) i ustawiamy na pierwsza klatke,
jesli nast¹pi po¿¹dana zmiana w czasie "przeskakujemy" tym prostok¹tem na nastepn¹ klatke(komórkê) w danym wierszu,
dzieki czemu postac bedzie sprawiala wrazenie jakby zmienila ulozenie

Zmiany poszczególnych kolumn w danym wierszu bêd¹ sterowane zmienn¹ przechowuj¹c¹ czas,
po up³ywie którego nale¿y przesun¹æ nasz prostok¹t na nastêpn¹ kolumnê, jesli dotrze do ostatniej
- ustawiamy go spowrotem na pierwsza kolumne

zmiany rzêdow beda wywolywane przez zewnetrzne funkje np funkcje ruchu obiektu gracz, jesli porusza sie w lewo,
przeskakujemy prostok¹tem uvRECT na pierwsz¹ kolumnê rzêdu w którym znajdujê siê zestaw odpowiednich animacji pokazujacych
gracza poruszajacego sie w tym kierunku i skaczemy po odpowiednich komorkach w danym rzêzie tak d³ugo,
jak dany warunek jest spe³niany

wszystkie animacje sa domyslnie zwrocone w jedna strone- nie ma oddzielnych rzedow na poruszanie sie w lewo
i na poruszanie w prawo - to strata czasu, pracy i miejsca w pamiêci, tak wiec animacja ruchu,
pomimo ¿e przyk³adowo porusza³a by nogami postaci nie bêdzie zwrócona w odpowiedni¹ stronê,
dlatego ustawiamy zmienna czyWprawo typu bool, która bedzie przechowywala informacje ,
w ktora strone jest zwrocona postaæ, jeœli tektura ma domyslnie tylko klatki postaci zwroconej
w prawo a poruszymy siê w lewo wystarczy wyœwietlic jej lustrzane odbicie

*/

class Animation																	//klasa odpowiedzialna za animacje windsrfera kiedy stoi w miejscu(dryfowanie, mruganie) czyli 3 animacje w 1 rzedzie w kolejnosci: 1->2->3->1->2->3->itd
{
public:																		    // funkcje publiczne
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); //1.wskaznik na wczytana wczesniej texture(w konstruktorze danego obiektu), 2 ilosc tekstur(dzielimy macierzysta teksture na ilosc kolumn w rzedzie x i wierszy w y), 3 czas pomiedzy zmianami klatek w danej animacji
	~Animation();

	void Update(int row, float deltaTime, bool czyWprawo);						//row - ktory rzad chcemy wybrac, deltaTime przechowuje czas pomiedzy poprzednia KLATK¥ a aktualn¹(ile to zajelo)- oduzaleznienie od hardwaru,ktrory w zaleznosci od tego czy jest dobry, bazujac na sekundach moglby duzo dluzej przeprowadzac dana animacje w porownaniu do operowania na klatkach

public:																			//zmienne publiczne
	sf::IntRect uvRect;															// zmienna przechowujaca wymiary obszaru tekstury(prostokat z odpowiedni¹ klatka surfera)bedacej czescia textury macierzystej
	sf::IntRect next_uvRect;														//zmienna przechowuj¹ca nastêpn¹ klatkê( na potrzebe np. jednoczesnego wyswietlania dwoch sprite'ow wody obok siebie, z czym ze jeden bêdzie wygl¹da³ nanastêpstwo drugiego)
private:																		//zmienne prywatne
	sf::Vector2u imageCount;													//zmienna unsigned_int(bo nie moze byc zerowa) zawierajaca ilosc klatek danej animacji, jesli nasz macierzysty plik tekstury sklada sie z 3 kolumn i 4 rzedow, ilosc kolumn to zmienna x a rzedow y(w ten sposob dzielimy rowno macierzysta teksture i uzyskujemy ilosc klatek(zakladajac ze tekstura ma regularna budowe)
	sf::Vector2u currentImage;													//zmienna przechowujaca polozenie obecnej textury(klatki) wg podzialu na komorki; x-kolumna,y-rzad; inkrementujac cala jednostke przechodzimy jedna komorke w prawo i jedna w dol czyli zmieniamy obrazek
	sf::Vector2u nextImage;

	float totalTime;															//czas od ostatniej zmiany animacji
	float switchTime;															// czas ktory ma minac pomiedzy zmiana poszczegolnej animacji

};

