#include "Menu.h"

bool Menu::Init() {
	m_Ctxt = Engine::GetInstance()->GetRenderer();
	SDL_Log("Menu initialized");
	return true;
}

bool Menu::Exit() {
	SDL_Log("Menu exited");
	return true;
}

void Menu::Render() {
	SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
	SDL_RenderClear(m_Ctxt);
	SDL_RenderPresent(m_Ctxt);
}

void Menu::Update() {

}

void Menu::StartGame() {

}

void Menu::Settings() {

}

void Menu::Editor() {

}

void Menu::Quit() {

}