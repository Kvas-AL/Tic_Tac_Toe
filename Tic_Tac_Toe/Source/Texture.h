#pragma once
#include "All_Included_libs.h"

const int RECT_WIDTH = 266;
const int RECT_HEIGHT = 200;

class Texture
{
public:

	Texture();
	~Texture();

	SDL_Texture* GetTexture();

	void TextureRender(int x, int y, SDL_Renderer* Renderer);

	bool LoadFromFile(std::string path, SDL_Renderer* Renderer);

private:
	SDL_Texture* m_Texture;
};