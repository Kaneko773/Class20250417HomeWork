#pragma once
#include "Vector2D.h"

class Player
{
public:
	Player(int x, int y);

	Vector2D<int> Get_m_pos() {//m_pos‚Ì‚Ü‚Ü
		return m_pos;
	}
	int Get_m_pos_x() {//x‚¾‚¯
		return m_pos.Get_x();
	}
	int Get_m_pos_y() {//y‚¾‚¯
		return m_pos.Get_y();
	}
	void Set_m_pos(int valx, int valy) {
		m_pos.Set_x(valx);
		m_pos.Set_y(valy);
	}
	void Draw();

private:
	Vector2D<int> m_pos;
};

