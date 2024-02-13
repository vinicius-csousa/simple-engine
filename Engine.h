#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
#include <vector>
#include "GameObject.h"
#include "GameState.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
public:
	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}
	
	bool Init();

	void Clear();
	void Quit();
	void Render();
	void Update();
	void Events();

	void PopState();
	void PushState(GameState* current);
	void ChangeState(GameState* target);

	inline GameMap* GetMap() { return m_LevelMap; }
	inline bool IsRunning() { return m_IsRunning; }
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }

private:
	static Engine* s_Instance;
	bool m_IsRunning;
	
	GameMap* m_LevelMap;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	std::vector<GameObject*> m_GameObjects;
	std::vector<GameState> m_States;

	Engine() {};
};
