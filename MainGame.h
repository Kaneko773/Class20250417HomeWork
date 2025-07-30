#pragma once
#include "SequenceBase.h"
#include <list>
#include "Paddle.h"//list�Ŏ��̂��Ǘ����Ă�̂ŃC���N���[�h

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

    bool isMenu;//���j���[���J���Ă邩�ǂ���
    Menu_Select menuSelect;

    float paddleFallSpeed;//�p�h���̗������x�𓝈ꂷ�邽��
};

