#pragma once

#include "Character.h"
#include "SpriteAnimation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "CollisionHandler.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 9.0f
#define RUN_FORCE 5.0f
#define ATTACK_TIME 15.0f

class Warrior : public Character
{
public:
	Warrior(Properties* props);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clear();

private:
	SpriteAnimation* m_Animation;
	RigidBody* m_RigidBody;

	void AnimationState();

	bool m_IsRunning;
	bool m_IsAttacking;
	bool m_IsCrouching;
	bool m_IsJumping;
	bool m_IsGrounded;
	bool m_IsFalling;

	float m_JumpTime;
	float m_JumpForce;
	float m_AttackTime;

	Collider* m_Collider;
	Vector2D m_LastSafePosition;
};

