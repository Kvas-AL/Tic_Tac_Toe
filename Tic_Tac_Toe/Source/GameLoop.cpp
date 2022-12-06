#include "GameLoop.h"

std::array<SDL_Point, TOTAL_CELLS> GetPoints()
{
	std::array<SDL_Point, TOTAL_CELLS> CellPoints;

	int i = 0;
	for (int w = SCREEN_WIDTH / SCREEN_WIDTH; w + RECT_WIDTH <= SCREEN_WIDTH; w += RECT_WIDTH)
	{
		for (int h = SCREEN_HEIGHT / SCREEN_HEIGHT - 1; h + RECT_HEIGHT <= SCREEN_HEIGHT; h += RECT_HEIGHT)
		{
			CellPoints[i].x = w;
			CellPoints[i].y = h;
			++i;
		}
	}

	return CellPoints;
}

bool TextureInit(std::array<Texture, TOTAL_TEXTURE>& AllTextures, Engine Engine)
{
	bool successful = true;

	for (int i = 0; i < TOTAL_TEXTURE; ++i)
	{
		switch (i)
		{
		case CROSS_TEXTURE: AllTextures[CROSS_TEXTURE].LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\CrossSprite.png", Engine.GetRenderer()); break;
		case CIRCLE_TEXTURE: AllTextures[CIRCLE_TEXTURE].LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\CircleSprite.png", Engine.GetRenderer()); break;
		case CROSS_WIN_SCREEN_TEXTURE: AllTextures[CROSS_WIN_SCREEN_TEXTURE].LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\CrossWinScreen.png", Engine.GetRenderer()); break;
		case CIRCLE_WIN_SCREEN_TEXTURE: AllTextures[CIRCLE_WIN_SCREEN_TEXTURE].LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\CircleWinScreen.png", Engine.GetRenderer()); break;
		case DRAW_WIN_SCREEN_TEXTURE: AllTextures[DRAW_WIN_SCREEN_TEXTURE].LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\DrawWinScreen.png", Engine.GetRenderer()); break;
		}

		if (AllTextures[i].GetTexture() == nullptr)
		{
			successful = false;
		}
	}

	return successful;
}

void GameLoop()
{
	Engine Engine;
	GameLogic Logic;
	std::array<Texture, TOTAL_TEXTURE> AllTextures;

	if (!Engine.Init())
	{
		std::cout << "Faild to initialize!";
	}
	else
	{
		if (!TextureInit(AllTextures, Engine))
		{
			std::cout << "Faild to load images!";
		}
		else
		{
			bool quit = false;

			SDL_Event e;
			const std::array<SDL_Point, TOTAL_CELLS> Points = GetPoints();

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						if (!Logic.GetWinner())
						{
							Logic.Turn(Points, e);
						}
						else
						{
							Logic.Restart();
						}
					}
				}
				SDL_SetRenderDrawColor(Engine.GetRenderer(), 0xC0, 0xC0, 0xC0, 0xC0);
				SDL_RenderClear(Engine.GetRenderer());

				SDL_SetRenderDrawColor(Engine.GetRenderer(), 0x00, 0x00, 0x00, 0x00);

				if (!Logic.GetWinner())
				{
					int PointIter = 0;
					for (int i = 0; i < TOTAL_CELLS / 3; ++i)
					{
						for (int y = 0; y < TOTAL_CELLS / 3; ++y)
						{
							SDL_Rect RectangleCell = { Points[PointIter].x,Points[PointIter].y,RECT_WIDTH,RECT_HEIGHT };
							SDL_RenderDrawRect(Engine.GetRenderer(), &RectangleCell);
							if (Logic.GetCellValue(i, y) == 1)
							{
								AllTextures[CROSS_TEXTURE].TextureRender(Points[PointIter].x, Points[PointIter].y, Engine.GetRenderer());
							}
							else if (Logic.GetCellValue(i, y) == 2)
							{
								AllTextures[CIRCLE_TEXTURE].TextureRender(Points[PointIter].x, Points[PointIter].y, Engine.GetRenderer());
							}
							++PointIter;
						}
					}
				}
				SDL_RenderPresent(Engine.GetRenderer());
			}
		}
	}
}