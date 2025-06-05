#pragma once
#include "Vector2.h"

class BoxCollider
{
public:
	void Initialization(Vector2<float> center, Vector2<float> size);

	float Get_rightSide() {
		return _center.Get_x() + _size.Get_width() / 2.0f;
	}
	float Get_leftSide() {
		return _center.Get_x() - _size.Get_width() / 2.0f;
	}
	float Get_topSide() {
		return _center.Get_y() - _size.Get_height() / 2.0f;
	}
	float Get_bottomSide() {
		return _center.Get_y() + _size.Get_height() / 2.0f;
	}

	Vector2<float> _center;
	Vector2<float> _size;
};

