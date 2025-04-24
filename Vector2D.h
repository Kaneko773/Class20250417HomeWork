#pragma once
template <typename T>
class Vector2D
{
public:
	Vector2D(){
		x = y = 0;
	}
	Vector2D(T valx, T valy) {
		x = valx;
		y = valy;
	}

	Vector2D& operator=(Vector2D source) {
		x = source.x;
		y = source.y;
		return *this;
	}

	T Get_x() {
		return x;
	}
	T Get_y() {
		return y;
	}
	void Set_x(T val) {
		x = val;
	}
	void Set_y(T val) {
		y = val;
	}

private:
	T x;
	T y;
};

