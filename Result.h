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
    void Enter() override;

    SequenceBase* Execute(ScoreManager& scoreManager) override;

    void Exit() override;

private:
    ResultScene::NextScene nextScene{};
};

