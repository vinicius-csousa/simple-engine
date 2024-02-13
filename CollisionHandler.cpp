#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
	m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
	m_CollisionTileMap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
	bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
	bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
	return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {
	int tileSize = 32;
	int rowCount = 20;
	int colCount = 60;

	int left_tile = a.x / tileSize;
	int right_tile = (a.x + a.w) / tileSize;

	int top_tile = a.y / tileSize;
	int bottom_tile = (a.y + a.h) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile >= colCount) right_tile = colCount - 1;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile >= rowCount) bottom_tile = rowCount - 1;

	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bottom_tile; j++) {
			if (m_CollisionTileMap[j][i] > 0)
				return true;
		}
	}

	return false;
}

float CollisionHandler::CalculateDistance(Point* p1, Point* p2) {
	return sqrt(pow((p1->X - p2->X), 2) + pow((p2->Y - p2->Y), 2))*(p1->X > p2->X ? 1 : -1);
}