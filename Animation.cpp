#include "Animation.h"

void Animation::Update() {
	m_SpriteFrame = (SDL_GetTicks64() / m_AnimationSpeed) % m_FrameCount;
}

void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight) {
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::setProps(std::string textureID, int spriteRow, int frameCount, int animationSpeed, SDL_RendererFlip flip) {
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimationSpeed = animationSpeed;
	m_Flip = flip;
}