#pragma once
#include "All_Included_libs.h"
#include "Engine.h"
#include "Texture.h"
#include "GameLogic.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int RECT_WEIGHT;
extern const int RECT_HEIGHT;

extern const int TOTAL_CELLS;

std::array<SDL_Point, TOTAL_CELLS> GetPoints();

void GameLoop();