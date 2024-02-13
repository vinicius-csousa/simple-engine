#include <iostream>
#include "Engine.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "ObjectFactory.h"

Engine* Engine::s_Instance = nullptr;

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
		return false;
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("map");

	TextureManager::GetInstance()->ParseTextures("assets/textures.xml");

	GameObject* player = ObjectFactory::GetInstance()->CreateObject("Warrior", new Properties("player", 100, 250, 115, 84));
	GameObject* demon = ObjectFactory::GetInstance()->CreateObject("Enemy", new Properties("demon", 300, 250, 288, 160));

	m_GameObjects.push_back(player);
	m_GameObjects.push_back(demon);

	Camera::GetInstance()->SetTarget(player->GetOrigin());

	return m_IsRunning = true;
};

void Engine::Update() {
	float dt = Timer::GetInstance()->GetDeltaTime();
	m_LevelMap->Update();
	
	for (unsigned int i = 0; i < m_GameObjects.size(); i++) {
		if (i > 0)
			m_GameObjects[i]->SetDistToPlayer(CollisionHandler::GetInstance()->CalculateDistance(m_GameObjects[0]->GetOrigin(), m_GameObjects[i]->GetOrigin()));
		m_GameObjects[i]->Update(dt);
	}

	Camera::GetInstance()->Update(dt);
};

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 234, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("background", 0, -520, 1920, 1080, 1, 1, 0.5);
	m_LevelMap->Render();
	
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects[i]->Draw();

	SDL_RenderPresent(m_Renderer);
};

void Engine::Events() {
	Input::GetInstance()->Listen();
};

void Engine::Clear() {
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects[i]->Clear();

	TextureManager::GetInstance()->Clear();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
};


void Engine::Quit() {
	m_IsRunning = false;
};