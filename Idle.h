#pragma once
#include "Player_StateBase.h"

class Player;

class Idle : public Player_StateBase {
public:
	Idle() {};
	~Idle() {};

	void Enter() override {};

	Player_StateBase* Execute(Player* player) override;

	void Exit() override {};

	void Draw() override {};
};