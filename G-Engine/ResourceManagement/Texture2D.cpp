#include "GEnginePCH.h"
#include "Texture2D.h"

#include <SDL_image.h>
#include <SDL_ttf.h>


dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

void dae::Texture2D::QueryDimensions()
{
	int width, height;
	SDL_QueryTexture(m_Texture, NULL, NULL, &width, &height);
	m_Width = width;
	m_Height = height;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	QueryDimensions();
}
