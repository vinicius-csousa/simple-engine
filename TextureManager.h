#pragma once

#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
#include "tinyxml.h"

class TextureManager
{
public:
	static TextureManager* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
	}

	bool Load(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Drop(std::string id);
	void Clear();

	void Draw(std::string id, int x, int y, int width, int height, float xScale = 1, float yScale = 1, float scrollRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager() {};
	std::map<std::string, SDL_Texture*> m_TextureMap;
	static TextureManager* s_Instance;
};

