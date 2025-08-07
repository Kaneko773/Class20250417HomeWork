#include "Player.h"

#include "DxLib.h"
#include "GameInfo.h"
#include "FrameRateManager.h"
#include "InputManager.h"

#include "Player_StateBase.h"
#include "Idle.h"

Player::Player(Vector2 pos, Vector2 size) : BoxCollider(pos, size)
{
	handle = LoadGraph("画像/300-300.png");

	//////////////////////////////////////////////////////////
	char handlePath[256];
	for (int i = 0; i < 10; ++i) {
		sprintf_s(handlePath, sizeof(handlePath), "画像/redhatfiles/png/Idle (%d).png", i + 1);
		handle_idle[i] = LoadGraph(handlePath);
	}
	handle_jump = LoadGraph("画像/redhatfiles/png/Jump (6).png");
	//////////////////////////////////////////////////////////

	canJump = false;

	vel_y = 0;

	jumpInputTime = 0;

	currentState = new Idle();
	currentState->Enter();
}
Player::~Player() 
{
	DeleteGraph(handle);

	//////////////////////////////////////////////////////////
	for (int i = 0; i < 10; ++i) {
		DeleteGraph(handle_idle[i]);
	}
	DeleteGraph(handle_jump);
	//////////////////////////////////////////////////////////

	if (currentState) {
		currentState->Exit();
		delete currentState;
		currentState = nullptr;
	}
}

void Player::Update()
{
	movementPerFrame = {0, 0};
	isCollisionResponse = false;
#if 0
	//重力
	vel_y += GravityAcceleration * FrameRateManager::getInstance()->Get_Deltatime();
	//ジャンプ
	if (InputManager::getInstance()->key_down[KEY_INPUT_SPACE] && canJump) {
		canJump = false;
		vel_y = -1.0f * PlayerJumpPower;
		jumpInputTime = GetNowHiPerformanceCount() / 1000000.0f;
	}
	if (!canJump) {
		//ジャンプボタンが離されたら
		if (InputManager::getInstance()->key_up[KEY_INPUT_SPACE]) {
			if ((GetNowHiPerformanceCount() / 1000000.0f) - jumpInputTime < 0.1f) vel_y += 0.2f;
		}
	}
#endif

	Player_StateBase* nextState = currentState->Execute(this);//更新
	if (nextState != currentState) //遷移
	{
		currentState->Exit();
		delete currentState;
		currentState = nextState;
		currentState->Enter();
	}

	movementPerFrame.y = vel_y;
}

void Player::Draw() const
{
	DrawExtendGraph((int)fourSides.leftSide, (int)fourSides.topSide, (int)fourSides.rightSide, (int)fourSides.bottomSide, handle, TRUE);
}

void Player::Landing() {
	canJump = true;
	vel_y = 0;
	isCollisionResponse = true;
	if (currentState) {
		currentState->Exit();
		delete currentState;
		currentState = new Idle();
		currentState->Enter();
	}
}