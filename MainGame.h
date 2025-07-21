#pragma once
#include "SequenceBase.h"
#include <list>

enum Menu_Select {
    BackGame = 0,
    GoTitle = 1,
};

class Player;
class Paddle;

class MainGame : public SequenceBase
{
    void Enter() override;

    SequenceBase* Execute(ScoreManager& scoreManager) override;

    void Exit() override;

    bool Menu();

private:
    Player* player;
    std::list<Paddle*> paddles;

    float timer;
    float nextPaddleCreateTime;

    bool isMenu;//メニューを開いてるかどうか
    Menu_Select menu_select;

    float paddleFallSpeed;//パドルの落下速度を統一するため
};

