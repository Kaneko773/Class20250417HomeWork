#include "DxLib.h"
#include "Player.h"

Player::Player(int x, int y) {
	Vector2D<int> temp(x, y);
	m_pos = temp;
}

void Player::Draw() {
	int GHandle = LoadGraph("‰æ‘œ/figure_jump.png");
	int drawPosx = m_pos.Get_x();
	int drawPosy = m_pos.Get_y();
	DrawExtendGraph(drawPosx, drawPosy, drawPosx+358 / 2, drawPosy+400 / 2, GHandle, TRUE);
	DeleteGraph(GHandle);
}