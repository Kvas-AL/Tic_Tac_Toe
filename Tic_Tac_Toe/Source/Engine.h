#pragma once
#include "All_Included_libs.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

class Engine
{
public:

	Engine();
	~Engine();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	bool Init();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
};