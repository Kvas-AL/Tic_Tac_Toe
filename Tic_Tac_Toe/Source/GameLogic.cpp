#include "GameLogic.h"

GameLogic::GameLogic()
{
	this->Restart();
}

int GameLogic::GetCellValue(int i, int y)
{
	return m_PlayingFild[i][y];
}

bool GameLogic::GetCrossTurn()
{
	return m_CrossTurn;
}

int GameLogic::GetWinner()
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
			if (!(x<Points[PointsIter].x || x>Points[PointsIter].x + RECT_HEIGHT || y<Points[PointsIter].y || y>Points[PointsIter].y + RECT_WIDTH))
			{
				if (m_PlayingFild[i][j] == 0)
				{
					if (m_CrossTurn)
					{
						m_PlayingFild[i][j] = CROSS;
						m_CrossTurn = false;
					}
					else
					{
						m_PlayingFild[i][j] = CIRCLE;
						m_CrossTurn = true;
					}
				}
			}
			++PointsIter;
		}
	}
	if (!(m_Victory))
	{
		VictoryCheck();
	}
}

void GameLogic::VictoryCheck()
{
	for (int i = 0, full = 0; i < TOTAL_CELLS / 3; ++i)
	{
		if (std::all_of(m_PlayingFild[i].begin(), m_PlayingFild[i].end(), [](int element) {return element != 0; }))
		{
			++full;
		}

		if (full == 3)
		{
			m_Victory = NOBODY;
		}
	}

	if (!(m_Victory))
	{
		int CrossDiagonalLeft = 0, CrossDiagonalRight = 0;
		int CircelDiagonalLeft = 0, CircelDiagonalRight = 0;
		int RightLeft = TOTAL_CELLS / 3 - 1;

		for (int i = 0; i < TOTAL_CELLS / 3; ++i)
		{
			if (m_PlayingFild[i][0] == 1 && m_PlayingFild[i][1] == 1 && m_PlayingFild[i][2] == 1
				|| m_PlayingFild[0][i] == 1 && m_PlayingFild[1][i] == 1 && m_PlayingFild[2][i] == 1)
			{
				m_Victory = CROSS;
				break;
			}
			else if (m_PlayingFild[i][0] == 2 && m_PlayingFild[i][1] == 2 && m_PlayingFild[i][2] == 2
				|| m_PlayingFild[0][i] == 2 && m_PlayingFild[1][i] == 2 && m_PlayingFild[2][i] == 2)
			{
				m_Victory = CIRCLE;
				break;
			}

			for (int LeftRight = 0; LeftRight < TOTAL_CELLS / 3; ++LeftRight)
			{
				if (LeftRight == i)
				{
					if (m_PlayingFild[i][LeftRight] == CROSS)
					{
						++CrossDiagonalLeft;
					}
					else if (m_PlayingFild[i][LeftRight] == CIRCLE)
					{
						++CircelDiagonalLeft;
					}
				}

				if (RightLeft == LeftRight)
				{
					if (m_PlayingFild[i][RightLeft] == CROSS)
					{
						++CrossDiagonalRight;
					}
					else if (m_PlayingFild[i][RightLeft] == CIRCLE)
					{
						++CircelDiagonalRight;
					}
				}
			}
			if (CrossDiagonalLeft == 3 || CrossDiagonalRight == 3
				|| CircelDiagonalLeft == 3 || CircelDiagonalRight == 3)
			{
				if (CrossDiagonalLeft == 3 || CrossDiagonalRight == 3)
				{
					m_Victory = CROSS;
					break;
				}
				else
				{
					m_Victory = CIRCLE;
					break;
				}
			}
			--RightLeft;
		}
	}
}

void GameLogic::Restart()
{
	for (auto element = m_PlayingFild.begin(); element != m_PlayingFild.end(); ++element)
	{
		element->fill(EMPTY);
	}
	m_CrossTurn = true;
	m_Victory = 0;
}