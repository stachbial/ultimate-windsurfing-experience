#include "Game.h"


Game::Game(GameState& gs,sf::RenderWindow& window, sf::View& View, bool isGamePlayed)
{
	this->window = &window;
	this->View = &View;
	LoadState = gs;
	visibleSegment = 7;																//inicjacja zmiennej, domyslnie ustawione na help screen
	this->isGamePlayed = isGamePlayed;
	isPaused = false;
	endSettingsDone = false;
	czasF = LoadState.gameTime - 3.f;

	segmentGUI = new SegmentGUI(visibleSegment, window, viewPos);
//inicjacja napisow i serc
	if (!font.loadFromFile("resources\\fullPack2025.ttf"))							//pobieramy czcionke numer 1
		return;
	//nick
	nickString = FileWork::convertToString(LoadState.nick);
	nick.setString(nickString);
	nick.setFont(font);
	nick.setFillColor(sf::Color::Yellow);
	nick.setCharacterSize(38);
	nick.setStyle(sf::Text::Regular);
	nick.setOutlineColor(sf::Color(97, 35, 103));//(97, 35, 103)
	nick.setOutlineThickness(3);
	nickRect = nick.getLocalBounds();//do ustalenia originu
	nick.setOrigin(nickRect.left + nickRect.width / 2.0f, nickRect.top + nickRect.height / 2.0f);
	nick.setPosition(sf::Vector2f((nickRect.left + nickRect.width / 2.0f)+100.f, 80.f));
	//czas
	czas.setString(LoadState.nick);
	czas.setFont(font);
	czas.setFillColor(sf::Color::Yellow);
	czas.setCharacterSize(38);
	czas.setStyle(sf::Text::Regular);
	czas.setOutlineColor(sf::Color(97, 35, 103));//(97, 35, 103)
	czas.setOutlineThickness(3);
	czasRect = czas.getLocalBounds();//do ustalenia originu
	czas.setOrigin(czasRect.left + czasRect.width / 2.0f, czasRect.top + czasRect.height / 2.0f);
	czas.setPosition(sf::Vector2f((nickRect.left + nickRect.width)+(czasRect.left + czasRect.width)+50.f, 80.f));
	//F1 - help
	help.setString("F1 or F1 AND 'fn' - HELP");
	help.setFont(font);
	help.setFillColor(sf::Color::White);
	help.setCharacterSize(28);
	help.setStyle(sf::Text::Regular);
	help.setOutlineColor(sf::Color(97, 35, 103));//(97, 35, 103)
	help.setOutlineThickness(2);
	helpRect = help.getLocalBounds();//do ustalenia originu
	help.setOrigin(helpRect.left + helpRect.width / 2.0f, helpRect.top + helpRect.height / 2.0f);
	help.setPosition(sf::Vector2f(window.getSize().x - (helpRect.left + helpRect.width) - 50.f, 80.f));
	//ESC - EXIT
	esc.setString("ESC - EXIT");
	esc.setFont(font);
	esc.setFillColor(sf::Color::White);
	esc.setCharacterSize(28);
	esc.setStyle(sf::Text::Regular);
	esc.setOutlineColor(sf::Color(97, 35, 103));//(97, 35, 103)
	esc.setOutlineThickness(2);
	escRect = esc.getLocalBounds();//do ustalenia originu
	esc.setOrigin(escRect.left + escRect.width / 2.0f, escRect.top + escRect.height / 2.0f);
	esc.setPosition(sf::Vector2f(window.getSize().x - (escRect.left + escRect.width) - 50.f, 100.f));
	//heart
	heartS.setSize(sf::Vector2f(50.f, 50.f));
	if (!heartT.loadFromFile("resources\\heart.png"))							//pobieramy czcionke numer 1
		return;
	heartS.setTexture(&heartT);
	

	//inicjacja elementów gry
	playerTexture.loadFromFile("resources\\windsurfer.png");									//zaladuj texture ""windsurfer.png" do zmiennej "playertexture"
	player = new Player(&playerTexture, sf::Vector2u(3, 4), 0.3f, 180.f, sf::Vector2f(LoadState.PlayerPosX, LoadState.PlayerPosY), LoadState.hp);

	map = new Map(gs.poziomT, window);

	View.setCenter(sf::Vector2f(LoadState.ViewPosX, LoadState.ViewPosY));
}


