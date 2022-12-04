#include "GameLoop.h"

std::array<SDL_Point, TOTAL_CELLS> GetPoints()
{
	std::array<SDL_Point, TOTAL_CELLS> CellPoints;

	int i = 0;
	for (int h = SCREEN_HEIGHT / SCREEN_HEIGHT - 1; h + RECT_HEIGHT < SCREEN_HEIGHT; h += RECT_HEIGHT)
	{
		for (int w = SCREEN_WIDTH / SCREEN_WIDTH; w < SCREEN_WIDTH; w += RECT_WEIGHT)
		{
			CellPoints[i].x = w;
			CellPoints[i].y = h;
			++i;
		}
	}

	return CellPoints;
}

void GameLoop()
{
	Engine Engine;
	if (!Engine.Init())
	{
		std::cout << "Faild to initialize!";
	}
	else
	{
		Texture CircleTexture;
		Texture CrossTexture;
		if (!CircleTexture.LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\CircleSprite.png", Engine.GetRenderer())
			|| !CrossTexture.LoadFromFile("C:\\CPP\\Tic_Tac_Toe\\Tic_Tac_Toe\\Data\\CrossSprite.png", Engine.GetRenderer()))
		{
			std::cout << "Faild to load images!";
		}
		else
		{
			bool quit = false;

			SDL_Event e;
			GameLogic Logic;
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
						Logic.Turn(Points, e);
					}
				}
				SDL_SetRenderDrawColor(Engine.GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Engine.GetRenderer());

				SDL_SetRenderDrawColor(Engine.GetRenderer(), 0x00, 0x00, 0x00, 0x00);

				int PointIter = 0;
				for (int i = 0; i < TOTAL_CELLS / 3; ++i)
				{
					for (int y = 0; y < TOTAL_CELLS / 3; ++y)
					{
						SDL_Rect RectangleCell = { Points[PointIter].x,Points[PointIter].y,RECT_WEIGHT,RECT_HEIGHT };
						SDL_RenderDrawRect(Engine.GetRenderer(), &RectangleCell);
						if (Logic.GetCellValue(i, y) == 1)
						{
							CrossTexture.TextureRender(Points[PointIter].x, Points[PointIter].y, Engine.GetRenderer());
						}
						else if (Logic.GetCellValue(i, y) == 2)
						{
							CircleTexture.TextureRender(Points[PointIter].x, Points[PointIter].y, Engine.GetRenderer());
						}
						++PointIter;
					}
				}
				SDL_RenderPresent(Engine.GetRenderer());
			}
		}
	}
}