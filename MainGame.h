#pragma once
#include "SequenceBase.h"
#include <list>
#include "Paddle.h"//listで実体を管理してるのでインクルード

class Player;

enum Menu_Select {
    BackGame = 0,
    GoTitle = 1,
};

class MainGame : public SequenceBase
{
public:
    MainGame();
    ~MainGame();

    void Enter() override;

    SequenceBase* Execute() override;

    void Exit() override;

    bool Menu();

    void Draw() override;

private:
    Player* player;
    std::list<Paddle> paddles;

    float timer;
    float nextPaddleCreateTime;

    bool isMenu;//メニューを開いてるかどうか
    Menu_Select menuSelect;

    float paddleFallSpeed;//パドルの落下速度を統一するため
};

