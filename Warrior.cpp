#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "ObjectFactory.h"
#include <string>

static Registr<Warrior> registr("Warrior");

Warrior::Warrior(Properties* props) : Character(props) {
	
	m_JumpForce = JUMP_FORCE;
	m_JumpTime = JUMP_TIME;
	m_AttackTime = ATTACK_TIME;

	m_Collider = new Collider();
	m_Collider->SetBox(props->X, props->Y, props->Width, props->Height);
	m_Collider->SetBuffer(-45, -7, 100, 70);
	
	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.0f);

	m_Animation = new SpriteAnimation();
	m_Animation->setProps(props->TextureID, 0, 8, 80);
}

void Warrior::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

	//m_Collider->Draw();
}

void Warrior::AnimationState() {
	// Idling
	m_Animation->setProps(m_TextureID, 0, 8, 80);
	m_Animation->setRepeat(true);

	// Running
	if (m_IsRunning) {
		m_Animation->setProps(m_TextureID, 2, 8, 120);
	}

	if (m_IsCrouching) {
		m_Animation->setProps(m_TextureID, 13, 2, 100);
		m_Animation->setRepeat(false);
	}

	if (m_IsAttacking) {
		m_Animation->setProps(m_TextureID, 9, 4, 80);
	}

	if (m_IsJumping) {
		m_Animation->setProps(m_TextureID, 5, 1, 200);
		m_Animation->setRepeat(false);
	}

	if (m_IsFalling) {
		m_Animation->setProps(m_TextureID, 7, 1, 120);
		m_Animation->setRepeat(false);
	}
}

void Warrior::Update(float dt) {

	m_IsRunning = false;
	m_IsCrouching = false;
	m_RigidBody->UnsetForce();

	// Run forward
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == 1 && !m_IsAttacking) {
		m_RigidBody->ApplyForceX(RUN_FORCE);
		m_IsRunning = true;
		m_Flip = SDL_FLIP_NONE;
	}

	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == -1 && !m_IsAttacking) {
		m_RigidBody->ApplyForceX(-RUN_FORCE);
		m_IsRunning = true;
		m_Flip = SDL_FLIP_HORIZONTAL;
	}

	// Crouching
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && m_IsGrounded) {
		m_RigidBody->UnsetForce();
		m_IsCrouching = true;
	}

	// Jumping
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(-m_JumpForce);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(-m_JumpForce);
	}
	else {
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	// Falling
	if (m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded)
		m_IsFalling = true;
	else
		m_IsFalling = false;

	// Attacking
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_L)) {
		m_RigidBody->UnsetForce();
		m_IsAttacking = true;
	}
	if (m_IsAttacking && m_AttackTime > 0)
		m_AttackTime -= dt;
	else {
		m_AttackTime = ATTACK_TIME;
		m_IsAttacking = false;
	}

	// Horizontal movement
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, 128, 128);
	
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())) {
		m_Transform->X = m_LastSafePosition.X;
	}

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Collider->SetBox(m_Transform->X, m_Transform->Y, 128, 128);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())) {
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	AnimationState();
	m_Animation->Update(0);
}

void Warrior::Clear() {
	TextureManager::GetInstance()->Drop(m_TextureID);
}