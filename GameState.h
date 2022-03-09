#pragma once
#include <SFML/Graphics.hpp>

#pragma pack(push)//w celu ujednolicenia ilosci bitow , w jakiej przechowywana bêdzie struktura
#pragma pack(1)
typedef struct {
	float PlayerPosX;
	float PlayerPosY;
	float ViewPosX;
	float ViewPosY;
	char nick[30];
	unsigned int hp;
	unsigned int poziomT;
	float gameTime;
}GameState;
#pragma pack(pop)