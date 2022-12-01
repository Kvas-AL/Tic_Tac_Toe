#pragma once
#include "All_Included_libs.h"
#include "Texture.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

void GameLoop();

class Game
{
public:

	Game();
	~Game();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	bool Init();

	bool LoadMedia();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Texture m_Texture;
};