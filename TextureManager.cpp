#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"
#include <map>

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename) {
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) {
		SDL_Log("Failed to load texture %s: $s", filename.c_str(), SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("Failed to create texture from surface: $s", SDL_GetError());
		return false;
	}

	m_TextureMap[id] = texture;

	return true;
}

bool TextureManager::ParseTextures(std::string source) {

	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cout << "Failed to open " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("texture")) {
			std::string id = e->Attribute("id");
			std::string src = e->Attribute("source");
			Load(id, src);
		}
	}

	std::cout << "Textures parsed successfully" << std::endl;

	return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float xScale, float yScale, float scrollRatio, SDL_RendererFlip flip) {
	Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;

	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = { x - cam.X, y, width*xScale, height*yScale };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip) {
	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect srcRect = { tileSize * frame, tileSize * row, tileSize, tileSize };
	SDL_Rect dstRect = { x - cam.X, y, tileSize, tileSize };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect srcRect = { width*frame, height*row, width, height };
	SDL_Rect dstRect = { x - cam.X, y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(std::string id) {
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void TextureManager::Clear(){
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	m_TextureMap.clear();

	SDL_Log("Textures succesfully cleaned");
}
