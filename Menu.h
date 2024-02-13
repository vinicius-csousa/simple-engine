#pragma once

#include "GameState.h"
#include "SDL.h"
#include "Engine.h"

class Menu : public GameState
{
public:
	Menu(){}
	virtual bool Init() = 0;
	virtual bool Exit() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	static void StartGame();
	static void Settings();
	static void Editor();
	static void Quit();
};

