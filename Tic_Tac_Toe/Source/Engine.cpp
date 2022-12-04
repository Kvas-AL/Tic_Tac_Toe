#include "Engine.h"

Engine::Engine() : m_Window(nullptr), m_Renderer(nullptr) {}

Engine::~Engine()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = nullptr;
	m_Window = nullptr;

	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Engine::GetRenderer()
{
	return m_Renderer;
}

SDL_Window* Engine::GetWindow()
{
	return m_Window;
}

bool Engine::Init()
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
