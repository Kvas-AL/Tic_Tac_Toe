#include "Game.h"


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
	else if (!Game.LoadMedia())
	{
		std::cout << "Faild to load media!";
	}
	else
	{
		SDL_Event e;
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

			SDL_Rect fillRect = { SCREEN_HEIGHT / 4,SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2,SCREEN_WIDTH / 2 };
			SDL_SetRenderDrawColor(Game.GetRenderer(), 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(Game.GetRenderer(), &fillRect);

			SDL_RenderPresent(Game.GetRenderer());
		}
	}
}