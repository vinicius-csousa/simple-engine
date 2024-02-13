#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat){}

void SpriteAnimation::Update(float dt) {
	if (m_Repeat || !m_IsEnded) {
		m_IsEnded = false;
		m_SpriteFrame = (SDL_GetTicks64() / m_AnimationSpeed) % m_FrameCount;
	}

	if (!m_Repeat && m_SpriteFrame == m_FrameCount-1) {
		m_IsEnded = true;
		m_SpriteFrame = m_FrameCount-1;
	}
	// m_SpriteFrame = (SDL_GetTicks64() / m_AnimationSpeed) % m_FrameCount;
}

void SpriteAnimation::Draw(int x, int y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE) {
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
}

void SpriteAnimation::setProps(std::string textureID, int spriteRow, int frameCount, int animationSpeed) {
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimationSpeed = animationSpeed;
}