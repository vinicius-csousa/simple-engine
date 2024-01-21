#include <iostream>
#include "Engine.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init() {
	if ((SDL_Init(SDL_INIT_VIDEO) != 0) || IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("SimpleEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (m_Window == nullptr) {
		SDL_Log("Failed to initialize window: %s", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) {
		SDL_Log("Failed to initialize renderer: %s", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load()) {
		SDL_Log("Failed to load map: %s", SDL_GetError());
		//return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("map");

	TextureManager::GetInstance()->Load("player_idle", "assets/images/characters/soldier/Idle.png");
	TextureManager::GetInstance()->Load("player_run", "assets/images/characters/soldier/Run.png");
	TextureManager::GetInstance()->Load("background", "assets/images/background.jpg");

	player = new Warrior(new Properties("player_idle", 100, 320, 128, 128, SDL_FLIP_HORIZONTAL));

	Camera::GetInstance()->SetTarget(player->GetOrigin());

	return m_IsRunning = true;
};

void Engine::Update() {
	float dt = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	player->Update(dt);
	Camera::GetInstance()->Update(dt);
};

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 234, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("background", 0, -520, 1920, 1080);
	m_LevelMap->Render();
	player->Draw();

	SDL_RenderPresent(m_Renderer);
};

void Engine::Events() {
	Input::GetInstance()->Listen();
};

void Engine::Clear() {
	TextureManager::GetInstance()->Clear();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
};


void Engine::Quit() {
	m_IsRunning = false;
};