void Game::Update(float deltaTime)
{
//aktualizacja obiektow zwiazanych z rozgrywka
	player->Update(deltaTime, *View, *window, map->getUpperMapBorder(), map->getViewMovementBorder(), isPaused);
	map->Update(deltaTime, *View, player, isPaused);


//aktualizacja czasu
	time = clock.getElapsedTime();
	if (!isPaused)
		czasF += time.asSeconds() -0.999f;//-3f aby zniwelowac opoznienie zwiazane z ladowaniem gry
	else
	{
		getCUrrentTime(czasF);
	}
	
//aktualizacja napisow i serc

  //czas i nick

	//pozycje napisow
	nickPos = sf::Vector2f((View->getCenter().x - View->getSize().x/2.f) + (nickRect.left + nickRect.width / 2.0f) + 100.f, 80.f);
	czasPos = sf::Vector2f((View->getCenter().x - View->getSize().x / 2.f) + (nickRect.left + nickRect.width) + (czasRect.left + czasRect.width) + 50.f, 80.f);
	nick.setPosition(nickPos);
	czas.setPosition(czasPos);
	//zawartosc napisu "czas"
	std::stringstream czasGry;//zmienna typy string stream do przekazania wartosci zmiennej czas jako string
	czasGry << "Czas !  " << czasF;
	czas.setString(czasGry.str());
	//help i esc
	help.setPosition(sf::Vector2f((View->getCenter().x + View->getSize().x / 2.f) - (helpRect.left + helpRect.width)/1.5f , 80.f));
	esc.setPosition(sf::Vector2f((View->getCenter().x + View->getSize().x / 2.f) - (escRect.left + escRect.width) , 135.f));
	//serca
	life.clear();//zeruj dotyczasowa zawartosc wektora
	if (player->getHP() >= 0)
	{
		for (int i = 0; i < player->getHP(); i++)//ustalenie ilosci zyc do wyswietlenia
		{
			heartPos = sf::Vector2f((View->getCenter().x - View->getSize().x / 2.f) + (100.f + i * heartS.getSize().x), 120.f);
			heartS.setPosition(heartPos);
			life.push_back(heartS);
		}
	}
	//aktualizacja pozycji widoku
	viewPos.x = View->getCenter().x - (View->getSize().x / 2.f);
	//okreslenie czy nalezy zakonczyc rozgrywke
	if (player->GetPosition().x >= map->getMapEndX())
		gameWon();
	if (player->getHP() <= 0)
		gameLost();
}

void Game::Draw(sf::RenderWindow& window)
{
	

	//jesli gra wstrzymana
	if (isPaused)//rysuj napisy
	{
		segmentGUI->Draw(window);
	}
	else//jesli rozgrywka trwa - rysuj jej elementy
	{
		map->Draw(window);//rysuj mape(przeciwnikow)
		player->Draw(window);//rysuj gracza
		//napisy
		window.draw(nick);
		window.draw(czas);
		window.draw(esc);
		window.draw(help);
		//serca
		for (int j = 0; j < life.size(); j++)
		{
			window.draw(life.at(j));
		}
	}
	
}

