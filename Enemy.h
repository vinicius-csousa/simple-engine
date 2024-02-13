#pragma once

#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SeqAnimation.h"
#include "SpriteAnimation.h"
#include "CollisionHandler.h"

class Enemy : public Character
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clear();
	virtual void Update(float dt);
	void AnimationState();

private:
	Collider* m_Collider;
	RigidBody* m_RigidBody;
	SeqAnimation* m_Animation;
	Vector2D m_LastSafePosition;
	int m_MovDir = 1;
	int m_LastMovDir = 1;

	bool m_IsIdling;
	bool m_IsWalking;
	bool m_IsAttacking;
};

