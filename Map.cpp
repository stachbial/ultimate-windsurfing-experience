#include "Map.h"

//yxszjklqp

Map::Map(unsigned int poziomT, sf::RenderWindow& window)
{
	srand(time(NULL));
	this->window = &window;
	pomoczaY = 0;
	drawEnd = false;
//inicjacja textur
	if(!sharkTexture.loadFromFile("resources\\shark.png"))
		return;

	if (!shipTexture.loadFromFile("resources\\ship.png"))
		return;

	
	if (!endingMap.loadFromFile("resources\\plaza.png"))
		return;

	mapend.setSize(sf::Vector2f(455.f, 845.f));
	mapend.setTexture(&endingMap);
	mapend.setOrigin(0.f, mapend.getSize().y);
	


//inicjacja wytycznych potrzebnych do stworzenia mapy na podstawie wybranego poziomu trudnoœci
	switch (poziomT)
	{
	case 1:
		//hard
		enemyCount = 2;				//co tyle rzêdów  stawiaj przeciwnika
		placeShip = 40;				//co tyle ma byæ to statek
		break;		
	default:
		//after,easy
		enemyCount = 6;
		placeShip = 40; 
		break;
	}

// tworzenie dwuwymiarowej tablicy struktór sk³adaj¹cych siê z kafelków 100.f x 100.f oraz wytycznych dotyczacych tworzenia przeciwnikow
	tileMap = new tile* [mapSizeY];
	for (int y = 0; y < mapSizeY; y++)
	{
		tileMap[y] = new tile[mapSizeX];
		for (int x = 0; x < mapSizeX; x++)
		{
			
			tileMap[y][x].tilePos = sf::Vector2f(x * tileSizeF, (window.getSize().y * 0.355f) +  y* tileSizeF);
			tileMap[y][x].tile.setSize(sf::Vector2f(tileSizeF, tileSizeF));
			tileMap[y][x].tile.setPosition(tileMap[y][x].tilePos);
			   
			if (x % enemyCount == 0 && pomoczaY == y ) //warunek postawienia rekina
			{
				if (x > 4)
				{
					tileMap[y][x].placeEnemy = true;
					tileMap[y][x].isPlaced = false;
					tileMap[y][x].isShark = true;
				}
				
			}else if (x % placeShip == 0 && x < mapSizeX-1 && pomoczaY == y) //warunek postawienia statku
			{
				tileMap[y][x].placeEnemy = true;
				tileMap[y][x].isPlaced = false;
				tileMap[y][x].isShark = false;
			}
			else //jesli nic nie stawiac
			{
				//inicjacja zmiennych struktury (wszystkie = false)
				tileMap[y][x].placeEnemy = false;
				tileMap[y][x].isPlaced = false;
				tileMap[y][x].isShark = false;
			}
			pomoczaY++;
			if (pomoczaY >= 5)
				pomoczaY = 0;
		}
	}
	gameEndX = tileMap[0][mapSizeX-1].tilePos.x + 300.f; //inicjacja zmiennej, na ktorej nalezy rysowac "mapend"
	mapend.setPosition(sf::Vector2f(gameEndX, window.getSize().y));//inicjacja zmiennej od ktorej nie nalezy poruszac widokiem view
	stopViewMove = gameEndX + mapend.getSize().x;
	upperBorderY = tileMap[0][0].tilePos.y;
}
Map::~Map(){}

void Map::Update(float deltaTime, sf::View& view, Player* player, bool isHELPscreen)
{
	sf::Vector2f playerPos(player->GetPosition());
	sf::FloatRect playerBodyBounds(player->GetbodyGbounds());
	//ustalenie obecnie widzianego obszaru mapy na podstawie widoku
	fromX = (view.getCenter().x / tileSizeF) - 7;
	toX = (view.getCenter().x / tileSizeF) + 10;
	if (fromX < 0)
		fromX = 0;
	else if (fromX >= mapSizeX)
		fromX = mapSizeX - 1;

	for (int z = 0; z < mapSizeY; z++)//dodawanie przeciwnikow do wektora, nadajac im pozycje kafelkow, obecnie znajduj¹cych siê w widoku
	{
		for (int s = fromX; s < toX; s++)
		{
			ruchRekina = rand() % 4;
			if (tileMap[z][s].placeEnemy == true)// jesli nalezy stworzyc przeciwnika
			{
				if (tileMap[z][s].isPlaced == false)//jezeli jeszcze nie zostal postawiony
				{
					sf::Vector2f temp(tileMap[z][s].tilePos);
					if (tileMap[z][s].isShark == false)//i nie jest to rekin
					{
						//dodaj statek do wektora i oznacz kafelek jako "postawiono przeciwnika"(isPlaced)
						ships.push_back(Ship(&shipTexture, sf::Vector2u(3, 1), 0.3f, temp, sf::Vector2f(250.f, 200.f), window, 100.f));
						tileMap[z][s].isPlaced = true;
					}
					else //jesli rekin
					{
						//dodaj rekin do wektora i oznacz kafelek jako "postawiono przeciwnika"
						sharks.push_back(Shark(&sharkTexture, sf::Vector2u(3, 6), 0.3f, temp, sf::Vector2f(150.f, 100.f), window, ruchRekina));
						tileMap[z][s].isPlaced = true;
					}
				}
			}
		}
	}
	for (size_t f = 0; f < sharks.size(); f++) //aktualizacja rekinow w wektorze
	{
		
		sharks.at(f).Update(deltaTime, &view, isHELPscreen);
		
		if (sharks.at(f).textureBody.getPosition().x <= view.getCenter().x- view.getSize().x/2) //usuwanie rekinow jesli sa poza widzialnym obszarem
		{
			sharks.erase(sharks.begin() + f);
		}
		else {
			//obsluga kolizji z graczem
			Collider playerBodyCollider = player->GetCollider();
			sharks.at(f).bite(player->isHurt(sharks.at(f).GetCollider().checkCollision(playerBodyCollider, 1.0f)));
		}
	}
	for (size_t o = 0; o < ships.size(); o++) //aktualizacja rekinow w wektorze
	{
		ships.at(o).Update(deltaTime, &view, playerPos, playerBodyBounds, isHELPscreen);
		
		if (ships.at(o).textureBody.getPosition().x <= view.getCenter().x / 2.f) //usuwanie rekinow jesli sa poza widzialnym obszarem
		{
			ships.erase(ships.begin() + o);
		}
		else
		{
			//kolizja z nabojami
			player->isHurt(ships.at(o).gotHit());
		}
	}
	if (view.getCenter().x + view.getSize().x >= gameEndX)//jesli koniec mapy jest w zasiegu widoku
		drawEnd = true;
	else
		drawEnd = false;

	
}

void Map::Draw(sf::RenderWindow& window)
{
	if (drawEnd)//jesli nalezy rysowac koniec mapy
		window.draw(mapend);

	for (size_t r = 0; r < ships.size(); r++)
	{
		ships.at(r).Draw(&window);
	}
	for (size_t a = 0; a < sharks.size(); a++)
	{
		sharks.at(a).Draw(window);
	}
	//std::cout << "Ships: " << ships.size()<<"\n";
	//std::cout << "Sharks: " << sharks.size()<<"\n";
}