void Game::Help_Esc_screenUpdate(sf::Event& keybordEvent)
{
	if (keybordEvent.type == sf::Event::KeyPressed)
	{
		//obsluga HELP
		if (keybordEvent.key.code == sf::Keyboard::F1)
			isF1pressed = true;

		if(isF1pressed)
		{
			delete segmentGUI;
			visibleSegment = 7;
			segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
			isPaused = true;
		}

		if (isPaused == true && visibleSegment == 7 && keybordEvent.key.code == sf::Keyboard::Enter)
		{
			visibleSegment = 0;
			isF1pressed = false;
			isPaused = false;
		}
			//obsluga ESC
		if (keybordEvent.key.code == sf::Keyboard::Escape)
		{
			delete segmentGUI;
			visibleSegment = 8;
			segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
			isPaused = true;//show escp screen
			
		}
		if (isPaused == true && visibleSegment == 8)//jesli aktualnie wyswietlany ESC screen
		{
			if (keybordEvent.key.code == sf::Keyboard::Up)
				segmentGUI->przesunG();

			if (keybordEvent.key.code == sf::Keyboard::Down)
				segmentGUI->przesunD();

			if (keybordEvent.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 1)
			{
				gramDalej();
			}

			if (keybordEvent.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 2)
			{
				saveANDquit();
			}
			if (keybordEvent.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 3)
			{
				justQuit();
			}
		}
		//obsluga Win Screen oraz Lost Screen
		if (isPaused == true && visibleSegment > 8 && keybordEvent.key.code == sf::Keyboard::Enter)
		{
			justQuit();
		}

	}
}

void Game::gramDalej()
{
	visibleSegment = 0;
	isPaused = false;
	resumeTime(czasF);
}

void Game::saveANDquit()
{
	//aktualizowanie pól struktury
	getCUrrentTime(czasF);
	LoadState.gameTime = currentTime;
	LoadState.hp = player->getHP();
	LoadState.PlayerPosX = player->GetPosition().x;
	LoadState.PlayerPosY = player->GetPosition().y;
	LoadState.ViewPosX = View->getCenter().x;
	LoadState.ViewPosY = View->getCenter().y;
	//zapis struktury do pliku
	FileWork::zapisz_stan_gry(LoadState);
	isGamePlayed = false;
}

void Game::justQuit()
{
	isGamePlayed = false;
}

void Game::getCUrrentTime(float czasShown)
{
	currentTime = czasShown;
}

void Game::resumeTime(float& czasToShow)
{
	clock.restart();
	czasToShow = currentTime;
}


void Game::gameLost()
{
	if (!endSettingsDone)
	{
		isPaused = true;
		getCUrrentTime(czasF);

		//ustalenie segmentuGUI z odpowiednim tektem do wyswietlenia
		visibleSegment = 10;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);

		//inicjacja tekstu zwi¹zanego z wygran¹ gr¹
		std::string win = "Przegrales    " + nickString;

		//2 wiersz
		std::stringstream wynik;//zmienna typy string stream do przekazania wartosci zmiennej czas jako string
		wynik << "Twoj wynik !  " << currentTime;
		//ustawienie ³ancuchow znaków dla wierszy

		segmentGUI->updateTextString(win, 0);
		segmentGUI->updateTextString(wynik.str(), 1);

		//ustaw flage aby instrukcje nie wykonywaly siê niepotrzebnie w pêtli
		endSettingsDone = true;
	}
}

void Game::gameWon()
{
	if (!endSettingsDone)
	{
		isPaused = true;
		getCUrrentTime(czasF);

		//ustalenie segmentuGUI z odpowiednim tektem do wyswietlenia
		visibleSegment = 9;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);

		//inicjacja tekstu zwi¹zanego z wygran¹ gr¹
		std::string win;
		win = "WYGRALES    " + nickString;

		//2 wiersz
		std::stringstream wynik;//zmienna typy string stream do przekazania wartosci zmiennej czas jako string
		wynik << "Twoj wynik !  " << currentTime;
		//ustawienie ³ancuchow znaków dla wierszy

		segmentGUI->updateTextString(win, 0);
		segmentGUI->updateTextString(wynik.str(), 1);

		//aktualizowanie pól struktury
		LoadState.gameTime = currentTime;
		//zapisz do listy graczy
		FileWork::zapisz_do_listyGraczy(LoadState);
		
		//ustaw flage aby instrukcje nie wykonywaly siê niepotrzebnie w pêtli
		endSettingsDone = true;
	}
}


 