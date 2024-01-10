#pragma once

#include <string>
#include "SDL.h"
#include "TextureManager.h"

class Animation
{
public:
	Animation(){}

	void Update();
	void Draw(int x, int y, int spriteWidth, int spriteHeight);
	void setProps(std::string textureID, int spriteRow, int frameCount, int animationSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
private:
	int m_SpriteRow, m_SpriteFrame, m_FrameCount, m_AnimationSpeed;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
};

