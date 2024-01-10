#pragma once

#include "IObject.h"
#include "Transform.h"
#include "SDL.h"

struct Properties {
public:
	Properties(std::string textureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		X = x;
		Y = y;
		Width = width;
		Height = height;
		TextureID = textureID;
		Flip = flip;
	}

	float X, Y;
	int Width, Height;
	std::string TextureID;
	SDL_RendererFlip Flip;
};

class GameObject : public IObject
{
public:
	virtual void Draw() = 0;
	virtual void Update(float dt = 0) = 0;
	virtual void Clear() = 0;

	GameObject(Properties* props) : m_Width(props->Width), m_Height(props->Height), m_TextureID(props->TextureID), m_Flip(props->Flip) {
		m_Transform = new Transform(props->X, props->Y);
	}

protected:
	Transform* m_Transform;
	int m_Width, m_Height;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;

};

