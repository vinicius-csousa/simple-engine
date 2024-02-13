#pragma once

#include "SDL.h"
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"
#include <vector>


class CollisionHandler
{
public:
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	bool MapCollision(SDL_Rect a);
	float CalculateDistance(Point* p1, Point* p2);

	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

private:
	CollisionHandler();
	static CollisionHandler* s_Instance;

	TileMap m_CollisionTileMap;
	TileLayer* m_CollisionLayer;

};

