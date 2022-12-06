#pragma once
#include "All_Included_libs.h"
#include "Engine.h"
#include "Texture.h"
#include "GameLogic.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int RECT_WIDTH;
extern const int RECT_HEIGHT;

extern const int TOTAL_CELLS;

enum TextureNumbering
{
	CROSS_TEXTURE = 0,
	CIRCLE_TEXTURE,

	CROSS_WIN_SCREEN_TEXTURE,
	CIRCLE_WIN_SCREEN_TEXTURE,
	DRAW_WIN_SCREEN_TEXTURE,

	TOTAL_TEXTURE
};

std::array<SDL_Point, TOTAL_CELLS> GetPoints();

void GameLoop();