#pragma once

#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include "Point.h"

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

	inline Point* GetOrigin() { return m_Origin; }
	inline void SetDistToPlayer(float dist) { m_DistToPlayer = dist; }

	GameObject(Properties* props) : m_Width(props->Width), m_Height(props->Height), m_TextureID(props->TextureID), m_Flip(props->Flip) {
		m_Transform = new Transform(props->X, props->Y);
		m_Origin = new Point(props->X + props->Width / 2, props->Y + props->Height / 2);
	}

protected:
	Transform* m_Transform;
	int m_Width, m_Height;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
	Point* m_Origin;
	float m_DistToPlayer;
};

