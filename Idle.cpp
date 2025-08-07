#include "Idle.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRateManager.h"
#include "InputManager.h"

#include "Player.h"
#include "Jump.h"

Player_StateBase* Idle::Execute(Player* player) {

	Player_StateBase* next = this;

	//d—Í
	player->Add_vel_y(GravityAcceleration * FrameRateManager::getInstance()->Get_Deltatime());
	//ƒWƒƒƒ“ƒv
	if (InputManager::getInstance()->key_down[KEY_INPUT_SPACE]) {
		player->Set_vel_y(-1.0f * PlayerJumpPower);
		player->Set_jumpInputTime(GetNowHiPerformanceCount() / 1000000.0f);

		next = new Jump();
	}

	return next;
};