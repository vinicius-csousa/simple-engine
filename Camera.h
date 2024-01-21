#pragma once

#include "SDL.h"
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"

class Camera
{
public:
	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

	void Update(float dt);
	inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }
	inline void SetTarget(Point* target) { m_Target = target; }

private:
	Camera() { m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; }

	static Camera* s_Instance;
	SDL_Rect m_ViewBox;
	Point* m_Target;
	Vector2D m_Position;

};

