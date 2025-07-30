#pragma once

union Vector2
{
	struct 
	{
		float x;
		float y;
	};
	struct
	{
		float width;
		float height;
	};

	bool operator==(const Vector2& add) {
		return x == add.x && y == add.y;
	}
	Vector2& operator+=(const Vector2& add) {
		x += add.x;
		y += add.y;
		return *this;
	}
	Vector2 operator+(const Vector2& add) {
		Vector2 temp = { x + add.x, y + add.y };
		return temp;
	}
	Vector2 operator-(const Vector2& add) {
		Vector2 temp = { x - add.x, y - add.y };
		return temp;
	}
	Vector2 operator*(const float& multi) {
		Vector2 temp = { multi * x, multi * y };
		return temp;
	}
};