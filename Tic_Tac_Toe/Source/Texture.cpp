#include "Texture.h"

Texture::Texture() :m_Texture(nullptr) {}

Texture::~Texture()
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = nullptr;
}

SDL_Texture* Texture::GetTexture()
{
	return m_Texture;
}

void Texture::TextureRender(int x, int y, SDL_Renderer* Renderer)
{
	SDL_Rect RenderQuad = { x,y,RECT_WIDTH,RECT_HEIGHT };

	SDL_RenderCopy(Renderer, m_Texture, NULL, &RenderQuad);
}

bool Texture::LoadFromFile(std::string path, SDL_Renderer* Renderer)
{
	bool succsesful = true;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!(loadedSurface))
	{
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
		succsesful = false;
	}
	else
	{
		m_Texture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (!(m_Texture))
		{
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << "\n";
			succsesful = false;
		}
		SDL_FreeSurface(loadedSurface);
	}

	return succsesful;
}