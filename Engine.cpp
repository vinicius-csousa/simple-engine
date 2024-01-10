#include <iostream>
#include "Engine.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Input.h"

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

	TextureManager::GetInstance()->Load("tree", "assets/images/tree.png");
	TextureManager::GetInstance()->Load("player_idle", "assets/images/characters/soldier/Idle.png");
	TextureManager::GetInstance()->Load("player_run", "assets/images/characters/soldier/Run.png");

	player = new Warrior(new Properties("player_idle", 100, 320, 128, 128, SDL_FLIP_HORIZONTAL));

	return m_IsRunning = true;
};

void Engine::Update() {
	player->Update(0);
};

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 234, 255);
	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("tree", 100, 100, 750, 750);

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