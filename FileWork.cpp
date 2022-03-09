#include "FileWork.h"


void FileWork::swapRecords(GameState& oddaj, GameState& przyjmij)
{
	GameState temp;
	temp.PlayerPosX = przyjmij.PlayerPosX;
	temp.PlayerPosY = przyjmij.PlayerPosY;
	temp.ViewPosX = przyjmij.ViewPosX;
	temp.ViewPosY = przyjmij.ViewPosY;
	strcpy(temp.nick, przyjmij.nick);
	temp.hp = przyjmij.hp;
	temp.poziomT = przyjmij.poziomT;
	temp.gameTime = przyjmij.gameTime;

	przyjmij.PlayerPosX = oddaj.PlayerPosX;
	przyjmij.PlayerPosY = oddaj.PlayerPosY;
	przyjmij.ViewPosX = oddaj.ViewPosX;
	przyjmij.ViewPosY = oddaj.ViewPosY;
	strcpy(przyjmij.nick, oddaj.nick);
	przyjmij.hp = oddaj.hp;
	przyjmij.poziomT = oddaj.poziomT;
	przyjmij.gameTime = oddaj.gameTime;

	oddaj.PlayerPosX = temp.PlayerPosX;
	oddaj.PlayerPosY = temp.PlayerPosY;
	oddaj.ViewPosX = temp.ViewPosX;
	oddaj.ViewPosY = temp.ViewPosY;
	strcpy(oddaj.nick, temp.nick);
	oddaj.hp = temp.hp;
	oddaj.poziomT = temp.poziomT;
	oddaj.gameTime = temp.gameTime;

}

std::string FileWork::convertToString(char* charArray)//zamiana z tablicy znakow na std::string
{
	std::string s = charArray;
	return s;
}



void FileWork::zapisz_stan_gry(GameState gs)//funkcja zapisuje aktualne wartoœci pól struktury do pliku "ostatniZapis"
{
	FILE* fp;
	fp = fopen("ostatniZapis.dat", "w+b");//otwarcie pliku w trybie zapisu
	//niepotrzebne->fseek(fp, 0* sizeof(GameState), SEEK_SET);//ustawienie wskaznika na poczatek pliku
	fwrite(&gs, sizeof(GameState), 1, fp);//zapisanie zawartosci struktury podanej jako parametr
	fclose(fp);
}

void FileWork::wczytaj_stan_gry(GameState& gs)//funkcja inicjalizuje pola struktury podanej w parametrze na bodstawie odczytu z pliku "ostatniZapis"
{
	FILE* fp;
	fp = fopen("ostatniZapis.dat", "r+b");//otwarcie pliku w trybie odczytu
	if (fp != NULL)
		std::cout << "B³¹d otwarcia pliku 'ostatniZapis.dat'" << std::endl;
	GameState buf;
	fread(&buf, sizeof(GameState), 1, fp);//odczyt i zapis bloku danych wielkosci GameState do bufora
	gs = buf;

	fclose(fp);
}



void FileWork::zapisz_do_listyGraczy(GameState gs)//funkcja zapisuje strukturê do pliku "listaGraczy"
{
	FILE* fp;
	fp = fopen("listaGraczy.dat", "a+b");//otwarcie pliku w trybie dopisywania i odczytu
	fwrite(&gs, sizeof(GameState), 1, fp);//zapisanie zawartosci struktury podanej jako parametr
	fclose(fp);
}

void FileWork::ustal_podium()//funkcja sortuje plik "listaGraczy" w kolejnosci malejacej pod wzgledem czasu ukonczenia rozgrywki
{
	GameState* listaG;
	int liczbaRekordow;
	FILE* fp;
	//ustalenie ilosci rekordow zapisanych w pliku
	fp = fopen("listaGraczy.dat", "r+b");//ostwarcie pliku do zapisu i odczytu
	fseek(fp, 0, SEEK_END);//ustawienie wskaznika na koniec pliku
	liczbaRekordow = ftell(fp) / sizeof(GameState);//ustalenie ilosci rekordow pliku poprzez podzielenie dlugosci pliku w bajtach na dlugosc jednej struktury w bajtach
	rewind(fp);//wróæ na pocz¹tek
//zapisanie rekordow z pliku do tymczasowej tablicy tworzonej dynamicznie
	listaG = new GameState[liczbaRekordow];//dynamiczna tablica w celu skopiowania zawartosci listy graczy
	for (int i = 0; i < liczbaRekordow; i++)
		fread(&listaG[i], sizeof(GameState), 1, fp);
	fclose(fp);

	//sortowanie b¹belkowe utworzonej tablicy wzglêdem czasu rozgrywki danego gracza
	for (int j = 0; j < liczbaRekordow; j++)//bubble sort
		for (int k = j + 1; k < liczbaRekordow; k++)
		{
			if (listaG[k].gameTime < listaG[j].gameTime)
				swapRecords(listaG[k], listaG[j]);
		}
	//otwarcie pliku w celu zapisania posortowanej tablicy struktur
	fp = fopen("listaGraczy.dat", "w+b");//otwarcie pliku w celu zapisania posortowanej tablicy struktur
	for (int p = 0; p < liczbaRekordow; p++)
		fwrite(&listaG[p], sizeof(GameState), 1, fp);
	fclose(fp);
}

std::string FileWork::zwroc_zawodnika_podium(int nrMiejsca)//zwraca ³añcuch znaków z informacj¹ na temat zawodnika z numerem miejsca na podium podanego w parametrze
{
	//zapis rekordu po¿¹danego racza do zmiennej tymczasowej
	//nrMiejsca - 1;
	GameState temp;
	FILE* fp;
	fp = fopen("listaGraczy.dat", "r+b");
	fseek(fp, nrMiejsca * sizeof(GameState), SEEK_CUR);
	//GameState buf;
	fread(&temp, sizeof(GameState), 1, fp);
	//in = buf;
	fclose(fp);
	//konkatenacja ³añcuchów znaków utworzonych na podstawie wartoœci pól pobranej struktury
		//zamiana tablicy char na std::string
	std::string Nick = FileWork::convertToString(temp.nick);

	////ustalenie poziomu truddnosci s³ownie
	std::string poziomT;

	if (temp.poziomT == 0)
		poziomT = " Easy";

	if (temp.poziomT == 1)
		poziomT = " Hard";

	if (temp.poziomT == 2)
		poziomT = " Afterparty";

	//po³¹czenie wszystkich zmiennych w jeden wiersz typu sstream
	std::ostringstream ss;
	ss << nrMiejsca + 1 << ". " << Nick << poziomT << " Czas :  " << temp.gameTime;
	//utworzenie ostatecznego ³añcucha zwracanego przez funkcje
	std::string playerRecord(ss.str());
	return playerRecord;
}