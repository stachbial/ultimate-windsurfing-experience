#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow& window, sf::View& View)
{	
	this->window = &window;
	this->view = &View;
	isGamePlayed = false;
	isViewReset = true;
	showIRRshape = false;

	width = window.getSize().x;
	height = window.getSize().y;
	visibleSegment = 0;  
//inicjalizacja struktury stan gry
	innitialGameState = {								
	206.f, 420.f,											// initial playerPosition  
	window.getSize().x / 2.f, window.getSize().y / 2.f,		//initial ViewPos								//View position
	"player",												//domyslny nick
	4,														//hp
	0,														//domyslny poziom trudnosci(easy)
	0.f														//inicjacja czasu
	};
	gs = innitialGameState;//inicjacja struktury w oparciu o ktora tworzona bedzie rozgrywka na initialGameSate
	bg = new BackGround(window, sf::Vector2u(6, 1), 0.5f, 2);
	segmentGUI = new SegmentGUI(visibleSegment, window, viewPos);//domyslnie rysuj glowny segment
	game = new Game(gs ,window, *view, isGamePlayed);								//inicjacja obiektu rozgrywki

	
	//inicjacja obiektu o nieregularnym kszta³cie
	initializeIRRshape();
	totalTime = 0.f;

}

void GameEngine::guiUpdate(sf::Event& event)
{
	if (game->isGamePlaying())//jesli toczy sie rozgrywka
		isGamePlayed = true;
	else
		isGamePlayed = false;

	if (!isGamePlayed)//jesli nie trwa aktualnie rozgrywka
	{
		if (!isViewReset)//jesli nie ustawiono spowrotem widoku i tla
		{
			delete bg;
			bg = new BackGround(*window, sf::Vector2u(6, 1), 0.5f, 2);//ustaw tlo
			view->setCenter(sf::Vector2f(width / 2.f, height / 2.f));//ustaw widok
			isViewReset = true;//ustaw flage na "ustawiono"
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
				segmentGUI->przesunG();

			if (event.key.code == sf::Keyboard::Down)
				segmentGUI->przesunD();

			if (event.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 0)
			{
				selected0(visibleSegment);
			}
			if (event.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 1)
			{
				selected1(visibleSegment);
			}

			if (event.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 2)
			{
				selected2(visibleSegment);
			}

			if (event.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 3)
			{
				selected3(visibleSegment);
			}
			if (event.key.code == sf::Keyboard::Enter && segmentGUI->getSelectedItem() == 4)
			{
				selected4(visibleSegment);
			}
			//obsluga irregularShape animation
			if (visibleSegment == 0 && event.key.code == sf::Keyboard::S)
			{
				//myDelay(10);
				if (showIRRshape == true)
					showIRRshape = false;
				else
					showIRRshape = true;
			}
		}
		if (visibleSegment == 1)//obsluga mechanizmu wpisywania nicku w odpowiednim segmencie													//jesli aktualnie wyswietlany jest 1 segment
		{
			if (event.type == sf::Event::TextEntered)										//jesli prowadzono text z klawiatury
			{
				inputNick += event.text.unicode;											//dodaj wcisniet¹ litere do ³añcucha inputNick
				if (event.text.unicode == 8 || event.text.unicode == 127)						//jesli zosta³ wciœniêty klawisz BackSpace lub delete
				{
					if (inputNick.size() > 1)												//jesli ³añcuch zawiera jakieœ znaki
						inputNick.resize(inputNick.size() - 2);								//usun ostatni¹ literê z ³ancucha inputNick(usuwam dwa bo jeszcze znak koñca ³añcucha "\0")
				}
				segmentGUI->updateTextString(inputNick, 1);										//ustaw odpowiedni text odpowiedniego wierszu tablicy w segmencie na inputNick
			}
		}
		//obsluga credits i pokazywanie animacji nieregularnego ksztaltu
		//credits
		if (visibleSegment == 0 && event.key.code == sf::Keyboard::C)//JESLI WYBRANO "CREDITS"
		{
			delete segmentGUI;
			visibleSegment = 11;
			segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		}
		if (visibleSegment == 11 && event.key.code == sf::Keyboard::Enter)//jesli wyjdz z credits - pokaz menu glowne
		{
			delete segmentGUI;
			visibleSegment = 0;
			segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		}

	}
	else//jesli toczy sie rozgrywka aktualizuj j¹
	{
		game->Help_Esc_screenUpdate(event);
	}
}

void GameEngine::gamePlayUpdate(float deltaTime)
{
	if (isGamePlayed)
		game->Update(deltaTime);
}

void GameEngine::BGupdate(float deltaTime)
{
	bg->BGupdate(*view, deltaTime);
	//animuj nieregularny obiekt
	if(showIRRshape && visibleSegment == 0)
		MoveIRRshape(deltaTime);
}

