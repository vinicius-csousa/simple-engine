#include "Enemy.h"
#include <stdio.h>
#include <iostream>
#include "ObjectFactory.h"

static Registr<Enemy> registr("Enemy");

Enemy::Enemy(Properties* props) : Character(props) {
	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.0f);
	m_Collider = new Collider();
	m_Collider->SetBox(props->X, props->Y, props->Width, props->Height);
	m_Collider->SetBuffer(-120, -65, 240, 70);

	m_Animation = new SeqAnimation(false);
	m_Animation->Parse("assets/animations.xml");
	m_Animation->SetCurrentSeq("demon_idle");
	m_Animation->SetRepeat(true);
}

void Enemy::Draw() {
	m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 1, 1, m_Flip);
	m_Collider->Draw();
}

void Enemy::AnimationState() {
	if (m_IsIdling)
		m_Animation->SetCurrentSeq("demon_idle");

	if (m_IsWalking) 
		m_Animation->SetCurrentSeq("demon_walk");

	if (m_IsAttacking)
		m_Animation->SetCurrentSeq("demon_cleave");
}

void Enemy::Update(float dt) {
	// To-do: add AI to the enemy
	m_IsIdling = false;
	m_IsWalking = false;
	m_IsAttacking = false;
	m_RigidBody->UnsetForce();
	
	if (m_Transform->X <= 300) {
		m_MovDir = 1;
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsWalking = true;
	}
	if (m_Transform->X >= 500) {
		m_MovDir = -1;
		m_Flip = SDL_FLIP_NONE;
		m_IsWalking = true;
	}
	if (abs(m_DistToPlayer) <= 50) {
		m_IsAttacking = true;
		if (m_DistToPlayer >= 0)
			m_Flip = SDL_FLIP_HORIZONTAL;
		else
			m_Flip = SDL_FLIP_NONE;
	}

	if (!m_IsAttacking)
		m_RigidBody->ApplyForceX(1.0 * m_MovDir);

	// Horizontal movement
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, 288, 160);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox()))
		m_Transform->X = m_LastSafePosition.X;

	// Vertical movement
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, 288, 160);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox()))
		m_Transform->Y = m_LastSafePosition.Y;

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	AnimationState();
	m_Animation->Update(dt);
}

void Enemy::Clear() {
}