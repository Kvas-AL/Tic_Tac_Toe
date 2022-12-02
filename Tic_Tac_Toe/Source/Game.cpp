#include "Game.h"

const int RECT_WEIGHT = 266;
const int RECT_HEIGHT = 200;

Game::Game() : m_Renderer(nullptr), m_Window(nullptr) {}

Game::~Game()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = nullptr;
	m_Window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer()
{
	return m_Renderer;
}

SDL_Window* Game::GetWindow()
{
	return m_Window;
}

bool Game::Init()
{
	bool successful = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
		successful = false;
	}
	else
	{
		m_Window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
		if (!(m_Window))
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
			successful = false;
		}
		else
		{
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!(m_Renderer))
			{
				std::cout << "Remderer could not be created! SDL Error: " << SDL_GetError() << "\n";
				successful = false;
			}
			else
			{
				int ImgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(ImgFlag) & ImgFlag))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
					successful = false;
				}
			}
		}
	}
	return successful;
}

bool Game::LoadMedia()
{


	return false;
}

void GameLoop()
{
	Game Game;
	if (!Game.Init())
	{
		std::cout << "Faild to initialize!";
	}
	//else if (!Game.LoadMedia())
	//{
	//	std::cout << "Faild to load media!";
	//}
	else
	{
		SDL_Event e;
		std::array<SDL_Point, TOTAL_CELLS> Points;
		bool quit = false;

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			SDL_SetRenderDrawColor(Game.GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(Game.GetRenderer());

			if (!Points.empty())
			{
				int i = 0;
				for (int h = SCREEN_HEIGHT / SCREEN_HEIGHT - 1; h <= SCREEN_HEIGHT; h += RECT_HEIGHT)
				{
					for (int w = SCREEN_WIDTH / SCREEN_WIDTH; w <= SCREEN_WIDTH; w += RECT_WEIGHT)
					{
						Points[i].x = w;
						Points[i].y = h;
						++i;
					}
				}
			}

			SDL_SetRenderDrawColor(Game.GetRenderer(), 0x00, 0x00, 0x00, 0x00);
			for (int i = 0; i < TOTAL_CELLS; ++i)
			{
				SDL_Rect RectangleCell = { Points[i].x,Points[i].y,RECT_WEIGHT,RECT_HEIGHT };
				SDL_RenderDrawRect(Game.GetRenderer(), &RectangleCell);
			}

			SDL_RenderPresent(Game.GetRenderer());
		}
	}
}