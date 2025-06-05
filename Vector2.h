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

