#pragma once
#include "Vector2.h"

struct FourSides {
	float rightSide;
	float leftSide;
	float topSide;
	float bottomSide;
};

class BoxCollider
{
public:
	BoxCollider(Vector2 _pos, Vector2 _size);
	virtual ~BoxCollider() {};
	
	void MoveByRate(float moveRate = 1.0f);//Š„‡‚ÅˆÚ“®
	void FixedMove(Vector2 pos);

	Vector2 center;
	Vector2 size;
	FourSides fourSides;

	Vector2 movementPerFrame;//‚PƒtƒŒ[ƒ€‚Å‚ÌˆÚ“®—Ê
	bool isCollisionResponse;//Õ“Ë‰“š‚µ‚½‚©‚Ç‚¤‚©
};

