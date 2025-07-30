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
	
	void MoveByRate(float moveRate = 1.0f);//�����ňړ�
	void FixedMove(Vector2 pos);

	Vector2 center;
	Vector2 size;
	FourSides fourSides;

	Vector2 movementPerFrame;//�P�t���[���ł̈ړ���
	bool isCollisionResponse;//�Փˉ����������ǂ���
};

