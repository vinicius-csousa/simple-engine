#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : Character(props) {
	m_Animation = new Animation();
	m_Animation->setProps(props->TextureID, 0, 9, 80);

	m_RigidBody = new RigidBody();
}

void Warrior::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt) {

	m_Animation->setProps(m_TextureID, 0, 9, 80); // Default texture = player_idle
	m_RigidBody->UnsetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
		m_RigidBody->ApplyForceX(5);
		m_Animation->setProps("player_run", 0, 8, 80);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		m_RigidBody->ApplyForceX(-5);
		m_Animation->setProps("player_run", 0, 8, 80, SDL_FLIP_HORIZONTAL);
	}

	m_RigidBody->ApplyForceY(-9.81);

	m_RigidBody->Update(dt);
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;
	m_Animation->Update();
}

void Warrior::Clear() {
	TextureManager::GetInstance()->Clear();
}