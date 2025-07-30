#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 _pos, Vector2 _size)
{
	center = _pos;
	size = _size;
	fourSides = {
		center.x + size.width / 2.0f,
		center.x - size.width / 2.0f,
		center.y - size.height / 2.0f,
		center.y + size.height / 2.0f
	};
	movementPerFrame = { 0, 0 };
	isCollisionResponse = false;
}

void BoxCollider::MoveByRate(float moveRate)
{
	center += movementPerFrame * moveRate;

	fourSides = {
		center.x + size.width / 2.0f,
		center.x - size.width / 2.0f,
		center.y - size.height / 2.0f,
		center.y + size.height / 2.0f
	};
}

void BoxCollider::FixedMove(Vector2 pos)
{
	center = pos;

	fourSides = {
		center.x + size.width / 2.0f,
		center.x - size.width / 2.0f,
		center.y - size.height / 2.0f,
		center.y + size.height / 2.0f
	};
}