#pragma once
#include "All_Included_libs.h"

const int RECT_WIDTH = 266;
const int RECT_HEIGHT = 200;

const int TOTAL_CELLS = 9;

enum Notation
{
	EMPTY = 0,
	CROSS,
	CIRCLE,

	NOBODY
};

class GameLogic
{
public:

	GameLogic();

	int GetCellValue(int i, int y);
	bool GetCrossTurn();
	int GetWinner();

	void Turn(const std::array<SDL_Point, TOTAL_CELLS>& Points, SDL_Event event);

	void VictoryCheck();

	void Restart();

private:
	std::array<std::array<int, TOTAL_CELLS / 3>, TOTAL_CELLS / 3> m_PlayingFild;
	int m_Victory;
	bool m_CrossTurn;
};