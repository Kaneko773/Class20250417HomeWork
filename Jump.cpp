#include "Jump.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRateManager.h"
#include "InputManager.h"

#include "Player.h"

Player_StateBase* Jump::Execute(Player* player) {

	Player_StateBase* next = this;

	//重力
	player->Add_vel_y(GravityAcceleration * FrameRateManager::getInstance()->Get_Deltatime());
	//ジャンプボタンが離されたら
	if (InputManager::getInstance()->key_up[KEY_INPUT_SPACE]) {
		if ((GetNowHiPerformanceCount() / 1000000.0f) - player->Get_jumpInputTime() < 0.1f) player->Add_vel_y(0.6f);
	}

	return next;
};