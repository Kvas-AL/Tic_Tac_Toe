#pragma once
#include "All_Included_libs.h"
#include "Texture.h"

extern const int RECT_WEIGHT;
extern const int RECT_HEIGHT;

const int TOTAL_CELLS = 9;

enum Victory
{
	CROSS = 1,
	CIRCLE
};

class GameLogic
{
public:

	GameLogic();

	int GetCellValue(int i, int y);
	bool GetTurn();
	int GetVictory();

	void Turn(const std::array<SDL_Point, TOTAL_CELLS>& Points, SDL_Event event);

	void VictoryCheck();

private:
	std::array<std::array<int, TOTAL_CELLS / 3>, TOTAL_CELLS / 3> m_PlayingFild;
	bool m_CrossTurn;
	int m_Victory;
};