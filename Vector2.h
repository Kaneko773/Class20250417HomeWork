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

	float& Get_x() {
		return Vec2.x;
	}
	float& Get_y() {
		return Vec2.y;
	}
	float& Get_width() {
		return Vec2.width;
	}
	float& Get_height() {
		return Vec2.height;
	}

private:
	U_Vector2<T> Vec2;
};

