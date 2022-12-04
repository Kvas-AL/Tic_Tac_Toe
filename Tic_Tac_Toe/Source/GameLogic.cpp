#include "GameLogic.h"

GameLogic::GameLogic()
{
	for (auto element = m_PlayingFild.begin(); element != m_PlayingFild.end(); ++element)
	{
		element->fill(0);
	}
	m_CrossTurn = true;
	m_Victory = 0;
}

int GameLogic::GetCellValue(int i, int y)
{
	return m_PlayingFild[i][y];
}

bool GameLogic::GetTurn()
{
	return m_CrossTurn;
}

int GameLogic::GetVictory()
{
	return m_Victory;
}

void GameLogic::Turn(const std::array<SDL_Point, TOTAL_CELLS>& Points, SDL_Event event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	int PointsIter = 0;
	for (int i = 0; i < TOTAL_CELLS / 3; ++i)
	{
		for (int j = 0; j < TOTAL_CELLS / 3; ++j)
		{
			if (!(x<Points[PointsIter].x || x>Points[PointsIter].x + RECT_WEIGHT || y<Points[PointsIter].y || y>Points[PointsIter].y + RECT_HEIGHT))
			{
				if (m_PlayingFild[i][j] == 0)
				{
					if (m_CrossTurn)
					{
						m_PlayingFild[i][j] = 1;
						m_CrossTurn = false;
					}
					else
					{
						m_PlayingFild[i][j] = 2;
						m_CrossTurn = true;
					}
				}
			}
			++PointsIter;
		}
	}
	VictoryCheck();
}
// TODO
void GameLogic::VictoryCheck()
{
	for (int i = 0; i < TOTAL_CELLS / 3; ++i)
	{
		for (int j = 0; j < TOTAL_CELLS / 3; ++j)
		{
			if (m_PlayingFild[i][j] == CROSS && m_PlayingFild[i][j + 1] && m_PlayingFild[i][j + 2] == CROSS)
			{

			}
		}
	}
}
