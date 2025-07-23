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
    void Enter(ScoreManager& scoreManager) override;

    SequenceBase* Execute() override;

    void Exit(ScoreManager& scoreManager) override;

    bool Menu();

    void Draw() override;

private:
    Player* player;
    std::list<Paddle*> paddles;

    float timer;
    float nextPaddleCreateTime;

    bool isMenu;//���j���[���J���Ă邩�ǂ���
    Menu_Select menu_select;

    float paddleFallSpeed;//�p�h���̗������x�𓝈ꂷ�邽��
};

