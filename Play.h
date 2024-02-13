#pragma once

#include <iostream>
#include "GameState.h"
#include "GameMap.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Timer.h"
#include "Menu.h"
#include "Input.h"
#include "Camera.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "CollisionHandler.h"

class Play : public GameState
{
public:
	Play();
	virtual bool Init() = 0;
	virtual bool Exit() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	static void OpenMenu();
	static void PauseGame();

	bool m_EditMode;
	GameMap* m_LevelMap;
	std::vector<GameObject*> m_GameObjects;
};

