#pragma once

#include "SDL.h"
#include "Camera.h"

class Collider {
public:
	inline SDL_Rect GetBox() { return m_Box; }
	inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x, y, w, h }; }

	void SetBox(int x, int y, int w, int h) {
		m_Box = { x - m_Buffer.x, y - m_Buffer.y, w - m_Buffer.w, h - m_Buffer.h };
	}

	void Draw() {
		Vector2D cam = Camera::GetInstance()->GetPosition();
		SDL_Rect box = m_Box;
		box.x -= cam.X;
		//box.y -= cam.Y;

		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
	}


private:
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;
};