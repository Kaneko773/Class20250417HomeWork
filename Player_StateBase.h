#pragma once

class Player;

class Player_StateBase {
public:
	Player_StateBase() {};
	virtual ~Player_StateBase() {};

	virtual void Enter() = 0;

	virtual Player_StateBase* Execute(Player* player) = 0;

	virtual void Exit() = 0;

	virtual void Draw() = 0;
};
