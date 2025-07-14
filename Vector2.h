#pragma once

template <typename T>
union U_Vector2
{
	struct 
	{
		T x;
		T y;
	};
	struct
	{
		T width;
		T height;
	};
};

template <typename T>
class Vector2
{
public:
	Vector2() {
		Vec2.x = Vec2.y = 0;
	}
	Vector2(T t1, T t2) {
		Vec2.x = t1;
		Vec2.y = t2;
	}

	Vector2& operator+=(const Vector2& add) {
		Vec2.x += add.Vec2.x;
		Vec2.y += add.Vec2.y;
		return *this;
	}
	Vector2 operator+(const Vector2& add) {
		Vector2<float> temp(Vec2.x + add.Vec2.x, Vec2.y + add.Vec2.y);
		return temp;
	}
	Vector2 operator-(const Vector2& add) {
		Vector2<float> temp(Vec2.x - add.Vec2.x, Vec2.y - add.Vec2.y);
		return temp;
	}
	Vector2 operator*(const float& multi) {
		Vector2<float> temp(multi * Vec2.x, multi * Vec2.y);
		return temp;
	}

	float Get_x() {
		return Vec2.x;
	}
	float Get_y() {
		return Vec2.y;
	}
	float Get_width() {
		return Vec2.width;
	}
	float Get_height() {
		return Vec2.height;
	}
	void Set_x(float _) {
		Vec2.x = _;
	}
	void Set_y(float _) {
		Vec2.y = _;
	}
	void Set_width(float _) {
		Vec2.width = _;
	}
	void Set_height(float _) {
		Vec2.height = _;
	}

	void Reset() {
		Vec2.x = 0;
		Vec2.y = 0;
	}

private:
	U_Vector2<T> Vec2;
};