void GameEngine::draw(sf::RenderWindow& window)												//rysuj GUi
{
	bg->draw(window);

	if (!isGamePlayed)
	{
		if(showIRRshape && visibleSegment == 0)//jesli widoczna jest pierwsza strona menu
		drawIRRshape(window);

		segmentGUI->Draw(window);															//rysuj aktualny segment w oknie
	}
	else
		game->Draw(window);
}



void GameEngine::selected0(unsigned int& visibleSegment)										//funkcja obs³uguj¹ca wybór opcji o numerze 0
{
	switch (visibleSegment)
	{
	case 0:
		//nowa gra
		delete segmentGUI;
		visibleSegment++;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 3:
		//graj !!!!
	//obsluga gui
		delete segmentGUI;
		visibleSegment = 0;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		gs = innitialGameState;//ustal domyslna wartosc struktury, na podstawie ktorej inicjowana bedzie rozgrywka(czyszczenie pól po wczesniejszym wpisaniu gry)
	//inicjalizacja rozgrywki
		//przekazanie nicku do struktury gs w formie tablicy char
		strcpy(gs.nick, inputNick.c_str());
		//przekazanie do gs informacji o poziomie trudnosci
		gs.poziomT = poziomT;
		//ostateczna inicjalizacja rozgrywki
		delete game;
		isGamePlayed = true;
		isViewReset = false;
		game = new Game(gs, *window, *view, isGamePlayed);
		break;
	default:
		break;
	}
}
void GameEngine::selected1(unsigned int& visibleSegment)										//funkcja obs³uguj¹ca wybór opcji o numerze 1
{
	switch (visibleSegment)
	{
	case 0:
		//wczytaj gre
		delete segmentGUI;
		visibleSegment = 4;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	
	case 2:
		// wybierz Easy
		delete segmentGUI;
		visibleSegment = 3;
		segmentGUI = new SegmentGUI(visibleSegment, *window,viewPos);
		poziomT = 0;//easy
		break;
	case 3:
		//wroc do wyboru poziomu trudnosci
		delete segmentGUI;
		visibleSegment = 2;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 4:
		//wczytaj 1 save
		delete segmentGUI;
		visibleSegment = 5;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 5:
		//Jestes pewny aby nadpisac ten plik? !!!!!!!!!!!! - inicjalizacja rozgrywki na podstawie wczytanego pliku
		//obsluga gui
		delete segmentGUI;
		visibleSegment = 0;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		//wczytanie parametrow z pliku do struktury
		FileWork::wczytaj_stan_gry(gs);
		//ostateczna inizjalizacja rozgrywki
		delete game;
		isGamePlayed = true;
		isViewReset = false;
		game = new Game(gs, *window, *view, isGamePlayed);
		break;
	default:
		break;
	}
}
void GameEngine::selected2(unsigned int& visibleSegment)										//funkcja obs³uguj¹ca wybór opcji o numerze 2
{
	switch (visibleSegment)
	{
	case 0:
		//najlepsze wyniki
		delete segmentGUI;
		visibleSegment = 6;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 1:
		//zatwierdz nick
		delete segmentGUI;
		visibleSegment = 2;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 2:
		// wybierz poziom Hard
		delete segmentGUI;
		visibleSegment = 3;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		poziomT = 1; // Hard
		break;
	case 3:
		//wroc do menu glownego
		delete segmentGUI;
		visibleSegment = 0;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 4:
		//wstecz
		delete segmentGUI;
		visibleSegment = 0;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 5:
		//wstecz
		delete segmentGUI;
		visibleSegment = 4;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	default:
		break;
	}
}
void GameEngine::selected3(unsigned int& visibleSegment)										//funkcja obs³uguj¹ca wybór opcji o numerze 3
{
	switch (visibleSegment)
	{
	case 0:
		//wyjdz z gry
		delete segmentGUI;
		//prawdopodobnie funkcja delete GUI (do przeanalizowania)
		exit(0);
		break;
	case 1:
		//wstecz
		delete segmentGUI;
		visibleSegment = 0;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	default:
		break;
	}
}
void GameEngine::selected4(unsigned int& visibleSegment)										//funkcja obs³uguj¹ca wybór opcji o numerze 4
{
	switch (visibleSegment)
	{
	case 2:
		//wstecz
		//()kasujWpisanyNick
		delete segmentGUI;
		visibleSegment = 1;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	case 6:
		//wstecz
		delete segmentGUI;
		visibleSegment = 0;
		segmentGUI = new SegmentGUI(visibleSegment, *window, viewPos);
		break;
	default:
		break;
	}
}

