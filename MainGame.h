#pragma once
#include "SequenceBase.h"
#include <list>

class Player;
class Paddle;

class MainGame : public SequenceBase
{
    void Enter() override;

    SequenceBase* Execute() override;

    void Exit() override;

private:
    Player* player;
    std::list<Paddle*> paddles;

    float timer;
    float nextPaddleCreateTime;
};

