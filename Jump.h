#pragma once
#include "Player_StateBase.h"

class Player;

class Jump : public Player_StateBase {
public:
	Jump() {};
	~Jump() {};

	void Enter() override {};

	Player_StateBase* Execute(Player* player) override;

	void Exit() override {};

	void Draw() override {};
};