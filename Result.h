#pragma once
#include "SequenceBase.h"

namespace ResultScene {
    enum NextScene {
        title = 0,
        mainGame = 1,
    };
}

class Result : public SequenceBase
{
public:
    Result();
    ~Result();

    void Enter() override;

    SequenceBase* Execute() override;

    void Exit() override;

    void Draw() override;

private:
    ResultScene::NextScene nextScene;
};

