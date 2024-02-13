#pragma once

#include <string>
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"

class SpriteAnimation : Animation
{
public:
	SpriteAnimation(bool repeat = true);

	virtual void Update(float dt);
	void Draw(int x, int y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip);
	void setProps(std::string textureID, int spriteRow, int frameCount, int animationSpeed);
	void setRepeat(bool repeat) { m_Repeat = repeat; }
	
private:
	int m_SpriteRow, m_SpriteFrame, m_FrameCount, m_AnimationSpeed;
	std::string m_TextureID;
};

