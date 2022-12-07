#pragma once
#include "All_Included_libs.h"

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
	int m_Width, m_Height;
};